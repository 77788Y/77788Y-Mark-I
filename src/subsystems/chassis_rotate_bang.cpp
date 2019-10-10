#include "subsystems/chassis.hpp"
#include "subsystems/chassis_rotate_bang.hpp"
#include "lib/generic.hpp"
#include <iostream>

namespace subsystems {
  namespace chassis {
    namespace controller_rotate_bang {


      ////
      // general vars

      TuningParams tuning_params = tuning_params_default;
      units::Time interrupt_time = 0;
      units::Angle target_angle = 0;
      units::Angle starting_angle = 0;


      ////
      // syncronous turning

      // initialize motion
      void initialize_motion(units::Angle _angle, units::Time _timeout, bool _relative, TuningParams _tuning) {

        // set up vars
        tuning_params = _tuning;
        starting_angle = orientation;
        target_angle = _angle + _relative * chassis::orientation;
        std::cout << orientation << "\t" << target_angle << std::endl;
        interrupt_time = _timeout < 0 ? _timeout : pros::millis() + _timeout;
      }


      // perform motion
      bool perform_motion() {

        // speedy turn
        int sign = generic::sign(target_angle - chassis::orientation);
        while ((interrupt_time < 0 || pros::millis() < interrupt_time) &&  sign * (target_angle - chassis::orientation) > tuning_params_default.stop_within_first) {
          chassis::move_voltage(-tuning_params.first_voltage * sign, tuning_params.first_voltage * sign);
          pros::delay(10);
        }

        // wait a bit for momentum to carry past target
        pros::delay(tuning_params.time_between);

        // slow turn
        sign = generic::sign(target_angle - chassis::orientation);
        while ((interrupt_time < 0 || pros::millis() < interrupt_time) &&  sign * (target_angle - chassis::orientation) > tuning_params_default.stop_within_second) {
          chassis::move_voltage(-tuning_params.second_voltage * sign, tuning_params.second_voltage * sign);
          pros::delay(10);
        }

        // brake
        sign = generic::sign(target_angle - chassis::orientation);
        move_voltage(-2000 * sign, 2000 * sign);
        pros::delay(300);
        move_voltage(0);

        return true;
      }

      // rotate
      bool rotate(units::Angle _angle, units::Time _timeout, bool _relative, TuningParams _tuning) {

        if (chassis::control_mutex.take(0)) {
          initialize_motion(_angle, _timeout, _relative, _tuning);
          bool r = perform_motion();
          chassis::control_mutex.give();
          return r;
        }

        return false;
      }
    }
  }
}
