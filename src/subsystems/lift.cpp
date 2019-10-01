#include "subsystems/lift.hpp"
#include <cmath>
#include <memory>

namespace subsystems {
  namespace lift {

    ////
    // motors, sensors, etc

    // motor
    pros::Motor m_motor (6, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);



    ////
    // update functions

    // update sensors
    void sensors_update() {
      pos = m_motor.get_position() * units::DEGREES;
    }



    ////
    // control functions

    // move voltage (same left/right)
    void move_voltage(int val) {
      if (m_motor.get_brake_mode() != pros::E_MOTOR_BRAKE_COAST) m_motor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
      m_motor.move_voltage(val);
    }


    // update PD controller
    units::Angle prev_pos = 0;
    units::Time prev_time = pros::millis();
    double pd_update() {

      // calculate p
      double error = angle_target - pos;
      double p = error * kp;

      // calculate d
      double prev_error = pos - prev_pos;
      double deriv = (prev_error - error) / (pros::millis() - prev_time);
      double d = deriv * kp / td;

      // update prev error and time
      prev_pos = pos;
      prev_time = pros::millis();

      // combine
      double pd = p + d;

      // move motor and return
      move_voltage(pd);
      return pd;
    }



    // hold position
    void hold() {
      if (m_motor.get_brake_mode() != pros::E_MOTOR_BRAKE_HOLD) {
        m_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        m_motor.move_velocity(0);
      }
    }
  }
}
