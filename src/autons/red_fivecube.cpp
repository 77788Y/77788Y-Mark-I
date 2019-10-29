#include "main.h"
#include "subsystems/lift.hpp"
#include "subsystems/angler.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/intake.hpp"
#include "autons.hpp"

using namespace subsystems;

void red_fivecube() {

  // tare orientation
  chassis::tare_orientation(0);

  // start intake and move forward, grabbing cubes
  intake::move_voltage(12000);
  chassis::move_by(35 * units::INCHES, 3000, 5000);
  pros::delay(700);
  intake::hold();

  // back out
  chassis::move_to(16 * units::INCHES, 2000, 6500, 2500, 6 * units::INCHES, 0, 8 * units::INCHES);

  // rotate
  chassis::rotate_to(-135 * units::DEGREES, 2000, 6000);

  // make sure cubes are at the bottom of the intake
  intake::move_voltage(-3000);
  pros::delay(700);
  intake::hold();

  // move to goal
  chassis::move_by(10 * units::INCHES, 2000, 6500, 2500, 6 * units::INCHES, 0, 8 * units::INCHES);

  // dump load
  intake::move_voltage(-1000);
  while (angler::pos > angler::POS_DEPOSIT + 8 * units::DEGREES) {
    angler::update_auto_deposit(true);
    pros::delay(10);
  }
  intake::move_voltage(0);

  // make sure load is fully in place
  chassis::move_by(6 * units::INCHES, 800, true, 5000);
  subsystems::angler::move_voltage(-12000);
  pros::delay(675);
  subsystems::angler::hold();

  // back out
  chassis::move_by(-15 * units::INCHES, 1000);
}
