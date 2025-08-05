# VacuumRobot

Vacuum robot for Hanford double shell thanks annulus

**Applied Research Center**  
**Florida International University**  
Anthony Abrahao <aabrahao@fiu.edu>  
Cosme Vasco <cvasco@fiu.edu>
Miami, 2025   

# System

| **Application** | **Description**                |
|------------------|-------------------------------|
| **Bridge**       | Raspberry Pi C++ code         |
| **Firmware**     | Microcontroller code          |

| **Component**         | **Specification**              |
|-----------------------|--------------------------------|
| **Microcontroller**   | Teensy 4.1                     |
| **Embedded Computer** | Raspberry Pi 5                 |
| **Operating System**  | Ubuntu Server 24.02            |

# Compiling Bridge

```bash
cd Bridge/SerialBridge
mkdir build
cd build
cmake ..
./bridge_serial
```

# Firmware commands

Please, type:

| **Command**       | **Description**                                                | **Values / Parameters**      |
|-------------------|----------------------------------------------------------------|-------------------------------|
| `drive left right`| Set motor velocities for left and right                        | Range: -127 to 127            |
| `halt`            | Stop the motor                                                 | None                          |
| `camera angle`    | Aim front camera to a specific angle                           | Angle in degrees              |
| `light on/off`    | Turn front camera light on or off                              | `1` = On, `0` = Off           |
| `reset`           | Restore system to initial conditions                           | None                          |
| `info`            | Send firmware information                                      | None                          |
| `help`            | Send list of defined commands                                  | None                          |
| `echo on/off`     | Enable or disable message echo                                 | `1` = On, `0` = Off           |
| `test on/off`     | Toggle microcontroller’s built-in LED                          | `1` = On, `0` = Off           |


Examples:

```
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

# Firmware dependencies

The firmware requires the following libraries:

- PWMServer
- RoboClaw

To install the RoboClaw library for use with a Teensy board in the Arduino IDE, follow these steps:

**Download the RoboClaw Arduino Library**

Obtain the RoboClaw Arduino library as a .zip file. This is typically available from the Basicmicro resources website.

**Open the Arduino IDE**

Launch the Arduino Integrated Development Environment on your computer.

**Add the .Zip Library**

- In the Arduino IDE, navigate to the top menu.
- Click on Sketch.
- Select Include Library.
- Choose Add .Zip Library....

**Select the Downloaded Library**

A dialog box will appear. Browse to the location where you saved the downloaded RoboClaw library .zip file, select it, and then click Open.

**Verification**

The Arduino IDE will now add the library to your installation. You can verify the installation by going to Sketch > Include Library again and checking if "RoboClaw" appears in the list of available libraries.

