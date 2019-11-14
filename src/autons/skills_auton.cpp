#include "main.h"
#include "macros.hpp"
#include "subsystems/lift.hpp"
#include "subsystems/angler.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/intake.hpp"
#include "autons.hpp"

using namespace subsystems;

void skills_auton() {

  int start_time = pros::millis();

  // tare orientation
  chassis::tare_orientation(0 * units::DEGREES);


  // stack----------------------------------------------------------------------

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

  // rotate to deposit
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

  // back out
  chassis::move_by(-10 * units::INCHES, 1000, 12000, 6500);


  // first tower----------------------------------------------------------------

  // rotate
  chassis::rotate_to(-260 * units::DEGREES, 4000, 6000);

  // re-align
  chassis::move_voltage(-5500);
  pros::delay(1000);
  chassis::move_voltage(0);
  pros::delay(100);

  // reset orientation and position
  chassis::tare_orientation(90 * units::DEGREES);
  chassis::tare_position();

  // move to cube
  chassis::move_to(32 * units::INCHES, 3000);
  pros::delay(100);
  chassis::hold();

  // get tray in desired position
  angler::m_motor.move_absolute(290, 100);
  while (fabs(angler::m_motor.get_position() - 320) >= 3) pros::delay(10);

  // intake cube
  macros::notify(macros::CODE_INTAKE_TOWER);
  chassis::move_to(40 * units::INCHES, 1000, 4000);
  chassis::move_to(36 * units::INCHES, 1000, 4000);
  pros::delay(100);

  // lift cube and place in tower
  macros::notify(macros::CODE_INTERRUPT);
  lift::goto_sync(lift::POS_HIGH_TOWER);
  chassis::move_to(41 * units::INCHES, 2000, 4000, 1000);
  pros::delay(20);
  intake::move_voltage(-10000);
  pros::delay(700);
  intake::hold();


  // second tower---------------------------------------------------------------

  // back out
  chassis::move_to(41 * units::INCHES);

  // rotate to second tower cube & reset lift
  chassis::rotate_by(-90 * units::DEGREES);
  chassis::move_by(-6 * units::INCHES);
  lift::goto_sync(lift::POS_MIN);

  // intake cube
  macros::notify(macros::CODE_INTAKE_TOWER);
  chassis::move_by(8 * units::INCHES, 1000, 4000);

  // realign on the wall
  chassis::move_voltage(-5500);
  pros::delay(2000);
  chassis::tare_orientation(0 * units::DEGREES);
  chassis::move_by(10 * units::INCHES);

  // go to second tower
  chassis::rotate_to(-67 * units::DEGREES);
  chassis::tare_position();
  chassis::move_to(24 * units::INCHES, 4000);

  // lift cube & place in tower
  macros::notify(macros::CODE_INTERRUPT);
  pros::delay(20);
  lift::goto_sync(lift::POS_LOW_TOWER);
  chassis::move_to(33 * units::INCHES, 1000);
  pros::delay(20);
  intake::move_voltage(-8000);
  pros::delay(500);
  intake::hold();


  // third tower----------------------------------------------------------------

  // back out & put lift down
  chassis::move_to(26 * units::INCHES, 1000);
  lift::goto_sync(lift::POS_MIN);

  // rotate to third tower cube & reset position
  chassis::rotate_by(66 * units::DEGREES);
  chassis::tare_position();

  // move to cube
  chassis::move_to(24.5 * units::INCHES, 4500);

  // // intake cube
  // macros::notify(macros::CODE_INTAKE_TOWER);
  // chassis::move_to(30.5 * units::INCHES, 2000, 4000, 1000);
  // intake::hold();
  //
  // // go to third tower
  // chassis::move_to(21 * units::INCHES, 1000);
  // chassis::rotate_by(20 * units::DEGREES, 1500);
  //
  // // lift cube & place in tower
  // macros::notify(macros::CODE_INTERRUPT);
  // lift::goto_sync(lift::POS_LOW_TOWER);
  // chassis::move_by(5 * units::INCHES);
  // pros::delay(20);
  // intake::move_voltage(-8000);
  // pros::delay(300);
  // intake::hold();
  //
  // // back out
  // chassis::move_by(-11 * units::INCHES);
  // chassis::hold();


  // second stack---------------------------------------------------------------

  // rotate to cubes
  // chassis::rotate_by(-20 * units::DEGREES);
  // lift::goto_sync(lift::POS_MIN);
  // chassis::tare_orientation();
  angler::m_motor.move_absolute(0, 100);
  //
  // // start intake and move forward, grabbing cubes
  intake::move_voltage(12000);
  chassis::move_to(85 * units::INCHES, 6000, 4000, 3000, 3 * units::INCHES, 2500, 3 * units::INCHES);
  pros::delay(600);
  intake::hold();
  pros::delay(200);

  // rotate to goal
  chassis::rotate_to(15 * units::DEGREES, 3000, 8000);
  pros::delay(200);
  intake::move_voltage(-4200);
  pros::delay(285);
  intake::hold();

  // move to goal
  chassis::move_by(12 * units::INCHES, 800, 10000, 2500, 6 * units::INCHES, 1000, 8 * units::INCHES);
  pros::delay(10);
  // chassis::move_voltage(0, 5800);
  // pros::delay(280);
  // chassis::move_voltage(0, 0);
  // pros::delay(100);
  chassis::hold();

  // dump load
  intake::move_voltage(-1500);
  t = pros::millis();
  while (angler::pos > angler::POS_DEPOSIT + 8 * units::DEGREES && pros::millis() - t < 2500) {
    angler::update_auto_deposit(true);
    pros::delay(10);
  }
  intake::move_voltage(0);

  // make sure load is fully in place
  chassis::move_by(3 * units::INCHES, 400, true, 4000);

  // back out
  chassis::move_by(-10 * units::INCHES, 1000, 12000, 6500);


  // fourth tower---------------------------------------------------------------

  // rotate
  chassis::rotate_to(180 * units::DEGREES, 4000, 6000);

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
  angler::m_motor.move_absolute(290, 100);
  while (fabs(angler::m_motor.get_position() - 320) >= 3) pros::delay(10);

  // intake cube
  macros::notify(macros::CODE_INTAKE_TOWER);
  chassis::move_to(42 * units::INCHES, 1000, 4000);
  chassis::move_to(38 * units::INCHES, 1000, 4000);
  pros::delay(600);

  // lift cube and place in tower
  lift::goto_sync(lift::POS_HIGH_TOWER);
  chassis::move_to(44 * units::INCHES, 2000, 4000, 1000);
  macros::notify(macros::CODE_INTERRUPT);
  pros::delay(20);
  intake::move_voltage(-6000);
  pros::delay(500);
  intake::hold();


  // fifth tower----------------------------------------------------------------

  // back out
  chassis::move_by(70 * units::INCHES);

  // rotate to fifth tower cube & reset lift
  chassis::rotate_by(90 * units::DEGREES);
  chassis::move_by(-6 * units::INCHES);
  lift::goto_sync(lift::POS_MIN);

  // intake cube
  macros::notify(macros::CODE_INTAKE_TOWER);
  chassis::move_by(10 * units::INCHES, 1000, 4000);

  // realign on the wall
  chassis::move_voltage(-5500);
  pros::delay(2000);
  chassis::tare_orientation(0 * units::DEGREES);
  chassis::move_by(10 * units::INCHES);

  // go to fifth tower
  chassis::rotate_to(30 * units::DEGREES);
  chassis::tare_position();
  chassis::move_to(24 * units::INCHES, 4000);

  // lift cube & place in tower
  lift::goto_sync(lift::POS_LOW_TOWER);
  chassis::move_to(30 * units::INCHES, 1000);
  macros::notify(macros::CODE_INTERRUPT);
  pros::delay(20);
  intake::move_voltage(-6000);
  pros::delay(500);
  intake::hold();

}
