#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <iostream>
#include <functional>
#include <boost/asio.hpp>

// Default message received callback!!!
inline void echo(const std::string &message) {
    std::cout << "arduino>" << message << std::endl;
}

class Serial {
public:
    explicit Serial(
        const std::string &port,
        std::function<void(const std::string)> callback = echo, 
        int baud_rate = 115200);
    ~Serial();
    void write(const std::string &message);
protected:
    // Asyncronous reading!!!!
    void readingStart();
    void readingStop();
    void read();
private:
    boost::asio::io_context m_iocontext;
    boost::asio::io_service m_ioservice;
    boost::asio::serial_port m_serial;
    std::function<void(const std::string)> m_callback;
    boost::asio::streambuf m_buffer;
    std::thread m_thread;
    std::atomic<bool> m_running;
    std::atomic<bool> m_reading;
};

#endif
