#include "subsystems/lift.hpp"
#include "lib/generic.hpp"
#include <iostream>
#include <cmath>
#include <memory>

namespace subsystems {
  namespace lift {

    ////
    // motors, sensors, etc

    // motor
    pros::Motor m_motor (6, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);



    ////
    // update functions

    // update sensors
    void sensors_update() {
      pos = ((m_motor.get_position() / 5) * units::DEGREES) + POS_MIN;
    }



    ////
    // control functions

    double kp = 50000;
    double td = 10000;

    // move voltage (same left/right)
    void move_voltage(int val) {
      if (m_motor.get_brake_mode() != pros::E_MOTOR_BRAKE_COAST) m_motor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
      m_motor.move_voltage(val);
    }


    // update PD controller
    units::Angle prev_pos = 0;
    units::Time prev_time = pros::millis();
    double prev_pd = 0;
    double pd_update() {

      units::Time delta_t = pros::millis() - prev_time;

      // calculate p
      double error = angle_target - pos;
      double p = error * kp;

      // calculate d
      double prev_error = pos - prev_pos;
      double deriv = (prev_error - error) / delta_t;
      double d = deriv * kp / td;

      // update prev error and time
      prev_pos = pos;
      prev_time = pros::millis();

      // combine
      double pd = p + d;

      // scale
      pd = generic::clamp(pd, -12000, 12000) + 5000 * cos(pos);
      if (fabs((pd - prev_pd) / delta_t ) > 1000) pd = generic::clamp(pd, prev_pd - 1000, prev_pd + 1000);
      if (pos <= POS_MIN + 8 * units::DEGREES && angle_target <= POS_MIN + 8 * units::DEGREES) pd = 0;

      // move motor and return
      prev_pd = pd;
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
