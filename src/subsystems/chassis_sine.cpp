#include "subsystems/chassis.hpp"
#include "lib/generic.hpp"
#include "subsystems/chassis_sine.hpp"

namespace subsystems {
  namespace chassis {
    namespace controller_sine {


      ///
      // general vars

      TuningParams tuning_params = tuning_params_default;
      units::Time interrupt_time = 0;
      units::Distance target_pos = 0;
      units::Distance starting_pos = 0;
      units::Distance dist_accel = 0;
      units::Distance dist_decel = 0;
      int amplitude = 12000;



      ////
      // syncronous movement


      // inialize motion
      void initialize_motion(units::Distance _dist, units::Time _timeout, bool _relative, TuningParams _tuning) {

        // set up variables
        tuning_params = _tuning;
        starting_pos = dist_avg;
        target_pos = _dist + _relative * chassis::dist_avg;
        interrupt_time = pros::millis() + _timeout;

        // generate sine equations
        units::Distance dist_rel = target_pos - chassis::dist_avg;
        units::Distance sum = tuning_params.dist_accel + tuning_params.dist_decel;
        dist_accel = tuning_params.dist_accel * generic::sign(dist_rel);
        dist_decel = tuning_params.dist_decel * generic::sign(dist_rel);
        amplitude = 12000;
        if (tuning_params.dist_accel + tuning_params.dist_decel > dist_rel) {
          dist_accel *= fabs(dist_rel / sum);
          dist_decel *= fabs(dist_rel / sum);
          amplitude *= (fabs(dist_accel) > fabs(dist_decel)) ? dist_accel / sum : dist_decel / sum;
        }
        amplitude -= tuning_params.volt_min * generic::sign(amplitude);
      }


      // perform motion
      bool perform_motion() {

        // accelerate
        bool is_behind = starting_pos < dist_accel;
        while ((pros::millis() < interrupt_time || interrupt_time < 0) && (starting_pos < target_pos) == is_behind) {

          move_voltage((amplitude * .5) * cos((M_PI * (dist_avg - starting_pos) / dist_accel) + M_PI) +
            (amplitude * .5) +
            tuning_params.volt_min * generic::sign(amplitude)
          );
        }

        // constant
        is_behind = dist_avg - starting_pos < target_pos - dist_decel;
        while (((pros::millis() < interrupt_time || interrupt_time < 0) && dist_avg - starting_pos < target_pos - dist_decel) == is_behind) {

          move_voltage(amplitude + tuning_params.volt_min * generic::sign(amplitude));
        }

        // decelerate
        is_behind = dist_avg < target_pos;
        while ((pros::millis() < interrupt_time || interrupt_time < 0) && (dist_avg < target_pos) == is_behind) {

          move_voltage((amplitude * .5) * cos(M_PI * (dist_avg - starting_pos) / dist_decel) +
            (amplitude * .5) +
            tuning_params.volt_min * generic::sign(amplitude)
          );
        }

        // brake
        move_voltage(-500 * generic::sign(amplitude));
        pros::delay(300);
        move_voltage(0);
        
        return true;
      }


      // move a distance
      bool move_dist(units::Distance _dist, units::Time _timeout, bool _relative, TuningParams _tuning) {

        if (chassis::control_mutex.take(0)) {
          initialize_motion(_dist, _timeout, _relative, _tuning);
          return perform_motion();
          chassis::control_mutex.give();
        }

        return false;
      }
    }
  }
}