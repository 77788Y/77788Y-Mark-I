#pragma once

#include "main.h"

namespace subsystems {
  namespace intake {

    ////
    // motors, sensors, etc

    // motor
    extern pros::Motor m_left;
    extern pros::Motor m_right;



    ////
    // control functions

    // move voltage
    void move_voltage(int val);

    // hold position
    void hold();
  }
}