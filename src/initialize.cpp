#include "main.h"
#include "macros.hpp"
#include "display.hpp"
#include "subsystems/async_control.hpp"
#include <memory>

void initialize() {

  // initialize subsystem controllers
  subsystems::task = std::make_shared<pros::Task>(pros::Task(subsystems::update_controllers, nullptr, "subsystems"));

  // initislize display
  display::init();
}

void disabled() {

}

void competition_initialize() {

}
