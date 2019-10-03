#pragma once

#include "main.h"
#include "lib/units.hpp"

namespace subsystems {
  namespace lift {


    ////
    // macros

    // positions
    const units::Angle POS_MAX = 55 * units::DEGREES;
    const units::Angle POS_MIN = -31 * units::DEGREES;

    ////
    // motors, sensors, etc

    // motor
    extern pros::Motor m_motor;


    ////
    // update

    // sensors
    void sensors_update();


    ////
    // control variables

    // current position
    inline units::Angle pos = POS_MIN;

    // target positon
    inline units::Angle angle_target = pos;

    // proportional constant
    extern double kp;

    // time-derivative constant
    extern double td;



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