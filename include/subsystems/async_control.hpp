#pragma once

#include "main.h"
#include "subsystems/angler.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/lift.hpp"
#include <memory>

namespace subsystems {


  // update controllers
  void update_controllers(void* params) {

    while (true) {

      // sensors
      angler::sensors_update();
      lift::sensors_update();
      chassis::update_vars();

      pros::delay(10);
    }
  }


  // reference to controller task
  inline std::unique_ptr<pros::Task> task;

}