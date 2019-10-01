#include "subsystems/chassis_pid.hpp"
#include "subsystems/chassis.hpp"

namespace subsystems {
  namespace chassis {
    namespace controller_pid {

      // variables
      units::Distance dist_prev = 0;


      // move update
      void move_update() {

        // calculate error
        units::Distance error = target_pos - dist_avg;
        
        // calculate derivative
        units::LinearVelocity deriv = (dist_prev - dist_avg) 
      }


      // move syncronous
      bool move_syncronous(
        units::Distance _dist,
        units::Time _timeout,
        units::Distance _threshold,
        PidConstants _constants
      );


      // move async
      void move_async(
        units::Distance _dist,
        units::Time _timeout,
        units::Distance _threshold,
        PidConstants _constants
      );


      // get settled
      bool get_settled();


      // wait until settled
      void wait_until_settled(units::Time _timeout);
    }
  }
}