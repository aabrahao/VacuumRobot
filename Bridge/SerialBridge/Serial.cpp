#include "Serial.h"

Serial::Serial(
    const std::string &port,
    std::function<void(const std::string)> callback,
    int baud_rate)
    : m_ioservice(),
      m_serial(m_iocontext),
      m_callback(callback),
      m_running(false),
      m_reading(false) {
    m_serial.open(port);
    m_serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
    m_serial.set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none));
    m_serial.set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::none));
    m_serial.set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one));
    m_serial.set_option(boost::asio::serial_port::character_size(boost::asio::serial_port::character_size(8)));
    readingStart();
}

Serial::~Serial() {
    readingStop();
    if (m_serial.is_open())
        m_serial.close();
}

void Serial::readingStart() {
    // Run io_context in separate thread
    m_thread = std::thread(
        [this]() { 
            m_iocontext.run(); 
    });
    // Start reading
    read();
}

void Serial::readingStop() {
    m_iocontext.stop();
    if (m_thread.joinable())
        m_thread.join();
}

void Serial::write(const std::string &message) {
    boost::asio::write(m_serial, boost::asio::buffer(message + '\n'));
}

void Serial::read() {
    boost::asio::async_read_until(m_serial, m_buffer, '\n',
        [this](boost::system::error_code error, std::size_t bytes) {
            if (!error) {
                // Get the data
                std::istream stream(&m_buffer);
                std::string line;
                std::getline(stream, line);
                // Execute received callback
                m_callback(line);
                // Read next
                read();
            }
            else {
                std::cout << "Error: opps, " << error.message() << std::endl;
            }
    });
}
