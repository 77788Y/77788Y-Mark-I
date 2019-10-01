#include "cmath"
#include "lib/joystick.hpp"


// default initializer
Joystick :: Joystick() :
    controller(pros::E_CONTROLLER_MASTER),
    deadband_left_x(.1),
    deadband_left_y(.1),
    deadband_right_x(.1),
    deadband_right_y(.1),
    updated(0) {}

// updates the stored variables
void Joystick :: update() {

  // save raw joystick button data
  bool raw_up = controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
  bool raw_down = controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
  bool raw_left = controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);
  bool raw_right = controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
  bool raw_a = controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);
  bool raw_b = controller.get_digital(pros::E_CONTROLLER_DIGITAL_B);
  bool raw_x = controller.get_digital(pros::E_CONTROLLER_DIGITAL_X);
  bool raw_y = controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
  bool raw_l1 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
  bool raw_l2 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
  bool raw_r1 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
  bool raw_r2 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

  // determine new button presses
  btn_up_new = (raw_up && !btn_up) - (!raw_up && btn_up);
  btn_down_new = (raw_down && !btn_down) - (!raw_down && btn_down);
  btn_left_new = (raw_left && !btn_left) - (!raw_left && btn_left);
  btn_right_new = (raw_right && !btn_right) - (!raw_right && btn_right);
  btn_a_new = (raw_a && !btn_a) - (!raw_a && btn_a);
  btn_b_new = (raw_b && !btn_b) - (!raw_b && btn_b);
  btn_x_new = (raw_x && !btn_x) - (!raw_x && btn_x);
  btn_y_new = (raw_y && !btn_y) - (!raw_y && btn_y);
  btn_l1_new = (raw_l1 && !btn_l1) - (!raw_l1 && btn_l1);
  btn_l2_new = (raw_l2 && !btn_l2) - (!raw_l2 && btn_l2);
  btn_r1_new = (raw_r1 && !btn_r1) - (!raw_r1 && btn_r1);
  btn_r2_new = (raw_r2 && !btn_r2) - (!raw_r2 && btn_r2);

  // update button hold times
  if (raw_up) btn_up_hold_time = (btn_up_new != 1) ? btn_up_hold_time + pros::millis() - updated : 0;
  if (raw_down) btn_down_hold_time = (btn_down_new != 1) ? btn_down_hold_time + pros::millis() - updated : 0;
  if (raw_left) btn_left_hold_time = (btn_left_new != 1) ? btn_left_hold_time + pros::millis() - updated : 0;
  if (raw_right) btn_right_hold_time = (btn_right_new != 1) ? btn_right_hold_time + pros::millis() - updated : 0;
  if (raw_a) btn_a_hold_time = (btn_a_new != 1) ? btn_a_hold_time + pros::millis() - updated : 0;
  if (raw_b) btn_b_hold_time = (btn_b_new != 1) ? btn_b_hold_time + pros::millis() - updated : 0;
  if (raw_x) btn_x_hold_time = (btn_x_new != 1) ? btn_x_hold_time + pros::millis() - updated : 0;
  if (raw_y) btn_y_hold_time = (btn_y_new != 1) ? btn_y_hold_time + pros::millis() - updated : 0;
  if (raw_l1) btn_l1_hold_time = (btn_l1_new != 1) ? btn_l1_hold_time + pros::millis() - updated : 0;
  if (raw_l2) btn_l2_hold_time = (btn_l2_new != 1) ? btn_l2_hold_time + pros::millis() - updated : 0;
  if (raw_r1) btn_r1_hold_time = (btn_r1_new != 1) ? btn_r1_hold_time + pros::millis() - updated : 0;
  if (raw_r2) btn_r2_hold_time = (btn_r2_new != 1) ? btn_r2_hold_time + pros::millis() - updated : 0;

  // update public raw button presses
  btn_up = raw_up;
  btn_down = raw_down;
  btn_left = raw_left;
  btn_right = raw_right;
  btn_a = raw_a;
  btn_b = raw_b;
  btn_x = raw_x;
  btn_y = raw_y;
  btn_l1 = raw_l1;
  btn_l2 = raw_l2;
  btn_r1 = raw_r1;
  btn_r2 = raw_r2;

  // update analog sticks (range of -100:100)
  analog_right_x = (float) controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) * 0.00787401575;
  if (fabs(analog_right_x) <= deadband_right_x) analog_right_x = 0.f;
  analog_right_y = (float) controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) * 0.00787401575;
  if (fabs(analog_right_y) <= deadband_right_y) analog_right_y = 0.f;
  analog_left_x = (float) controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) * 0.00787401575;
  if (fabs(analog_left_x) <= deadband_left_x) analog_left_x = 0.f;
  analog_left_y = (float) controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) * 0.00787401575;
  if (fabs(analog_left_y) <= deadband_left_y) analog_left_y = 0.f;

  // update time when last updated
  updated = pros::millis();
}
