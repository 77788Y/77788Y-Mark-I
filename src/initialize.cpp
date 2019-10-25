#include "main.h"
#include "macros.hpp"
#include "subsystems/async_control.hpp"
#include <memory>

void initialize() {

  // initialize subsystem controllers
  subsystems::task = std::make_shared<pros::Task>(pros::Task(subsystems::update_controllers, nullptr, "subsystems"));

}

void disabled() {

}

void competition_initialize() {

}
