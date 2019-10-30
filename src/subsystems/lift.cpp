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

    // move voltage (same left/right)
    void move_voltage(int val) {
      if (m_motor.get_brake_mode() != pros::E_MOTOR_BRAKE_COAST) m_motor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
      m_motor.move_voltage(val);
    }


    // tell async controller to update its target
    void goto_async(units::Angle pos) {

      angle_target = pos;
      task->notify_ext(1, NOTIFY_ACTION_OWRITE, NULL);
    }


    // goto syncronous
    bool goto_sync(units::Angle pos, units::Time timeout) {

      goto_async(pos);
      return wait_for_settle(timeout);
    }


    // wait until controller reaches target
    bool wait_for_settle(units::Time timeout, units::Angle threshold) {

      // setup interrupt variables
      units::Time interrupt_time = timeout < 0 ? timeout : pros::millis() + timeout;
      units::Angle start_target = angle_target;

      // keep checking until interrupted
      while ((pros::millis() < interrupt_time || interrupt_time < 0) && angle_target == start_target) {

        // if settled, return true
        if (fabs(angle_target - pos) <= threshold) return true;
        pros::delay(10);
      }

      // if interrupted before being settled, return false
      return false;
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
