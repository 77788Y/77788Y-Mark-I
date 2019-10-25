#include "main.h"
#include "subsystems/lift.hpp"
#include "subsystems/angler.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/chassis_auton.hpp"
#include "subsystems/intake.hpp"
#include "autons.hpp"

void red_fivecube() {

  // tare orientation
  subsystems::chassis::tare_orientation(0);

  // start intake and move forward, grabbing cubes
  subsystems::intake::move_voltage(12000);
  move_dist(35 * units::INCHES, 3000, true, tuning_params_slow);
  pros::delay(700);
  subsystems::intake::hold();

  // back out
  move_dist(16 * units::INCHES, 2000, false, tuning_params_default_all_cubes);

  // rotate
  rotate(-135 * units::DEGREES, 2000);

  // make sure cubes are at the bottom of the intake
  subsystems::intake::move_voltage(-3000);
  pros::delay(700);
  subsystems::intake::hold();

  // move to goal
  move_dist(10 * units::INCHES, 2000);

  // dump load
  subsystems::intake::move_voltage(-1000);
  while (subsystems::angler::pos > subsystems::angler::POS_DEPOSIT + 8 * units::DEGREES) {
    subsystems::angler::update_auto_deposit(true);
    pros::delay(10);
  }
  subsystems::intake::hold();

  // make sure load is fully in place
  move_dist(6 * units::INCHES, 800, true, tuning_params_slow);
  subsystems::angler::move_voltage(-12000);
  pros::delay(675);
  subsystems::angler::hold();

  // back out
  move_dist(-15 * units::INCHES, 1000);
}
