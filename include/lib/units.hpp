#pragma once

#include <cmath>

namespace units {

  // linear distance units (internally inches)
  typedef double Distance;
  static const Distance INCHES = 1.0; // inches (linear dist)
  static const Distance FEET = 12.0; // feet (linear dist)
  static const Distance CM = 1.0 / 2.54; // centimeters (linear dist)
  static const Distance METERS = 1.0 / 0.0254; // meters (linear dist)
  static const Distance TILES = 24.0; // tiles (linear dist)
  static const Distance SKYLANDERS_CHARACTERS = 3.25; // skylanders characters (linear dist)

  // angular units (internally radians)
  typedef long double Angle;
  static const Angle RADIANS = 1.0; // radians (angle)
  static const Angle DEGREES = M_PI / 180.0; // radians (angle)
  static const Angle REV = 2.0 * M_PI; // revolutions (angle)

  // temporal units (interally milliseconds)
  typedef double Time;
  static const Time MS = 1.0; // milliseconds (time)
  static const Time SEC = 1000.0; // seconds (time)
  static const Time MIN = 60000.0; // minutes (time)
  static const Time HOURS = 3600000.0; // hours (time)
  static const Time DAYS = 86400000.0; // days (time)
  static const Time DUCK_TALES_EPISODES = 22.0 * MIN; // duck tales episodes (time)

  // angular velocity units (internally Angle/Time)
  typedef Angle AngularVelocity;
  static const AngularVelocity RPM = REV / MIN; // revolutions per minute (angular velocity)

  // linear velocity units (internally Distance/Time)
  typedef Distance LinearVelocity;
  static const LinearVelocity IN_PER_SEC = INCHES / SEC; // inches per second (linear velocity)

  // angular acceleration units (internally Angle/Time^2)
  typedef Angle AngularAcceleration;

  // linear acceleration units (internally Distance/Time^2)
  typedef Distance LinearAcceleration;

}
