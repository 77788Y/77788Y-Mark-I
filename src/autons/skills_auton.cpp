#include "main.h"
#include "subsystems/lift.hpp"
#include "subsystems/angler.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/intake.hpp"
#include "autons.hpp"

using namespace subsystems;

void skills_auton() {

  int start_time = pros::millis();

  // tare orientation
  chassis::tare_orientation(0);

  // start intake and move forward, grabbing cubes
  intake::move_voltage(12000);
  chassis::move_to(36 * units::INCHES, 6000, 4000, 3000, 3 * units::INCHES, 2500, 3 * units::INCHES);
  pros::delay(300);
  intake::hold();

  // turn to cube
  chassis::rotate_to(23 * units::DEGREES, 3000, 6000);

  //go to intake cube
  intake::move_voltage(12000);
  chassis::move_by(9 * units::INCHES, 3000, 4000);
  pros::delay(269);

  // back out
  chassis::move_by(-26.5 * units::INCHES, 5000, 8000, 3000, 2 * units::INCHES, 1000, 14 * units::INCHES);
  intake::hold();

  // rotate
  pros::delay(500);
  chassis::rotate_to(-143 * units::DEGREES, 3000, 8000);
  pros::delay(200);
  intake::move_voltage(-4200);
  pros::delay(275);
  intake::hold();

  // move to goal
  chassis::move_by(6.25 * units::INCHES, 800, 10000, 2500, 6 * units::INCHES, 1000, 8 * units::INCHES);
  pros::delay(10);
  chassis::move_voltage(0, 5800);
  pros::delay(255);
  chassis::move_voltage(0, 0);
  pros::delay(100);
  chassis::hold();

  // dump load
  intake::move_voltage(-1500);
  while (angler::pos > angler::POS_DEPOSIT + 8 * units::DEGREES) {
    angler::update_auto_deposit(true);
    pros::delay(10);
  }
  intake::move_voltage(0);

  // make sure load is fully in place
  chassis::move_by(3 * units::INCHES, 400, true, 4000);

  // back out
  chassis::move_by(-12 * units::INCHES, 1000, 12000, 6500);

  // rotate
  chassis::rotate_to(-270 * units::DEGREES, 4000, 6000);

  // re-align
  chassis::move_voltage(-6000);
  pros::delay(1500);
  chassis::move_voltage(0);
  pros::delay(400);

  chassis::tare_orientation(90 * units::DEGREES);
  chassis::tare_position();
  chassis::move_to(34 * units::INCHES, 3000);
  pros::delay(300);
  chassis::hold();

  angler::m_motor.move_absolute(320, 100);
  while (fabs(angler::m_motor.get_position() - 320) >= 3) pros::delay(10);

  intake::move_voltage(6000);
  chassis::move_to(42 * units::INCHES, 1000, 4000);
  intake::move_voltage(0);
  chassis::move_to(38 * units::INCHES, 1000, 4000);
  pros::delay(300);

  lift::goto_sync(lift::POS_HIGH_TOWER);

  chassis::move_to(44 * units::INCHES, 2000, 4000, 1000);
  intake::move_voltage(-6000);
  pros::delay(500);
  intake::hold();
  chassis::move_to(40 * units::INCHES);

  chassis::rotate_to(69 * units::DEGREES);
  lift::goto_sync(lift::POS_MIN);

  intake::move_voltage(6000);
  chassis::move_by(6 * units::INCHES, 1000, 4000);
  intake::move_voltage(0);
  chassis::move_voltage(-8000);
  pros::delay(1500);
  chassis::tare_orientation(0 * units::DEGREES);
  chassis::move_by(10 * units::INCHES);

  chassis::rotate_to(-140 * units::DEGREES);
  chassis::move_by(40 * units::INCHES);


}
