#include "main.h"
#include "macros.hpp"
#include "lib/joystick.hpp"
#include "lib/generic.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/lift.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/angler.hpp"

// import subsystems into current namespace
using namespace subsystems;

// declare and define controller
Joystick controller;

void opcontrol() {

  // initialize macros
  macros::init();

	// lift control data
	int lift_index = 0;
	units::Angle lift_angles[] = {lift::POS_MIN, lift::POS_LOW_TOWER, lift::POS_HIGH_TOWER};

	while (true) {

		// update controller
		controller.update();

		// dirty hack to disable angler
		if (macros::current == macros::CODE_ANGLER_LIFT && (controller.btn_r1 || controller.btn_r2 || controller.btn_x || controller.btn_b || controller.btn_a)) {
			macros::notify(macros::CODE_INTERRUPT);
			pros::delay(2);
		}

		// drive
		if (controller.btn_r1 && controller.btn_r2) chassis::hold();
		else {

			// exponential drive
			double left  = (.25 * pow(5, fabs(controller.analog_left_y))  - .25) * generic::sign(controller.analog_left_y);
			double right = (.25 * pow(5, fabs(controller.analog_right_y)) - .25) * generic::sign(controller.analog_right_y);

			chassis::move_voltage(left * 12000.0, right * 12000.0);
		}

		// lift
		if (controller.btn_l1_new == 1) {

			++lift_index;
			if (lift_index > 2) lift_index = 2;
			lift::goto_async(lift_angles[lift_index]);
		}
		else if (controller.btn_l2_new == 1) {

			lift_index = 0;
			lift::goto_async(lift_angles[lift_index]);
		}

		if (macros::current != macros::CODE_ANGLER_LIFT) {

			// intake
			if ((controller.btn_r1 - controller.btn_r2) && !(controller.btn_b || controller.btn_x)) intake::move_voltage((controller.btn_r1 - controller.btn_r2) * 12000);
			else if (controller.btn_a) intake::move_voltage(-1000);
			else if (controller.btn_b - controller.btn_x) intake::move_voltage((controller.btn_b - controller.btn_x) * 1000);
			else intake::hold();

			// angler
			if (controller.btn_a) angler::update_auto_deposit();
			else if (controller.btn_b_new == 1 and lift::pos < (lift::POS_MIN + 5 * units::DEGREES)) angler::m_motor.move_absolute(0, 100);
			else angler::hold();
		}

		// debug
		// if (controller.btn_left) chassis::tare_orientation(90 * units::DEGREES);
		if (true && pros::millis() % 250 <= 10) {

			std::cout << "Angler angle:  " << angler::pos / units::DEGREES << "°" << std::endl;
			std::cout << "Lift angle:    " << angler::pos / units::DEGREES << "°" << std::endl;
			std::cout << "Chassis Left:  " << chassis::dist_l << "\"" << std::endl;
			std::cout << "Chassis Right: " << chassis::dist_r << "\"" << std::endl;
			std::cout << "Chassis Angle: " << chassis::orientation / units::DEGREES << "°" << std::endl << std::endl;
		}

		pros::delay(10);
	}
}
