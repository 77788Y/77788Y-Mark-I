#pragma once

#include "main.h"
#include "lib/units.hpp"

namespace subsystems {
  namespace angler {


    ////
    // constants

    // position
    const units::Angle POS_RETRACTED = 137 * units::DEGREES;
    const units::Angle POS_LIFT = 137 * units::DEGREES;
    const units::Angle POS_DEPOSIT = 39 * units::DEGREES;

    ////
    // motors, sensors, etc

    // motor
    extern pros::Motor m_motor;



    ////
    // control functions

    inline units::Angle pos = POS_RETRACTED;

    // update sensors
    void sensors_update();

    // move voltage
    void move_voltage(int val);

    // update auto deposit
    void update_auto_deposit(bool speedy = false);

    // hold position
    void hold();
  }
}
