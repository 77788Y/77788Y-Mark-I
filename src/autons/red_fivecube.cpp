#include "main.h"
#include "subsystems/lift.hpp"
#include "subsystems/angler.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/intake.hpp"
#include "autons.hpp"

using namespace subsystems;

void red_fivecube() {

  int start_time = pros::millis();

  // tare orientation
  chassis::tare_orientation(0);

  // start intake and move forward, grabbing cubes
  intake::move_voltage(12000);
  pros::delay(10);
  intake::move_voltage(12000);
  pros::delay(10);
  intake::move_voltage(12000);
  pros::delay(10);
  intake::move_voltage(12000);
  pros::delay(10);
  intake::move_voltage(12000);
  chassis::move_to(36 * units::INCHES, 6350, 4000, 3000, 3 * units::INCHES, 2500, 3 * units::INCHES);
  pros::delay(300);
  intake::hold();

  // turn to cube
  chassis::rotate_to(23 * units::DEGREES, 3000, 6250);

  //go to intake cube
  intake::move_voltage(12000);
  chassis::move_by(9 * units::INCHES, 3000, 4000);

  // back out
  chassis::move_by(-26.5 * units::INCHES, 3000, 9500, 4000, 2 * units::INCHES, 5000, 14 * units::INCHES);
  intake::hold();

  // rotate
  pros::delay(300);
  chassis::rotate_to(-141 * units::DEGREES, 3000, 8000);
  pros::delay(200);
  intake::move_voltage(-4200);
  pros::delay(275);
  intake::hold();

  // move to goal
  chassis::move_by(6.25 * units::INCHES, 800, 10000, 2700, 6 * units::INCHES, 1000, 8 * units::INCHES);
  pros::delay(10);
  chassis::move_voltage(0, 5800);
  pros::delay(255);
  chassis::move_voltage(0, 0);
  pros::delay(100);
  chassis::hold();

  // dump load
  intake::move_voltage(-1500);
  while (angler::pos > angler::POS_DEPOSIT + 9 * units::DEGREES) {
    angler::update_auto_deposit(true);
    pros::delay(10);
  }
  intake::move_voltage(0);

  // make sure load is fully in place
  if (pros::millis() - start_time < 13750) chassis::move_by(1 * units::INCHES, 300, 4000);

  // back out
  chassis::move_by(-15 * units::INCHES, 1000, 12000, 6500);

}
