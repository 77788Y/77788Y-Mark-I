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
      bool move_dist(units::Distance _dist, units::Time _timeout = -1, bool _relative = true, TuningParams _tuning = tuning_params_default, units::Distance _threshold = 1 * units::INCHES);


      ////
      // asyncronous movement

      // type of motion
      enum MotionType {
        MOTION_NONE,
        MOTION_LINEAR
      };

      // current motion type
      static MotionType motion_type = MOTION_NONE;

      // check if motion is completed
      bool check_settled();

      // wait for motion to be completed
      bool wait_until_settled(units::Time timeout = -1);

      // move a distance
      bool move_dist_async(units::Distance _dist, units::Time _timeout = -1, bool _relative = true, TuningParams _tuning = tuning_params_default, units::Distance _threshold = 1 * units::INCHES);

      // task
      inline std::shared_ptr<pros::Task> task;

      // initialize controller
      void init();


      ////
      // asyncronous notifications

      // type of notification
      enum Notification {
        NOTIFY_NONE = 0,
        NOTIFY_INTERRUPT = 1
      };

      // interrupt motion
      void interrupt();
    }
  }
}