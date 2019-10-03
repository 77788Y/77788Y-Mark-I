#include "subsystems/chassis_pid.hpp"
#include "subsystems/chassis.hpp"

namespace subsystems {
  namespace chassis {
    namespace controller_pid {

      // variables
      units::Distance dist_prev = 0;
      units::Time time_prev = pros::millis();
      units::Time time_start = pros::millis();
      units::Distance integral = 0;


      // move update
      void move_update() {

        // delta time
        units::Time delta_t = pros::millis() - time_prev;

        // calculate error and p
        units::Distance error = target_pos - dist_avg;
        double p = error * constants.kp;
        
        // calculate derivative and d
        units::LinearVelocity deriv = (dist_prev - dist_avg) / delta_t;
        double d = deriv * constants.kp / constants.td;

        // calculate integral
        double current_calculation = p + (integral * constants.kp / constants.ti) + d;
        if (fabs(current_calculation) < constants.windup_threshold) integral += error;

        // calculate pid
        double pid = p + (integral * constants.kp / constants.ti) + d;

        // update prev values
        dist_prev = dist_avg;
        time_prev = pros::millis();

        // update motors
        move_voltage(pid);
      }


      // move syncronous
      bool move_syncronous(
        units::Distance _dist,
        units::Time _timeout,
        units::Distance _threshold,
        PidConstants _constants
      ) {

        // set variables
        target_pos = dist_avg + _dist;
        return true;
      }


      // move async
      void move_async(
        units::Distance _dist,
        units::Time _timeout,
        units::Distance _threshold,
        PidConstants _constants
      );


      // get settled
      bool get_settled();


      // wait until settled
      void wait_until_settled(units::Time _timeout);
    }
  }
}