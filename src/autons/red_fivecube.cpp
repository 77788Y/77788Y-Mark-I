#include "main.h"
#include "subsystems/lift.hpp"
#include "subsystems/angler.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/chassis_auton.hpp"
#include "subsystems/intake.hpp"
#include "autons.hpp"

SineTuningParams tuning_params_slow = {
  .min_accel = 3000,
  .min_decel = 6000,
  .max_vol = 3000,
  .dist_accel = 5 * units::INCHES,
  .dist_decel = 5 * units::INCHES
};

void flip_out(){
  while (subsystems::angler::pos > subsystems::angler::POS_RETRACTED - 5 *units::DEGREES){
    subsystems::angler::move_voltage(12000);
  }
  while (subsystems::angler::pos < subsystems::angler::POS_RETRACTED){
    subsystems::angler::move_voltage(-12000);
  }
  subsystems::angler::hold();
  while (subsystems::lift::pos < subsystems::lift::POS_MIN + 20 * units::DEGREES){
    subsystems::lift::move_voltage(12000);
  }
  while (subsystems::lift::pos > subsystems::lift::POS_MIN){
    subsystems::lift::move_voltage(-100);
  }
  subsystems::lift::hold();
}

void red_fivecube(){
  flip_out();
  subsystems::intake::move_voltage(12000);
  move_dist(35 * units::INCHES, 3000, true, tuning_params_slow);
  pros::delay(700);
  subsystems::intake::hold();
  move_dist(17 * units::INCHES, 2000, false, tuning_params_default_all_cubes);

  rotate(-135 * units::DEGREES, 2000);
  subsystems::intake::move_voltage(-2500);
  pros::delay(700);
  subsystems::intake::hold();

  move_dist(11 * units::INCHES, 2000);
  while (subsystems::angler::pos > subsystems::angler::POS_DEPOSIT + 8 * units::DEGREES) {
    subsystems::angler::update_auto_deposit(true);
    pros::delay(10);
  }
  move_dist(6 * units::INCHES, 800);
  subsystems::angler::move_voltage(-12000);
  pros::delay(675);
  subsystems::angler::hold();
  move_dist(-15 * units::INCHES, 1000);
}
