#include "subsystems/chassis.hpp"
#include "subsystems/chassis_rotate_bang.hpp"
#include "lib/generic.hpp"

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
        interrupt_time = pros::millis() + _timeout;
      }


      // perform motion
      bool perform_motion() {

        // speedy turn
        bool is_behind = chassis::orientation < target_angle;
        int sgn = generic::sign(target_angle - chassis::orientation);
        while ((chassis::orientation < target_angle - tuning_params.stop_within * sgn) == is_behind) {
          chassis::move_voltage(-tuning_params.first_voltage * sgn, tuning_params.first_voltage * sgn);
        }

        // wait a bit for momentum to carry past target
        pros::delay(tuning_params.time_between);

        // slow turn
        is_behind = chassis::orientation < target_angle;
        sgn = generic::sign(target_angle - chassis::orientation);
        while ((chassis::orientation < target_angle) == is_behind) {
          chassis::move_voltage(-tuning_params.second_voltage * sgn, tuning_params.second_voltage * sgn);
        }

        return true;
      }

      // rotate
      bool rotate(units::Angle _angle, units::Time _timeout, bool _relative, TuningParams _tuning) {

        if (chassis::control_mutex.take(0)) {
          initialize_motion(_angle, _timeout, _relative, _tuning);
          return perform_motion();
          chassis::control_mutex.give();
        }

        return false;
      }
    }
  }
}