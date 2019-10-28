// #include "main.h"
// #include "subsystems/lift.hpp"
// #include "subsystems/angler.hpp"
// #include "subsystems/chassis.hpp"
// #include "subsystems/intake.hpp"
// #include "autons.hpp"

// void blue_wide_zone() {

//   // "slow" turn parameters
//   TuningParams turn_slow = {
//     .first_voltage = 5000,
//     .second_voltage = 3000,
//     .stop_within_first = 3 * units::DEGREES,
//     .stop_within_second = 0 * units::DEGREES,
//     .time_between = 50 * units::MS
//   };

//   // tare orientation
//   subsystems::chassis::tare_orientation(180 * units::DEGREES);

//   // start intake and move forward, grabbing cubes
//   subsystems::intake::move_voltage(12000);
//   move_dist(35 * units::INCHES, 3000, true, tuning_params_slow);
//   pros::delay(700);

//   // back out
//   move_dist(4 * units::INCHES, 2000, false, tuning_params_default_all_cubes);

//   // rotate
//   rotate(85 * units::DEGREES, 3000, true, turn_slow);

//   // make sure cubes are at the bottom of the intake
//   subsystems::intake::move_voltage(-2500);
//   pros::delay(700);
//   subsystems::intake::hold();

//   // move to goal
//   move_dist(72 * units::INCHES, 6000);

//   // dump load
//   while (subsystems::angler::pos > subsystems::angler::POS_DEPOSIT + 8 * units::DEGREES) {
//     subsystems::angler::update_auto_deposit(true);
//     pros::delay(10);
//   }

//   // make sure load is fully in place
//   move_dist(6 * units::INCHES, 800);
//   subsystems::angler::move_voltage(-12000);
//   pros::delay(675);
//   subsystems::angler::hold();

//   // back out
//   move_dist(-15 * units::INCHES, 1000);
// }
