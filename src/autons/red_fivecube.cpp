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
  chassis::move_to(36 * units::INCHES, 6000, 4000);
  pros::delay(300);
  intake::hold();

  // turn to cube
  chassis::rotate_to(23 * units::DEGREES, 3000, 6000);

  //go to intake cube
  intake::move_voltage(12000);
  chassis::move_by(9 * units::INCHES, 3000, 4000);
  pros::delay(700);
  intake::hold();

  // back out
  chassis::move_by(-27 * units::INCHES, 5000, 8000, 2500, 4 * units::INCHES, 2000, 12 * units::INCHES);

  // rotate
  intake::move_voltage(-3000);
  pros::delay(300);
  intake::hold();
  chassis::rotate_to(-147.5 * units::DEGREES, 3000, 6000);

  // move to goal
  chassis::move_by(10.5 * units::INCHES, 2000, 6500, 2500, 6 * units::INCHES, 0, 8 * units::INCHES);

  // dump load
  intake::move_voltage(-2000);
  while (angler::pos > angler::POS_DEPOSIT + 8 * units::DEGREES) {
    angler::update_auto_deposit(true);
    pros::delay(10);
  }
  intake::move_voltage(0);

  // make sure load is fully in place
  chassis::move_by(6 * units::INCHES, 800, true, 2500);

  // back out
  chassis::move_by(-15 * units::INCHES, 1000);

}
