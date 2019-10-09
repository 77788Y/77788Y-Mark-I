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
        int first_voltage = 8000;
        int second_voltage = 4000;
        units::Angle stop_within_first = 15 * units::DEGREES;
        units::Angle stop_within_second = 2 * units::DEGREES;
        units::Time time_between = 100 * units::MS;
      };

      // default params
      inline TuningParams tuning_params_default;


      ////
      // syncronous turning

      // rotate
      bool rotate(units::Angle _angle, units::Time _timeout = -1, bool _relative = false, TuningParams _tuning = tuning_params_default);
    }
  }
}