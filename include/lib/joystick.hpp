#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "main.h"

class Joystick {

public:

  // controller object
  pros::Controller controller;

  // time when last updated
  int updated;

  // raw joystick button values
  bool btn_up;
  bool btn_down;
  bool btn_left;
  bool btn_right;
  bool btn_a;
  bool btn_b;
  bool btn_x;
  bool btn_y;
  bool btn_l1;
  bool btn_l2;
  bool btn_r1;
  bool btn_r2;

  // registers NEW button pressed
  int btn_up_new;
  int btn_down_new;
  int btn_left_new;
  int btn_right_new;
  int btn_a_new;
  int btn_b_new;
  int btn_x_new;
  int btn_y_new;
  int btn_l1_new;
  int btn_l2_new;
  int btn_r1_new;
  int btn_r2_new;

  // stores how long buttons have been held down
  int btn_up_hold_time;
  int btn_down_hold_time;
  int btn_left_hold_time;
  int btn_right_hold_time;
  int btn_a_hold_time;
  int btn_b_hold_time;
  int btn_x_hold_time;
  int btn_y_hold_time;
  int btn_l1_hold_time;
  int btn_l2_hold_time;
  int btn_r1_hold_time;
  int btn_r2_hold_time;

  // analog stick values (left/right, horizontal/vertical)
  float analog_right_x;
  float analog_right_y;
  float analog_left_y;
  float analog_left_x;

  // analog deadbands
  float deadband_right_x;
  float deadband_right_y;
  float deadband_left_x;
  float deadband_left_y;

  // initializer
  Joystick();

  // updates the button readings
  void update();
};

#endif
