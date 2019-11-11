#include "subsystems/angler.hpp"
#include <cmath>
#include <iostream>

namespace subsystems {
  namespace angler {

    ////
    // motors, sensors, etc

    // motor
    pros::Motor m_motor (2, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);



    ////
    // control functions

    // update sensors
    void sensors_update() {
      pos = -m_motor.get_position() * units::DEGREES * 3.0 / 35.0 + POS_RETRACTED;
    }

    // move voltage (same left/right)
    void move_voltage(int val) {
      if (m_motor.get_brake_mode() != pros::E_MOTOR_BRAKE_COAST) m_motor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
      m_motor.move_voltage(val);
    }

    // update auto deposit
    void update_auto_deposit(bool speedy) {
      if (pos < POS_DEPOSIT + 33 * units::DEGREES) move_voltage((pos - POS_DEPOSIT) * (speedy ? 15000.0 : 7250.0));
      else move_voltage(12000);
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
