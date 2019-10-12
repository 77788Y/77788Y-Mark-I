#include "macros.hpp"
#include "subsystems/angler.hpp"
#include "subsystems/intake.hpp"
#include <cmath>

namespace macros {

  bool run_angler_lift() {

    // move intake to correct position
    subsystems::intake::m_left.move_absolute(floor(subsystems::intake::m_left.get_position() / 360.0), 200);
    subsystems::intake::m_right.move_absolute(floor(subsystems::intake::m_right.get_position() / 360.0), 200);
    if ((Code) task->notify_take(true, 500) == CODE_NONE) return false;

    // move angler
    subsystems::angler::m_motor.move_absolute(20, 100);
    if ((Code) task->notify_take(true, 500) == CODE_NONE) return false;
    return true;
  }
}