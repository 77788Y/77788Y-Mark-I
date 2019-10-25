#include "macros.hpp"
#include "subsystems/angler.hpp"
#include "subsystems/intake.hpp"
#include <cmath>

namespace macros {

  bool run_angler_lift() {

    // move angler
    subsystems::angler::m_motor.move_absolute(230, 100);
    if ((Code) task->notify_take(true, 500) == CODE_INTERRUPT) return false;
    return true;
  }
}