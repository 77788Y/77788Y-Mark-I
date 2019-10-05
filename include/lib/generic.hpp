#pragma once

#include <cmath>

namespace generic {

  // return sign of a value
  template <typename T>
  inline T sign(T val) {
    return val / fabs(val);
  }


  // clamp a value between two limits
  inline double clamp(double val, double min, double max) {
    if (val < min) return min;
    if (val > max) return max;
    return val;
  }


  // wrap a value around two limits
  inline int wrap(int val, int min, int max) {
    return (val - min) % (max - min) + max;
  }
  inline double wrap(double val, double min, double max) {
    if (val > max) return wrap(val - (max - min), min, max);
    if (val < min) return wrap(val + (max - min), min, max);
    return val;
  }
}