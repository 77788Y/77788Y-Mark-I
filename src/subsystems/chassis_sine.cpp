#include "subsystems/chassis.hpp"
#include "lib/generic.hpp"
#include "subsystems/chassis_sine.hpp"

namespace subsystems {
  namespace chassis {
    namespace controller_sine {


      ///
      // general vars

      // target position of chassis
      units::Distance target_pos = 0;

      // threshold for checking settled
      units::Distance threshold = 0;



      ////
      // syncronous movement

      // exit a movement from an interrupt
      bool cleanup_interrupt() {
        move_voltage(0);
        motion_type = MOTION_NONE;
        return false;
      }


      // move a distance
      bool move_dist(units::Distance _dist, units::Time _timeout, bool _relative, TuningParams _tuning, units::Distance _threshold) {

        // set up variables
        TuningParams tuning_params = _tuning;
        target_pos = _dist + _relative * chassis::dist_avg;
        threshold = _threshold;
        units::Time interrupt_time = pros::millis() + _timeout;
        motion_type = MOTION_LINEAR;

        // generate sine equations
        units::Distance starting_pos = dist_avg;
        units::Distance dist_rel = target_pos - chassis::dist_avg;
        units::Distance sum = tuning_params.dist_accel + tuning_params.dist_decel;
        units::Distance dist_accel = tuning_params.dist_accel * generic::sign(dist_rel);
        units::Distance dist_decel = tuning_params.dist_decel * generic::sign(dist_rel);
        int amplitude = 12000;
        if (tuning_params.dist_accel + tuning_params.dist_decel > dist_rel) {
          dist_accel *= fabs(dist_rel / sum);
          dist_decel *= fabs(dist_rel / sum);
          amplitude *= (fabs(dist_accel) > fabs(dist_decel)) ? dist_accel / sum : dist_decel / sum;
        }
        amplitude -= tuning_params.volt_min * generic::sign(amplitude);

        // accelerate
        bool is_behind = starting_pos < dist_accel;
        while ((pros::millis() < interrupt_time || interrupt_time < 0) && (starting_pos < target_pos) == is_behind) {

          // check for interrupt
          if (task->notify_take(true, 0) == NOTIFY_INTERRUPT) return cleanup_interrupt();

          // move
          move_voltage((amplitude * .5) * cos((M_PI * (dist_avg - starting_pos) / dist_accel) + M_PI) +
            (amplitude * .5) +
            tuning_params.volt_min * generic::sign(amplitude)
          );
        }

        // constant
        is_behind = dist_avg - starting_pos < target_pos - dist_decel;
        while (((pros::millis() < interrupt_time || interrupt_time < 0) && dist_avg - starting_pos < target_pos - dist_decel) == is_behind) {

          // check for interrupt
          if (task->notify_take(true, 0) == NOTIFY_INTERRUPT) return cleanup_interrupt();

          // move
          move_voltage(amplitude + tuning_params.volt_min * generic::sign(amplitude));
        }

        // decelerate
        is_behind = dist_avg < target_pos;
        while ((pros::millis() < interrupt_time || interrupt_time < 0) && (dist_avg < target_pos) == is_behind) {

          // check for interrupt
          if (task->notify_take(true, 0) == NOTIFY_INTERRUPT) return cleanup_interrupt();

          // move
          move_voltage((amplitude * .5) * cos(M_PI * (dist_avg - starting_pos) / dist_decel) +
            (amplitude * .5) +
            tuning_params.volt_min * generic::sign(amplitude)
          );
        }

        // brake
        move_voltage(-500 * generic::sign(amplitude));
        if (task->notify_take(true, 300) == NOTIFY_INTERRUPT) return cleanup_interrupt(); // delay for 300 ms, while still checking for interrupts
        move_voltage(0);

        // clean up
        motion_type = MOTION_NONE;
        return true;
      }



      ////
      // asyncronous movement

      // check if motion is completed
      bool check_settled() {
        switch (motion_type) {
          
          case (MOTION_NONE): return true;
          case (MOTION_LINEAR): return fabs(chassis::dist_avg - target_pos) <= threshold;
          default: return true;
        }
      }


      // wait for motion to be completed
      bool wait_until_settled(units::Time timeout) {

        units::Time timeout_time = pros::millis() + timeout;
        while (!check_settled() && (timeout < 0 || pros::millis() < timeout_time)) pros::delay(10);
        return check_settled();
      }


      // move a distance
      bool move_dist_async(units::Distance _dist, units::Time _timeout, bool _relative, units::Distance _threshold);


      // update task
      void update_task(void*);


      // initialize controller
      void init() {
        task = std::make_shared<pros::Task>(update_task, nullptr, "sine chassis controller");
      }



      ////
      // asyncronous notifications


      // interrupt motion
      void interrupt() {
        task->notify_ext(NOTIFY_INTERRUPT, NOTIFY_ACTION_OWRITE, NULL);
      }
    }
  }
}