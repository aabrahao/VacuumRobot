#include <RoboClaw.h>

#include <PWMServo.h>
#include "SerialPort.h"
#include "Gpio.h"
#include "SkidSteerDrive.h"

///////////////////////////////////////////////////
// Definitions

#define COMPUTER_BAUD 115200

#define LEDBAR_PIN 26

#define SERVO_PIN 5
#define SERVO_HOME 180
#define SERVO_MIN 900
#define SERVO_MAX 2100

#define MOTOR_DRIVER_SERIAL Serial8
#define MOTOR_DRIVER_BAUD 38400

// Serial Port with embedded computer

void messageReceivedCallback(const String &message);
SerialPort computer(COMPUTER_BAUD, messageReceivedCallback);

// Hardware interfaces
Gpio led(LED_BUILTIN);
Gpio ledbar(LEDBAR_PIN);
PWMServo servo;

// Power Train
SkidSteerDrive drive(&MOTOR_DRIVER_SERIAL);

///////////////////////////////////////////////////
// Arduino 

void setup() {
  computer.setup();
  led.setup();
  ledbar.setup();
  servo.attach(SERVO_PIN, SERVO_MIN, SERVO_MAX);
  drive.begin(MOTOR_DRIVER_BAUD);
  reset();
}

void loop() {
  computer.update();
}

///////////////////////////////////////////////////
// Callbacks

void messageReceivedCallback(const String &message) {
  auto action = command(message);
  if (action == "drive") {
    int qpps_left = argumentInt(message, 1);
    int qpps_right = argumentInt(message, 2);
    drive.speed(qpps_left, qpps_right);
  } 
  else if (action == "halt") {
    drive.halt();
  } 
  else if (action == "camera") {
    int angle = argumentInt(message, 1);
    servo.write(angle);
  } 
  else if (action == "light") {
    bool on = argumentBool(message, 1);
    if (on)
      ledbar.on();
    else
      ledbar.off();
  } 
  else if (action == "reset") {
    reset();
  }
  else if (action == "info") {
    computer.send( info() );
  } 
  else if (action == "help") {
    computer.send( help() );
  } 
  else if (action == "echo") {
    bool on = argumentBool(message, 1);
    if (on)
      computer.setEcho(true);
    else
      computer.setEcho(false);
  }
  else if (action == "test") {
    bool on = argumentBool(message, 1);
    if (on)
      led.on();
    else
      led.off();
  }
  else {
    computer.sendError("opps, '" + message + "' command not found!");
  }
}

///////////////////////////////////////////////////
// Info

String info(void) {
  String s = "Vaccum robot<br>"
             "Firmware version 0.0.1<br>"
             "Applied Research Center<br>"
             "Florida International University<br>"
             "Anthony Abrahao <aabrahao@fiu.edu><br>"
             "Cosme Vasco <cvasco@fiu.edu><br>"
             "Miami, 2025"; 
  return s;
}

String help(void) {
  String s = "drive left right: signed velocities from -127 to 127<br>"
             "halt: stop motor<br>"
             "camera angle: aim front camera at angle in degrees<br>"
             "light on: turn front camera light on (1) and off (0)<br>"
             "reset: restore initial conditions<br>"
             "info: send firmware information<br>"
             "help: send defined commands<br>"
             "echo on: turn message echo on (1) and off (0)<br>"
             "test on: turn microcontroller builtin led on (1) and off (0)<br>";
  return s;
}

void reset(void) {
    drive.halt();
    servo.write(SERVO_HOME);
    ledbar.off();
    led.off();
    computer.setEcho(false);
}

