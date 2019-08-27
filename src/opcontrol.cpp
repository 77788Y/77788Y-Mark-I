#include "main.h"
#include "lib/joystick.hpp"
#include "subsystems/chassis.hpp"

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

		pros::delay(10);
	}
}
