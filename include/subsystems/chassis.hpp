#pragma once

#include "main.h"

namespace subsytems {
  namespace chassis {

    ////
    // motors, sensors, etc

    // motors
    extern pros::Motor m_front_l;
    extern pros::Motor m_front_r;
    extern pros::Motor m_back_l;
    extern pros::Motor m_back_r;



    ////
    // control functions

    // move voltage (separate left and right)
    void move_voltage(int l, int r);

    // move voltage (same left/right)
    void move_voltage(int val);
  }
}