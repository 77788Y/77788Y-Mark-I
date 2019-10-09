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

        int min_accel = 4000;
        int min_decel = 0;
        int max_vol = 12000;
        units::Distance dist_accel = 4 * units::INCHES;
        units::Distance dist_decel = 10 * units::INCHES;
        
      };

      // default params
      inline TuningParams tuning_params_default_no_cubes;
      inline TuningParams tuning_params_default_all_cubes = {
        .dist_accel = 10 * units::INCHES,
        .dist_decel = 4 * units::INCHES
      };


      ////
      // syncronous movement

      // move a distance
      bool move_dist(units::Distance _dist, units::Time _timeout = -1, bool _relative = true, TuningParams _tuning = tuning_params_default_no_cubes);
    }
  }
}