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
  pros::delay(600);
  intake::hold();

  // turn to cube
  chassis::rotate_to(21 * units::DEGREES, 3000, 6000);

  //go to intake cube
  intake::move_voltage(12000);
  chassis::move_by(9 * units::INCHES, 3000, 4000);
  pros::delay(269);

  // back out
  chassis::move_by(-24 * units::INCHES, 5000, 8000, 3000, 2 * units::INCHES, 1500, 8 * units::INCHES);
  intake::hold();

  // rotate
  pros::delay(200);
  chassis::rotate_to(-138 * units::DEGREES, 3000, 8000);
  pros::delay(200);
  intake::move_voltage(-4200);
  pros::delay(285);
  intake::hold();

  // move to goal
  chassis::move_by(9 * units::INCHES, 800, 10000, 2500, 6 * units::INCHES, 1000, 8 * units::INCHES);
  pros::delay(10);
  chassis::move_voltage(0, 5800);
  pros::delay(280);
  chassis::move_voltage(0, 0);
  pros::delay(100);
  chassis::hold();

  // dump load
  intake::move_voltage(-1500);
  int t = pros::millis();
  while (angler::pos > angler::POS_DEPOSIT + 8 * units::DEGREES && pros::millis() - t < 2500) {
    angler::update_auto_deposit(true);
    pros::delay(10);
  }
  intake::move_voltage(0);

  // make sure load is fully in place
  chassis::move_by(3 * units::INCHES, 400, true, 4000);

  // move tray
  angler::m_motor.move_absolute(480, 100);
  pros::delay(850);

  // back out
  chassis::move_by(-10 * units::INCHES, 1000, 12000, 6500);

  // rotate
  chassis::rotate_to(-260 * units::DEGREES, 4000, 6000);

  // re-align
  chassis::move_voltage(-5500);
  pros::delay(2000);
  chassis::move_voltage(0);
  pros::delay(400);

  // reset orientation and position
  chassis::tare_orientation(90 * units::DEGREES);
  chassis::tare_position();

  // move to cube
  chassis::move_to(34 * units::INCHES, 3000);
  pros::delay(300);
  chassis::hold();

  // get tray in desired position
  angler::m_motor.move_absolute(320, 100);
  while (fabs(angler::m_motor.get_position() - 320) >= 3) pros::delay(10);

  // intake cube
  intake::move_voltage(6000);
  chassis::move_to(42 * units::INCHES, 1000, 4000);
  intake::hold();
  chassis::move_to(38 * units::INCHES, 1000, 4000);
  pros::delay(300);

  // lift cube and place in tower
  lift::goto_sync(lift::POS_HIGH_TOWER);
  chassis::move_to(44 * units::INCHES, 2000, 4000, 1000);
  intake::move_voltage(-6000);
  pros::delay(500);
  intake::hold();

  // back out
  chassis::move_to(40 * units::INCHES);

  // rotate to second tower cube & reset lift
  chassis::rotate_by(-90 * units::DEGREES);
  chassis::move_by(-6 * units::INCHES);
  lift::goto_sync(lift::POS_MIN);

  // intake cube
  intake::move_voltage(6400);
  chassis::move_by(6 * units::INCHES, 1000, 4000);
  intake::move_voltage(0);

  // realign on the wall
  chassis::move_voltage(-5500);
  pros::delay(2000);
  chassis::tare_orientation(0 * units::DEGREES);
  chassis::move_by(10 * units::INCHES);

  // go to second tower
  chassis::rotate_to(-62 * units::DEGREES);
  chassis::tare_position();
  chassis::move_to(24 * units::INCHES, 4000);

  // lift cube & place in tower
  lift::goto_sync(lift::POS_LOW_TOWER);
  chassis::move_to(29 * units::INCHES, 1000);
  intake::move_voltage(-6000);
  pros::delay(500);
  intake::hold();

  // next
  chassis::move_to(25 * units::INCHES, 1000);
  lift::goto_sync(lift::POS_MIN);
  chassis::rotate_by(63.5 * units::DEGREES);
  chassis::tare_position();
  chassis::move_to(24 * units::INCHES, 4000);
  intake::move_voltage(6000);
  chassis::move_to(30.5 * units::INCHES, 2000, 4000, 1000);
  intake::hold();
  chassis::move_to(22 * units::INCHES, 1000);
  chassis::rotate_by(22 * units::DEGREES, 1000);
  lift::goto_sync(lift::POS_LOW_TOWER);
  chassis::move_by(5 * units::INCHES);
  intake::move_voltage(-6000);
  pros::delay(500);
  intake::hold();

}
