# VacuumRobot

Hanford vacuum robot  
Applied Research Center  
Florida International University  
Anthony Abrahao <aabrahao@fiu.edu>  
Cosme Vasco <cvasco@fiu.edu>  
Miami, 2025   

# Applicatons

- **Bridge**: Raspiberry Pi C++ code
- **Firmware**: Microcontroller code

# Firmware dependencies

The firmware requires the following libraries:

- PWMServer
- RoboClaw

To install the RoboClaw library for use with a Teensy board in the Arduino IDE, follow these steps:

**Download the RoboClaw Arduino Library:**

Obtain the RoboClaw Arduino library as a .zip file. This is typically available from the Basicmicro resources website.

**Open the Arduino IDE:**

Launch the Arduino Integrated Development Environment on your computer.

**Add the .Zip Library:**

- In the Arduino IDE, navigate to the top menu.
- Click on Sketch.
- Select Include Library.
- Choose Add .Zip Library....

**Select the Downloaded Library:**

A dialog box will appear. Browse to the location where you saved the downloaded RoboClaw library .zip file, select it, and then click Open.

**Verification:**

The Arduino IDE will now add the library to your installation. You can verify the installation by going to Sketch > Include Library again and checking if "RoboClaw" appears in the list of available libraries.

# Compiling Bridge

```bash
cd Bridge/SerialBridge
mkdir build
cd build
cmake ..
./serial_bridge
```


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

