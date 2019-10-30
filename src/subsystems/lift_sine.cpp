#include "subsystems/lift.hpp"
#include "lib/sine_profile.hpp"

namespace subsystems {
  namespace lift {


    ////
    // constants

    // accel/decel distance
    static const units::Angle ACCEL_DIST = 25 * units::DEGREES;
    static const units::Angle DECEL_DIST = 25 * units::DEGREES;

    // start/end voltage
    static const int START_VOLTAGE = 2000;
    static const int END_VOLTAGE = 2000;

    // max voltage
    static const int MAX_VOLTAGE = 12000;

    // bias voltage
    static const int BIAS_VOLTAGE = 4000;

    void task_update(void*) {

      while (true) {

        // wait for notification
        task -> notify_take(true, TIMEOUT_MAX);

        units::Angle dist = angle_target - pos;

        // calculate scale
        double scale = ACCEL_DIST + DECEL_DIST > fabs(dist) ? fabs(dist / (ACCEL_DIST + DECEL_DIST)) : 1;

        // scale all values to be possible
        units::Distance actual_accel_dist = ACCEL_DIST * scale;
        units::Distance actual_decel_dist = DECEL_DIST * scale;
        int actual_max_voltage = START_VOLTAGE < END_VOLTAGE ?
          (MAX_VOLTAGE - START_VOLTAGE) * scale + START_VOLTAGE :
          (MAX_VOLTAGE - END_VOLTAGE)   * scale + END_VOLTAGE;
        
        // correct signs in case of backwards movement
        int sign = generic::sign(dist);
        int actual_start_voltage = START_VOLTAGE * sign;
        int actual_end_voltage   = END_VOLTAGE   * sign;
        actual_accel_dist *= sign;
        actual_decel_dist *= sign;
        actual_max_voltage *= sign;

        // generate profiles
        SineProfile accel_profile(actual_start_voltage, actual_max_voltage, actual_accel_dist);
        SineProfile decel_profile(actual_max_voltage,   actual_end_voltage, actual_decel_dist);

        // calculate motion parameters
        units::Distance starting_pos = pos;

        // follow accel profile
        while (sign * (actual_accel_dist - (pos - starting_pos)) > 0 && !task -> notify_take(false, 0)) {

          move_voltage(accel_profile.get_at(pos - starting_pos));
          pros::delay(10);
        }

        // move at constant speed
        move_voltage(actual_max_voltage);
        while (sign * ((angle_target - actual_decel_dist) - pos) > 0 && !task -> notify_take(false, 0)) pros::delay(10);

        // follow decel profile
        while (sign * (angle_target - pos) > 0 && !task -> notify_take(false, 0)) {

          // calculate raw voltage
          move_voltage(decel_profile.get_at(actual_decel_dist - (angle_target - pos)));
          pros::delay(10);
        }

        // brake
        move_voltage(-500 * sign);
        pros::delay(300);

      }
    }
  }
}