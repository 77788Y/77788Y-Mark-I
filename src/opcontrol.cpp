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

// declare and define vision
pros::Vision vision(21);


// line-up alert
void lineup_alert(void*) {
	while (true) {

		// update signature
		auto sig = vision.get_by_sig(0, 1);

		// check if in range
		if (sig.height > 100 && sig.width > 250 && abs(sig.x_middle_coord - 158) <= 50 && abs(sig.top_coord) <= 30 && abs(sig.top_coord + sig.height - 135) <= 15) {

			// do controller stuff
			controller.controller.set_text(0, 0, "               ");
			pros::delay(50);
			controller.controller.set_text(1, 0, "    IN THE YARD");
			pros::delay(50);
			controller.controller.set_text(2, 0, "               ");
			pros::delay(100);
			controller.controller.rumble("-");
			std::cout << "entered" << std::endl;
			pros::delay(50);

			// wait until out of range
			sig = vision.get_by_sig(0, 1);
			while (sig.height > 100 && sig.width > 250 && abs(sig.x_middle_coord - 158) <= 60 && abs(sig.top_coord) <= 40 && abs(sig.top_coord + sig.height - 135) <= 35) {

				pros::delay(20);
				sig = vision.get_by_sig(0, 1);
			}

			// do controller stuff
			controller.controller.set_text(0, 0, "               ");
			pros::delay(50);
			controller.controller.set_text(1, 0, "               ");
			pros::delay(50);
			controller.controller.set_text(2, 0, "               ");
			pros::delay(100);
			controller.controller.rumble(".");
			std::cout << "exited" << std::endl;
			pros::delay(300);
		}

		pros::delay(20);
	}
}



void opcontrol() {

  // initialize macros
  macros::init();

	// start vision task
	pros::Task vision_task(lineup_alert, nullptr, "lineup alert");

	// clear controller screen
	controller.controller.set_text(0, 0, "               ");
	pros::delay(50);
	controller.controller.set_text(1, 0, "               ");
	pros::delay(50);
	controller.controller.set_text(2, 0, "               ");

	// lift control data
	uint8_t lift_btn_count = 0;
	units::Time lift_last_press = pros::millis();

	while (true) {

		// update controller
		controller.update();

		// dirty hack to disable angler
		if (macros::current == macros::CODE_ANGLER_LIFT && (controller.btn_r1 || controller.btn_r2 || controller.btn_x || controller.btn_b || controller.btn_a)) {
			macros::notify(macros::CODE_INTERRUPT);
			pros::delay(2);
		}

		// move angler for lift macro
		if (controller.btn_y_new == 1) {
			macros::notify(macros::CODE_ANGLER_LIFT);
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
		if (controller.btn_l2_new == 1) lift::goto_async(lift::POS_MIN);
		if (controller.btn_l1_new == 1) {
			++lift_btn_count;
			lift_last_press = pros::millis();
		}
		if ((pros::millis() - lift_last_press >= 300 && lift_btn_count > 0) || lift_btn_count >= 2) {

			// move lift
			switch (lift_btn_count) {
				default: break;
				case 1: lift::goto_async(lift::POS_LOW_TOWER);
				case 2: lift::goto_async(lift::POS_HIGH_TOWER);
			}

			lift_btn_count = 0;
		}

		if (macros::current != macros::CODE_ANGLER_LIFT) {

			// intake
			if ((controller.btn_r1 - controller.btn_r2) && !(controller.btn_b || controller.btn_x)) intake::move_voltage((controller.btn_r1 - controller.btn_r2) * 12000);
			else if (controller.btn_a) intake::move_voltage(-1000);
			else if (controller.btn_b - controller.btn_x) intake::move_voltage((controller.btn_b - controller.btn_x) * 1000);
			else intake::hold();

			// angler
			if (controller.btn_a) angler::update_auto_deposit();
			else if (controller.btn_x - controller.btn_b) angler::move_voltage((controller.btn_x - controller.btn_b) * 12000);
			else angler::hold();
		}

		// debug
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
