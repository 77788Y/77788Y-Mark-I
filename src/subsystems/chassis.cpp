#include "subsystems/chassis.hpp"

namespace subsystems {
  namespace chassis {

    ////
    // motors, sensors, etc

    // motors
    pros::Motor m_front_l (1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
    pros::Motor m_front_r (2, pros::E_MOTOR_GEARSET_18, true,  pros::E_MOTOR_ENCODER_DEGREES);
    pros::Motor m_back_l  (3, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
    pros::Motor m_back_r  (4, pros::E_MOTOR_GEARSET_18, true,  pros::E_MOTOR_ENCODER_DEGREES);

    // encoders
    pros::ADIEncoder enc_l('A', 'B', false);
    pros::ADIEncoder enc_r('C', 'D', false);



    ////
    // update functions

    // variables
    void update_vars() {

      units::Angle angle_l = enc_l.get_value() * units::DEGREES;
      units::Angle angle_r = enc_r.get_value() * units::DEGREES;

      dist_l = angle_l * WHEEL_RADIUS;
      dist_r = angle_r * WHEEL_RADIUS;
      dist_avg = (dist_l + dist_r) * .5;
      orientation = (dist_r - dist_l) / CHASSIS_DIAM;
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
  }
}
