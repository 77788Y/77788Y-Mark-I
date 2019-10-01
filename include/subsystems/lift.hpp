#pragma once

#include "main.h"
#include "lib/units.hpp"

namespace subsystems {
  namespace lift {


    ////
    // macros

    // positions
    const units::Angle POS_MAX = 45 * units::DEGREES;
    const units::Angle POS_MIN = -45 * units::DEGREES;

    ////
    // motors, sensors, etc

    // motor
    extern pros::Motor m_motor;


    ////
    // control variables

    // current position
    inline units::Angle pos = 0;

    // target positon
    inline units::Angle angle_target = 0;

    // proportional constant
    inline double kp = 0;

    // time-derivative constant
    inline double td;



    ////
    // control functions

    // move voltage
    void move_voltage(int val);

    // update pd controller
    double pd_update();

    // hold position
    void hold();
  }
}