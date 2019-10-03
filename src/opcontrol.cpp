#include "main.h"
#include "lib/joystick.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/lift.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/angler.hpp"

// import subsystems into current namespace
using namespace subsystems;

// declare/define controller
Joystick controller;

void opcontrol() {

	while (true) {

		// update controller
		controller.update();

		// drive
		chassis::move_voltage(controller.analog_left_y * 12000.0, controller.analog_right_y * 12000.0);

		// lift
		if (controller.btn_l1) lift::angle_target = lift::POS_MAX;
		else if (controller.btn_l2) lift::angle_target = lift::POS_MIN;
		else if (controller.btn_l1_new == -1 || controller.btn_l2_new == -1) lift::angle_target = lift::pos;

		// intake
		if ((controller.btn_r1 - controller.btn_r2) && !(controller.btn_b || controller.btn_x)) intake::move_voltage((controller.btn_r1 - controller.btn_r2) * 12000);
		else if (controller.btn_a) intake::move_voltage(-750);
		else if (controller.btn_b - controller.btn_x) intake::move_voltage((controller.btn_b - controller.btn_x) * 2500 + 1000);
		else intake::hold();

		// angler
		if (controller.btn_a) angler::update_auto_deposit();
		else if (controller.btn_x - controller.btn_b) angler::move_voltage((controller.btn_x - controller.btn_b) * 12000 - 4000);
		else angler::hold();

		pros::delay(10);
	}
}
