#include <iostream>
#include "Serial.h"

void info(void) {
    std::string s{
        "Vaccum robot\n"
        "Firmware version 0.0.1\n"
        "Applied Research Center\n"
        "Florida International University\n"
        "Anthony Abrahao <aabrahao@fiu.edu>\n"
        "Cosme Vasco <cvasco@fiu.edu>\n"
        "Miami, 2025\n" 
    }; 
    std::cout << s << std::endl;
}

void help(void) {
    std::string s {
        "===========================\n"
        "Firmware commands:\n"
        "drive left right: velocities from -127 to 127\n"
        "halt: stop motor\n"
        "camera angle: aim front camera at angle in degrees\n"
        "light on: turn front camera light on (1) and off (0)\n"
        "reset: restore initial conditions\n"
        "info: send firmware information\n"
        "help: send defined commands\n"
        "echo on: turn message echo on (1) and off (0)\n"
        "test on: turn microcontroller builtin led on (1) and off (0)\n"
        "\n"
        "===========================\n"
        "Examples:\n"
        "drive 64 -64\n"
        "halt\n"
        "camera 45\n"
        "light 1\n"
        "light 0\n"
        "test 1\n"
        "test 0\n"
        "echo 1\n"
        "echo 0\n"
        "reset\n"
    };
    std::cout << s << std::endl;
}

class Reinterpretor {
public:
    void operator()(const std::string &message) const {
        std::cout << "Firmware replied: " << message << std::endl;
    }
};

int main(int argc, char *argv[]) {
    Serial serial("/dev/ttyACM0", Reinterpretor());
    info(); 
    help();
    serial.write("reset");
    std::string cmd;
    while (true) {
        std::cout << "?> ";
        std::getline(std::cin, cmd);
        if (cmd == "bye") {
            break;
        }
        serial.write(cmd);
    }
    serial.write("reset");
    std::cout << "Bye!" << std::endl;
    return 0;
}
