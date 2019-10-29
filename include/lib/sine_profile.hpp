#pragma once

#include "lib/generic.hpp"
#include <iostream>

class SineProfile {

  public:

    // construct sine profile
    SineProfile(double from, double to, double over):
      amp(to - from), constant(from), width(over), sign(generic::sign(over))
    {}


    // get value along sine profile
    double get_at(double pos) {

      if (sign * pos < 0) return constant;
      if (sign * (width - pos) < 0) return constant;

      return
        (amp / 2) * -cos(M_PI * fabs(pos) / width) +
        amp / 2 +
        constant;
    }


  private:

    // sine params
    double amp;
    double constant;
    double width;
    int sign;

};
