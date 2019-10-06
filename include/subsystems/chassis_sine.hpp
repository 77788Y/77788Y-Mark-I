#pragma once

#include "main.h"
#include "lib/units.hpp"
#include <memory>

namespace subsystems {
  namespace chassis {
    namespace controller_sine {

      ////
      // tuning params
      struct TuningParams {

        int volt_min;
        units::Distance dist_accel;
        units::Distance dist_decel;
        
      };

      // default params
      inline TuningParams tuning_params_default = {
        .volt_min = 2000,
        .dist_accel = 4 * units::INCHES,
        .dist_decel = 4 * units::INCHES
      };


      ////
      // syncronous movement

      // move a distance
      bool move_dist(units::Distance _dist, units::Time _timeout = -1, bool _relative = true, TuningParams _tuning = tuning_params_default);
    }
  }
}