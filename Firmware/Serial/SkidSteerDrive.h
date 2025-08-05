#ifndef __SKID_STEER_DRIVE_H__
#define __SKID_STEER_DRIVE_H__

#include <RoboClaw.h>
#include "RoboClawMotor.h"

class SkidSteerDrive {
public:  
  SkidSteerDrive(HardwareSerial *serial, uint32_t timeout = 1000)
  : m_driver(serial, timeout),
    m_front_right(m_driver, 0x82, 1),
    m_front_left(m_driver, 0x82, 2),
    m_back_right(m_driver, 0x80, 2),
    m_back_left(m_driver, 0x80, 1) { 

  }
  void begin(long speed) {
    m_driver.begin(speed);
  }
  void speed(int qpps_left, int qpps_right) { 
    m_front_left.speed(qpps_left);
    m_back_left.speed(qpps_left);
    m_front_right.speed(qpps_right);
    m_back_right.speed(qpps_right);
  }
  void halt() {
    m_front_left.speed(0);
    m_back_left.speed(0);
    m_front_right.speed(0);
    m_back_right.speed(0);
  }
private:
  RoboClaw m_driver;
  RoboClawMotor m_front_right;
  RoboClawMotor m_front_left;
  RoboClawMotor m_back_right;
  RoboClawMotor m_back_left;
};

#endif