#include "macros.hpp"
#include "subsystems/intake.hpp"
#include <cmath>

pros::ADIAnalogIn cube_detect('H');

namespace macros {

  bool run_intake_tower() {

    // move angler
    while (cube_detect.get_value() > 1700) {
      if ((Code) task->notify_take(true, 0) == CODE_INTERRUPT) return false;
      subsystems::intake::move_voltage(12000);
      pros::delay(10);
    }
    subsystems::intake::hold();
    return true;
  }
}
