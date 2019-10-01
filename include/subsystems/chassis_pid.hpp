#pragma once

#include "main.h"
#include "lib/units.hpp"

namespace subsystems {
  namespace chassis {
    namespace controller_pid {

      // constants struct
      struct PidConstants {

        double kp = 1;
        double ti = 0;
        double td = 0;
      };


      // standard constants
      inline PidConstants constants_default = {
        .kp = 1,
        .ti = 0,
        .td = 0
      };


      // pid parameters
      inline units::Distance target_pos = 0;
      inline units::Time timeout = 0;
      inline units::Time time_start = pros::millis();
      inline units::Distance threshold = 0;
      inline PidConstants constants = constants_default;


      // move update
      void move_update();


      // move syncronous
      bool move_syncronous(
        units::Distance _dist,
        units::Time _timeout = -1,
        units::Distance _threshold = 1 * units::INCHES,
        PidConstants _constants = constants_default
      );


      // move async
      void move_async(
        units::Distance _dist,
        units::Time _timeout = -1,
        units::Distance _threshold = 1 * units::INCHES,
        PidConstants _constants = constants_default
      );


      // get settled
      bool get_settled();


      // wait until settled
      void wait_until_settled(units::Time _timeout=-1);
    }
  }
}