#pragma once

#include "main.h"
#include <memory>


namespace display {

  enum AssistState {
    STATE_NONE,
    STATE_GOOD,
    STATE_FORWARD,
    STATE_BACKWARD
  };

  inline lv_obj_t* img_deposit_assist = nullptr;

  void init();

  void set_assist_state(AssistState state);
}