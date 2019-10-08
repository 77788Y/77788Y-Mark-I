#pragma once

#include "main.h"
#include "lib/units.hpp"
#include <memory>

namespace subsystems {
  namespace chassis {

    ////
    // constants
    const units::Distance WHEEL_RADIUS = (2.75 / 2) * units::INCHES;
    const units::Distance CHASSIS_DIAM = 11.5 * units::INCHES;



    ////
    // motors, sensors, etc

    // motors
    extern pros::Motor m_front_l;
    extern pros::Motor m_front_r;
    extern pros::Motor m_back_l;
    extern pros::Motor m_back_r;



    ////
    // variables

    // position
    inline units::Distance dist_l = 0;
    inline units::Distance dist_r = 0;
    inline units::Distance dist_avg = 0;
    inline units::Angle orientation = 0;



    ////
    // update functions

    // variables
    void update_vars();



    ////
    // control functions

    // move voltage (separate left and right)
    void move_voltage(int l, int r);

    // move voltage (same left/right)
    void move_voltage(int val);

    // reset encoders
    void tare();



    ////
    // async

    // mutex
    inline pros::Mutex control_mutex;
  }
}