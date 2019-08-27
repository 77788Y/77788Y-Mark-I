#include "subsystems/chassis.hpp"

namespace subsytems {
  namespace chassis {

    ////
    // motors, sensors, etc
    
    // motors
    pros::Motor m_front_l (1 , pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
    pros::Motor m_front_r (10, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
    pros::Motor m_back_l  (11, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
    pros::Motor m_back_r  (20, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);



    ////
    // control functions

    // move voltage (separate left and right)
    void move_voltage(int l, int r) {
      m_front_l.move_voltage(l);
      m_front_r.move_voltage(r);
      m_back_l.move_voltage(l);
      m_back_r.move_voltage(r);
    }

    // move voltage (same left/right)
    void move_voltage(int val) {
      move_voltage(val, val);
    }
  }
}