#include "Serial.h"

Serial::Serial(const std::string& port, MessageCallback onMessage, ErrorCallback onError, int baud)
    : m_context(),
      m_port(m_context),
      m_onMessage(onMessage),
      m_onError(onError) {
    try {
        m_port.open(port);
        m_port.set_option(boost::asio::serial_port_base::baud_rate(baud));
        m_port.set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none));
        m_port.set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::none));
        m_port.set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one));
        m_port.set_option(boost::asio::serial_port::character_size(boost::asio::serial_port::character_size(8)));
        startReading();
    } catch (const boost::system::system_error& e) {
        throw std::runtime_error("Failed to open serial port '" + port + "': " + std::string(e.what()));
    }
}

Serial::~Serial() {
    stopReading();
    if (m_port.is_open()) 
        m_port.close();
}

void Serial::startReading() {
    m_thread = std::thread([this]() { 
        m_context.run(); 
    });
    doRead();
}

void Serial::stopReading() {
    if (!m_context.stopped())
        m_context.stop();
     if (m_thread.joinable())
        m_thread.join();
}

void Serial::send(const std::string& message) {
    try {
        boost::asio::write(m_port, boost::asio::buffer(message + '\n'));
    } catch (const boost::system::system_error& e) {
        if (m_onError)
            m_onError("Write failed: " + std::string(e.what()));
    }
}

bool Serial::connected() const {
    return m_port.is_open();
}

void Serial::doRead() {
    boost::asio::async_read_until(m_port, m_buffer, '\n',
        [this](boost::system::error_code error, std::size_t bytes) {
            if (!error) {
                try {
                    // Get the data
                    std::istream stream(&m_buffer);
                    std::string line;
                    std::getline(stream, line);
                    // Remove carriage return if present
                    if (!line.empty() && line.back() == '\r')
                        line.pop_back();
                    // Invoke received callback
                    if (m_onMessage)
                        m_onMessage(line);
                    // Continue reading
                    doRead();
                } catch (const std::exception& e) {
                    if (m_onError)
                        m_onError("Message processing failed: " + std::string(e.what()));
                }
            } else if (error != boost::asio::error::operation_aborted) {
                // Only report errors that aren't from intentional cancellation
                if (m_onError)
                    m_onError("Read operation failed: " + error.message());
            }
        });
}