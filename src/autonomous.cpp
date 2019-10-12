#include "main.h"
#include "subsystems/lift.hpp"
#include "subsystems/angler.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/chassis_auton.hpp"
#include "subsystems/intake.hpp"
#include "autons.hpp"

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


void autonomous() {

  flip_out();

  // red_fivecube();
  // blue_fivecube();
  red_wide_zone();
  // blue_wide_zone();
}
