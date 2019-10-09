#include "main.h"
#include "subsystems/lift.hpp"
#include "subsystems/angler.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/chassis_auton.hpp"
#include "subsystems/intake.hpp"
#include "autons.hpp"

void blue_fivecube(){
  subsystems::chassis::tare_orientation(180);
  subsystems::intake::move_voltage(12000);
  move_dist(32 * units::INCHES);
  pros::delay(500);
  move_dist(12 * units::INCHES, -1, false);
  subsystems::intake::hold();

  rotate(270 * units::DEGREES);

  move_dist(20 * units::INCHES);
  subsystems::angler::update_auto_deposit();

  move_dist(-15 * units::INCHES);
}
