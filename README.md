# VacuumRobot

Vacuum robot for Hanford double shell thanks annulus

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

# Firmware commands

**Type:** 

- drive left right: velocities from -127 to 127
- halt: stop motor
- camera angle: aim front camera at angle in degrees
- light on/off: turn front camera light on (1) and off (0)
- reset: restore initial conditions
- info: send firmware information
- help: send defined commands
- echo on/off: turn message echo on (1) and off (0)
- test on/off: turn microcontroller builtin led on (1) and off (0)

**Examples:**

```bash
drive 64 -64
halt
camera 45
light 1
light 0
test 1
test 0
echo 1
echo 0
reset
```
