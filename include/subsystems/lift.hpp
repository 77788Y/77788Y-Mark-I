#pragma once

#include "main.h"
#include "lib/units.hpp"
#include <memory>

namespace subsystems {
  namespace lift {


    ////
    // macros

    // positions
    const units::Angle POS_MAX = 50 * units::DEGREES;
    const units::Angle POS_MIN = -31 * units::DEGREES;
  const units::Angle POS_LOW_TOWER = 21.5 * units::DEGREES;
    const units::Angle POS_HIGH_TOWER = 40 * units::DEGREES;


    ////
    // task

    // Task object
    inline std::unique_ptr<pros::Task> task = nullptr;

    // update function
    void task_update(void*);


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



    ////
    // control functions

    // move voltage
    void move_voltage(int val);

    // goto position
    void goto_async(units::Angle pos);
    bool goto_sync(units::Angle pos, units::Time timeout = -1);

    // wait until controller reaches target
    bool wait_for_settle(units::Time timeout = -1, units::Angle threshold = 5 * units::DEGREES);

    // hold position
    void hold();
  }
}
