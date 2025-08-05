#ifndef __SERIAL_PORT_H__
#define __SERIAL_PORT_H__

#include "Command.h"

class SerialPort {
public:
  using ReceivedCallback = void (*)(const String &);
  SerialPort(long baud, ReceivedCallback callback, bool echo=false)
  : m_echo(echo), 
    m_baud(baud), 
    m_callback(callback) { }
  void setEcho(bool echo) { m_echo = echo; }
  void setup() {
    Serial.begin(m_baud);
  }
  void update() {
    if (Serial.available() > 0) {
      char c = Serial.read();
      if (c == m_delimeter) {
        m_callback( clean(m_buffer) );
        if (m_echo) 
          sendEcho(m_buffer);
        m_buffer = String();
      } else
        m_buffer += c;
    }
  }
  void send(const String &message) {
    Serial.print(message + m_delimeter);
  }
  void sendEcho(const String &message) {
    send("Echo: " + message);
  }
  void sendError(const String &message) {
    send("Error: " + message);
  }
private:
  bool m_echo;
  long m_baud;
  ReceivedCallback m_callback;
  const char m_delimeter = '\n';
  String m_buffer;
};

#endif