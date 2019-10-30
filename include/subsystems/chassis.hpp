#pragma once

#include "main.h"
#include "lib/units.hpp"
#include <memory>

namespace subsystems {
  namespace chassis {

    ////
    // constants
    const units::Distance WHEEL_RADIUS = (2.683 / 2) * units::INCHES;
    const units::Distance CHASSIS_DIAM = 5.0235 * units::INCHES;



    ////
    // motors, sensors, etc

    // motors
    extern pros::Motor m_front_l;
    extern pros::Motor m_front_r;
    extern pros::Motor m_back_l;
    extern pros::Motor m_back_r;



    ////
    // variables

    // position
    inline units::Distance dist_l = 0;
    inline units::Distance dist_r = 0;
    inline units::Distance dist_avg = 0;
    inline units::Angle orientation = 0;



    ////
    // update functions

    // variables
    void update_vars();



    ////
    // control functions

    // hold motors
    void hold();

    // move voltage (separate left and right)
    void move_voltage(int l, int r);

    // move voltage (same left/right)
    void move_voltage(int val);

    // move by a distance
   void move_by (
      units::Distance dist,
      units::Time timeout = -1,
      int max_voltage = 8000,
      int start_voltage = 4000, units::Distance accel_dist = 4 * units::INCHES,
      int end_voltage   = 2000, units::Distance decel_dist = 6 * units::INCHES,
      double angle_correct_weight = 7500
    );

    // move to a distance
    inline void move_to (
      units::Distance dist,
      units::Time timeout = -1,
      int max_voltage = 8000,
      int start_voltage = 4000, units::Distance accel_dist = 4 * units::INCHES,
      int end_voltage   = 2000, units::Distance decel_dist = 6 * units::INCHES,
      double angle_correct_weight = 7500
    ) { move_by(dist - dist_avg, timeout, max_voltage, start_voltage, accel_dist, end_voltage, decel_dist); }

    // rotate by an angle
   void rotate_by (
      units::Angle angle,
      units::Time timeout = -1,
      int max_voltage = 8000,
      int start_voltage = 4000, units::Angle accel_angle = 4 * units::INCHES,
      int end_voltage   = 2000, units::Angle decel_angle = 6 * units::INCHES
    );

    // rotate to an angle
    inline void rotate_to (
      units::Angle angle,
      units::Time timeout = -1,
      int max_voltage = 8000,
      int start_voltage = 8000, units::Angle accel_angle = 45 * units::DEGREES,
      int end_voltage   = 0,    units::Angle decel_angle = 45 * units::DEGREES
    ) { rotate_by(angle - orientation, timeout, max_voltage, start_voltage, accel_angle, end_voltage, decel_angle); }

    // reset encoders
    void tare_position(units::Distance ref = 0);
    void tare_orientation(units::Angle ref = 0);


    ////
    // async

    // mutex
    inline pros::Mutex control_mutex;
  }
}
