#include <iostream>
#include "Serial.h"

void info(void) {
    std::string s{
        "Vaccum robot\n"
        "===========================\n"
        "Firmware version 0.0.1\n"
        "Applied Research Center\n"
        "Florida International University\n"
        "Anthony Abrahao <aabrahao@fiu.edu>\n"
        "Cosme Vasco <cvasco@fiu.edu>\n"
        "Miami, 2025\n" 
    }; 
    std::cout << s << std::endl;
}

void receivedCallback(const std::string &message) {
        std::cout << "Firmware replied: " << message << std::endl;
}

int main(int argc, char *argv[]) {
    Serial serial("/dev/ttyACM0", receivedCallback);
    info(); 
    serial.write("reset");
    std::string cmd;
    while (true) {
        std::cout << "?> ";
        std::getline(std::cin, cmd);
        if (cmd == "bye")
            break;
        serial.write(cmd);
    }
    serial.write("reset");
    std::cout << "Bye!" << std::endl;
    return 0;
}
