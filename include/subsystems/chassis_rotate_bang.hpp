#pragma once

#include "main.h"
#include "lib/units.hpp"
#include <memory>

namespace subsystems {
  namespace chassis {
    namespace controller_rotate_bang {


      ////
      // tuning params
      struct TuningParams {
        int first_voltage;
        int second_voltage;
        units::Angle stop_within;
        units::Time time_between;
      };

      // default params
      inline TuningParams tuning_params_default = {
        .first_voltage = 6000,
        .second_voltage = 3000,
        .stop_within = 10 * units::DEGREES,
        .time_between = 300 * units::MS
      };


      ////
      // syncronous turning

      // rotate
      bool rotate(units::Angle _angle, units::Time _timeout = -1, bool _relative = false, TuningParams _tuning = tuning_params_default);
    }
  }
}