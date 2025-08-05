#ifndef __ROBO_CLAW_MOTOR_H__
#define __ROBO_CLAW_MOTOR_H__

#include <RoboClaw.h>

class RoboClawMotor {
public:
    RoboClawMotor(RoboClaw &driver, unsigned char address, uint8_t motor) 
    : m_driver(driver), 
      m_address(address), 
      m_motor(motor) { 

      }
    // Speed -127 to 127
    void speed(int s) {
      if (m_motor == 1) {
        if (s < 0)
          m_driver.BackwardM1(m_address, abs(s));
        else
          m_driver.ForwardM1(m_address, s);
      }
      else if (m_motor == 2){
        if (s < 0)
          m_driver.BackwardM2(m_address, abs(s));
        else
          m_driver.ForwardM2(m_address, s);
      }
    }

private:
    RoboClaw &m_driver;
    unsigned char m_address;
    uint8_t m_motor;
};

#endif