#include "subsystems/chassis.hpp"
#include "subsystems/chassis_sine.hpp"
#include "subsystems/chassis_rotate_bang.hpp"

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

    // move voltage (separate left and right)
    void move_voltage(int l, int r) {
      m_front_l.move_voltage(l);
      m_front_r.move_voltage(r);
      m_back_l.move_voltage(l);
      m_back_r.move_voltage(r);
    }


    // move voltage (same left/right)
    void move_voltage(int val) {
      move_voltage(val, val);
    }


    // reset position
    void tare_position(units::Distance ref) {
      dist_ref_l = dist_l - ref;
      dist_ref_r = dist_r - ref;

      update_vars();
    }


    // reset orietation
    void tare_orientation(units::Angle ref) {
      orientation_ref = orientation - ref;

      update_vars();
    }
  }
}
