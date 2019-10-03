#pragma once

#include "main.h"
#include "lib/units.hpp"

namespace subsystems {
  namespace angler {


    ////
    // constants

    // position
    const units::Angle POS_RETRACTED = 136 * units::DEGREES;
    const units::Angle POS_DEPOSIT = 90 * units::DEGREES;

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
    void update_auto_deposit();

    // hold position
    void hold();
  }
}