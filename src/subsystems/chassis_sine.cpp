#include "subsystems/chassis.hpp"
#include "lib/generic.hpp"
#include "subsystems/chassis_sine.hpp"
#include <iostream>

namespace subsystems {
  namespace chassis {
    namespace controller_sine {


      ///
      // general vars

      SineTuningParams tuning_params = tuning_params_default_no_cubes;
      units::Time interrupt_time = 0;
      units::Distance target_pos = 0;
      units::Distance starting_pos = 0;
      units::Distance dist_accel = 0;
      units::Distance dist_decel = 0;
      int amp_accel = tuning_params_default_no_cubes.max_vol;
      int amp_decel = tuning_params_default_no_cubes.max_vol;
      int constant_speed = tuning_params_default_no_cubes.max_vol;
      int sign = 0;



      ////
      // syncronous movement


      // inialize motion
      void initialize_motion(units::Distance _dist, units::Time _timeout, bool _relative, SineTuningParams _tuning) {

        // set up variables
        tuning_params = _tuning;
        starting_pos = dist_avg;
        target_pos = _dist + (_relative * chassis::dist_avg);
        interrupt_time = _timeout < 0 ? _timeout : pros::millis() + _timeout;

        // generate sine equations
        units::Distance dist_rel = target_pos - chassis::dist_avg;
        sign = generic::sign(dist_rel);
        dist_accel = tuning_params.dist_accel * sign;
        dist_decel = tuning_params.dist_decel * sign;
        int amp_base = tuning_params.max_vol * sign;
        units::Distance sum = dist_accel + dist_decel;
        if (fabs(tuning_params.dist_accel + tuning_params.dist_decel) > fabs(dist_rel)) {
          dist_accel *= fabs(dist_rel / sum);
          dist_decel *= fabs(dist_rel / sum);
          amp_base *= (fabs(dist_accel) > fabs(dist_decel)) ? fabs(dist_accel / sum) : fabs(dist_decel / sum);
        }
        constant_speed = amp_base;
        std::cout << constant_speed;
        amp_accel = constant_speed - tuning_params.min_accel * sign;
        amp_decel = constant_speed - tuning_params.min_decel * sign;
      }


      // perform motion
      bool perform_motion() {

        // accelerate
        std::cout << "accelerating" << std::endl;
        // bool is_behind = dist_avg < dist_accel;
        while ((pros::millis() < interrupt_time || interrupt_time < 0) && sign * (dist_accel - (dist_avg - starting_pos)) > 0) {

          move_voltage((amp_accel * .5) * cos((M_PI * fabs(dist_avg - starting_pos) / dist_accel) + M_PI) +
            (amp_accel * .5) +
            tuning_params.min_accel * sign
          );

          if (pros::millis() % 250 <= 100) std::cout << (dist_avg - starting_pos) << "\t" << ((amp_accel * .5) * cos((M_PI * fabs(dist_avg - starting_pos) / dist_accel) + M_PI) + (amp_accel * .5) + tuning_params.min_accel * sign) << std::endl;
          pros::delay(10);
        }

        // constant
        std::cout << "constant" << std::endl;
        while ((pros::millis() < interrupt_time || interrupt_time < 0) && sign * ((target_pos - dist_decel) - dist_avg) > 0) {

          move_voltage(constant_speed);

          pros::delay(10);
        }

        // decelerate
        std::cout << "decelerating" << std::endl;
        // is_behind = dist_avg < target_pos;
        while ((pros::millis() < interrupt_time || interrupt_time < 0) && sign * (target_pos - dist_avg) > 0) {

          move_voltage((amp_decel * .5) * cos((M_PI * fabs(target_pos - dist_avg) / dist_decel) + M_PI) +
            (amp_decel * .5) +
            tuning_params.min_decel * sign
          );

          pros::delay(10);
        }

        // brake
        move_voltage(-500 * sign);
        pros::delay(300);
        move_voltage(0);

        return true;
      }


      // move a distance
      bool move_dist(units::Distance _dist, units::Time _timeout, bool _relative, SineTuningParams _tuning) {

        if (chassis::control_mutex.take(0)) {
          std::cout << "reached mutex" << std::endl;
          initialize_motion(_dist, _timeout, _relative, _tuning);
          std::cout << "gonna perform" << std::endl;
          bool r = perform_motion();
          std::cout << "performed" << std::endl;
          chassis::control_mutex.give();
          return r;
        }

        return false;
      }
    }
  }
}
