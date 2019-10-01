#pragma once

#include "main.h"

namespace subsytems {
  namespace lift {

    ////
    // motors, sensors, etc

    // motor
    extern pros::Motor m_motor;



    ////
    // control functions

    // move voltage (same left/right)
    void move_voltage(int val);

    // hold position
    void hold();
  }
}