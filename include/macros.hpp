#pragma once

#include "main.h"
#include <memory>

namespace macros {

  // macro codes
  enum Code {
    CODE_NONE = 0,
    CODE_INTERRUPT = 1,
    CODE_ANGLER_LIFT = 2,
    CODE_INTAKE_TOWER = 3
  };

  // current macro
  inline Code current = CODE_INTERRUPT;

  // functions
  bool run_angler_lift();
  bool run_intake_tower();

  // task
  inline std::unique_ptr<pros::Task> task = nullptr;

  // update current function
  inline void update(void*) {
    while (true) {

      // get notification
      Code code = (Code) task->notify_take(true, TIMEOUT_MAX);
      if (code != CODE_INTERRUPT) current = code;

      // execute correct function
      switch (code) {

        // move angler and stuff for lift
        case (CODE_ANGLER_LIFT): run_angler_lift(); break;

        // move intake for towers
        case (CODE_INTAKE_TOWER): run_intake_tower(); break;

        default: break;
      }

      current = CODE_NONE;
    }
  }

  // send a notification
  inline void notify(Code code) {

    task->notify_ext(code, pros::E_NOTIFY_ACTION_OWRITE, NULL);
  }

  // initialize task
  inline void init() {

    task = std::make_unique<pros::Task>(update, nullptr, "macros");
  }

}
