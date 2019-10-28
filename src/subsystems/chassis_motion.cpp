#include "subsystems/chassis.hpp"
#include "lib/sine_profile.hpp"
#include "lib/generic.hpp"

namespace subsystems {
  namespace chassis {

    ////
    // move a distance

    // relative motion
    void move_by(units::Distance dist, units::Time timeout, int start_voltage, units::Distance accel_dist, int end_voltage, units::Distance decel_dist, int max_voltage) {

      // calculate scale
      double scale = accel_dist + decel_dist > fabs(dist) ? fabs(dist / (accel_dist + decel_dist)) : 1;

      // scale all values to be possible
      units::Distance actual_accel_dist = accel_dist * scale;
      units::Distance actual_decel_dist = decel_dist * scale;
      int actual_max_voltage = start_voltage < end_voltage ?
        (max_voltage - start_voltage) * scale + start_voltage :
        (max_voltage - end_voltage)   * scale + end_voltage;
      
      // correct signs in case of backwards movement
      int sign = generic::sign(dist);
      int actual_start_voltage = start_voltage * sign;
      int actual_end_voltage   = end_voltage   * sign;
      actual_accel_dist *= sign;
      actual_decel_dist *= sign;
      actual_max_voltage *= sign;

      // generate profiles
      SineProfile accel_profile(actual_start_voltage, actual_max_voltage, actual_accel_dist);
      SineProfile decel_profile(actual_max_voltage,   actual_end_voltage, actual_decel_dist);

      // calculate exit parameters
      units::Distance starting_pos = dist_avg;
      units::Distance target_dist = dist_avg + dist;
      units::Time interrupt_time = timeout >= 0 ? pros::millis() + timeout : timeout;

      // follow accel profile
      while ((pros::millis() < interrupt_time || interrupt_time < 0) && sign * (actual_accel_dist - (dist_avg - starting_pos)) > 0) {

        move_voltage(accel_profile.get_at(dist_avg - starting_pos));
        pros::delay(10);
      }

      // move at constant speed
      move_voltage(actual_max_voltage);
      while ((pros::millis() < interrupt_time || interrupt_time < 0) && sign * ((target_dist - actual_decel_dist) - dist_avg) > 0) pros::delay(10);

      // follow decel profile
      while ((pros::millis() < interrupt_time || interrupt_time < 0) && sign * (target_dist - dist_avg) > 0) {

        move_voltage(decel_profile.get_at(actual_decel_dist - (target_dist - dist_avg)));
        pros::delay(10);
      }

      // brake
      move_voltage(-500 * sign);
      pros::delay(300);
      move_voltage(0);
    }



    ////
    // rotate

    // relative motion
    void rotate_by(units::Angle angle, units::Time timeout, int start_voltage, units::Angle accel_angle, int end_voltage, units::Angle decel_angle, int max_voltage) {

      // calculate scale
      double scale = accel_angle + decel_angle > fabs(angle) ? fabs(angle / (accel_angle + decel_angle)) : 1;

      // scale all values to be possible
      units::Angle actual_accel_angle = accel_angle * scale;
      units::Angle actual_decel_angle = accel_angle * scale;
      int actual_max_voltage = start_voltage < end_voltage ?
        (max_voltage - start_voltage) * scale + start_voltage :
        (max_voltage - end_voltage)   * scale + end_voltage;
      
      // correct signs in case of backwards movement
      int sign = generic::sign(angle);
      int actual_start_voltage = start_voltage * sign;
      int actual_end_voltage   = end_voltage   * sign;
      actual_accel_angle *= sign;
      actual_decel_angle *= sign;
      actual_max_voltage *= sign;

      // generate profiles
      SineProfile accel_profile(actual_start_voltage, actual_max_voltage, actual_accel_angle);
      SineProfile decel_profile(actual_max_voltage,   actual_end_voltage, actual_decel_angle);

      // calculate exit parameters
      units::Distance starting_pos = orientation;
      units::Distance target_angle = orientation + angle;
      units::Time interrupt_time = timeout >= 0 ? pros::millis() + timeout : timeout;

      // follow accel profile
      while ((pros::millis() < interrupt_time || interrupt_time < 0) && sign * (actual_accel_angle - (orientation - starting_pos)) > 0) {

        move_voltage(accel_profile.get_at(dist_avg - starting_pos));
        pros::delay(10);
      }

      // move at constant speed
      move_voltage(actual_max_voltage);
      while ((pros::millis() < interrupt_time || interrupt_time < 0) && sign * ((target_angle - actual_decel_angle) - orientation) > 0) pros::delay(10);

      // follow decel profile
      while ((pros::millis() < interrupt_time || interrupt_time < 0) && sign * (target_angle - orientation) > 0) {

        double speed = decel_profile.get_at(actual_decel_angle - (target_angle - orientation));
        move_voltage(-speed, speed);
        pros::delay(10);
      }

      // brake
      move_voltage(500 * sign, -500 * sign);
      pros::delay(300);
      move_voltage(0);
    }
  }
}