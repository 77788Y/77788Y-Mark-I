#include "main.h"
#include "subsystems/lift.hpp"
#include "subsystems/angler.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/chassis_auton.hpp"
#include "subsystems/intake.hpp"

void autonomous() {
  
move_dist(4 * units::INCHES, -1, false);
rotate(90 * units::DEGREES);

}
