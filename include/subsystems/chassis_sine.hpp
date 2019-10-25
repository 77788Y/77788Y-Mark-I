#pragma once

#include "main.h"
#include "lib/units.hpp"
#include <memory>

namespace subsystems {
  namespace chassis {
    namespace controller_sine {

      ////
      // tuning params
      struct SineTuningParams {

        int min_accel = 4000;
        int min_decel = 2000;
        int max_vol = 8000;
        units::Distance dist_accel = 4 * units::INCHES;
        units::Distance dist_decel = 6 * units::INCHES;

      };

      // default params
      inline SineTuningParams tuning_params_default_no_cubes;
      inline SineTuningParams tuning_params_default_all_cubes = {
        .min_accel = 4250,
        .min_decel = 2500,
        .max_vol = 9000,
        .dist_accel = 8 * units::INCHES,
        .dist_decel = 4 * units::INCHES
      };

      inline SineTuningParams tuning_params_slow = {
        .min_accel = 3000,
        .min_decel = 6000,
        .max_vol = 3000,
        .dist_accel = 5 * units::INCHES,
        .dist_decel = 5 * units::INCHES
      };

      ////
      // syncronous movement

      // move a distance
      bool move_dist(units::Distance _dist, units::Time _timeout = -1, bool _relative = true, SineTuningParams _tuning = tuning_params_default_no_cubes);
    }
  }
}
