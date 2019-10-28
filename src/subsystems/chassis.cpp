#include "subsystems/chassis.hpp"
#include "lib/sine_profile.hpp"
#include "lib/generic.hpp"

namespace subsystems {
  namespace chassis {

    ////
    // motors, sensors, etc

    // motors
    pros::Motor m_front_l (3, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
    pros::Motor m_front_r (10, pros::E_MOTOR_GEARSET_18, true,  pros::E_MOTOR_ENCODER_DEGREES);
    pros::Motor m_back_l  (1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
    pros::Motor m_back_r  (9, pros::E_MOTOR_GEARSET_18, true,  pros::E_MOTOR_ENCODER_DEGREES);

    // encoders
    pros::ADIEncoder enc_l('A', 'B', true);
    pros::ADIEncoder enc_r('C', 'D', true);

    // position and angle references
    units::Distance dist_ref_l = 0;
    units::Distance dist_ref_r = 0;
    units::Angle orientation_ref = 0;



    ////
    // update functions

    // variables
    void update_vars() {

      units::Angle angle_l = enc_l.get_value() * units::DEGREES;
      units::Angle angle_r = enc_r.get_value() * units::DEGREES;

      dist_l = angle_l * WHEEL_RADIUS + dist_ref_l;
      dist_r = angle_r * WHEEL_RADIUS + dist_ref_r;
      dist_avg = (dist_l + dist_r) * .5;
      orientation = (dist_r - dist_l) / CHASSIS_DIAM + orientation_ref;
    }



    ////
    // control functions

    void hold() {
      m_front_l.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
      m_front_r.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
      m_back_l.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
      m_back_r.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
      
      m_front_l.move_velocity(0);
      m_front_r.move_velocity(0);
      m_back_l.move_velocity(0);
      m_back_r.move_velocity(0);
    }

    // move voltage (separate left and right)
    void move_voltage(int l, int r) {
      m_front_l.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
      m_front_r.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
      m_back_l.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
      m_back_r.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

      m_front_l.move_voltage(l);
      m_front_r.move_voltage(r);
      m_back_l.move_voltage(l);
      m_back_r.move_voltage(r);
    }


    // move voltage (same left/right)
    void move_voltage(int val) {
      move_voltage(val, val);
    }


    // move a distance
    void move_dist_relative(units::Distance dist, units::Time timeout, int start_voltage, units::Distance accel_dist, int end_voltage, units::Distance decel_dist, int max_voltage) {

      // calculate scale
      double scale = accel_dist + decel_dist > fabs(dist) ? fabs(dist / (accel_dist + decel_dist)) : 1;

      // scale all values to be possible
      units::Distance actual_accel_dist = accel_dist * scale;
      units::Distance actual_decel_dist = decel_dist * scale;
      int actual_max_voltage = start_voltage < end_voltage ?
        (max_voltage - start_voltage) * scale + start_voltage :
        (max_voltage - end_voltage)   * scale + end_voltage;
      
      // correct signs in case of backwards movement
      int sign = generic::sign(dist);
      int actual_start_voltage = start_voltage * sign;
      int actual_end_voltage   = end_voltage   * sign;
      actual_accel_dist *= sign;
      actual_decel_dist *= sign;
      actual_max_voltage *= sign;

      // generate profiles
      SineProfile accel_profile(actual_start_voltage, actual_max_voltage, actual_accel_dist);
      SineProfile decel_profile(actual_max_voltage,   actual_end_voltage, actual_decel_dist);

      // calculate exit parameters
      units::Distance starting_pos = dist_avg;
      units::Distance target_dist = dist_avg + dist;
      units::Time interrupt_time = timeout >= 0 ? pros::millis() + timeout : timeout;

      // follow accel profile
      while ((pros::millis() < interrupt_time || interrupt_time < 0) && sign * (actual_accel_dist - (dist_avg - starting_pos)) > 0) {

        move_voltage(accel_profile.get_at(dist_avg - starting_pos));
        pros::delay(10);
      }

      // move at constant speed
      move_voltage(actual_max_voltage);
      while ((pros::millis() < interrupt_time || interrupt_time < 0) && sign * ((target_dist - actual_decel_dist) - dist_avg) > 0) pros::delay(10);

      // follow decel profile
      while ((pros::millis() < interrupt_time || interrupt_time < 0) && sign * (target_dist - dist_avg) > 0) {

        move_voltage(decel_profile.get_at(actual_decel_dist - (target_dist - dist_avg)));
        pros::delay(10);
      }

      // brake
      move_voltage(-500 * sign);
      pros::delay(300);
      move_voltage(0);
    }


    // reset position
    void tare_position(units::Distance ref) {
      dist_ref_l = ref - (dist_l - dist_ref_l);
      dist_ref_r = ref - (dist_r - dist_ref_r);

      update_vars();
    }


    // reset orietation
    void tare_orientation(units::Angle ref) {
      orientation_ref = ref - ((orientation - orientation_ref) / CHASSIS_DIAM);

      update_vars();
    }
  }
}
