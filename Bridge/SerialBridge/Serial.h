#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <iostream>
#include <functional>
#include <thread>
#include <atomic>
#include <stdexcept>
#include <boost/asio.hpp>

class Serial {
public:
    using MessageCallback = std::function<void(const std::string&)>;
    using ErrorCallback = std::function<void(const std::string&)>;
    // Default callbacks
    static void messageCallback(const std::string& message) {
        std::cout << "Firmware>" << message << std::endl;
    }
    static void errorCallback(const std::string& error) {
        std::cerr << "Serial error: " << error << std::endl;
    }
    // Constructor
    explicit Serial(
        const std::string& port,
        MessageCallback onMessage = messageCallback,
        ErrorCallback onError = errorCallback,
        int baud = 115200);
    // Destructor
    ~Serial();
    // Non-copyable but movable
    Serial(const Serial&) = delete;
    Serial& operator=(const Serial&) = delete;
    Serial(Serial&&) = default;
    Serial& operator=(Serial&&) = default;
    // Messages
    void send(const std::string& message);
    bool connected() const;
protected:
    // Asynchronous reading methods
    void startReading();
    void stopReading();
    void doRead();
private:
    boost::asio::io_context m_context;
    boost::asio::serial_port m_port;
    MessageCallback m_onMessage;
    ErrorCallback m_onError;
    boost::asio::streambuf m_buffer;
    std::thread m_thread;
};

#endif
