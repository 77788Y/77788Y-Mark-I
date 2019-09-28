#include "main.h"
#include "lib/joystick.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/lift.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/angler.hpp"

// import subsystems into current namespace
using namespace subsytems;

// declare/define controller
Joystick controller;

void opcontrol() {

	while (true) {

		// update controller
		controller.update();

		// drive
		chassis::move_voltage(controller.analog_left_y * 12000.0, controller.analog_right_y * 12000.0);

		// lift
		if (controller.btn_l1 - controller.btn_l2) lift::move_voltage((controller.btn_l1 - controller.btn_l2) * 12000);
		else lift::hold();

		// intake
		if (controller.btn_r1 - controller.btn_r2) intake::move_voltage((controller.btn_r1 - controller.btn_r2) * 12000);
		else intake::hold();

		// angler
		if (controller.btn_x - controller.btn_b) angler::move_voltage((controller.btn_x - controller.btn_b) * 12000);
		else angler::hold();

		pros::delay(10);
	}
}
