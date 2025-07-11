#pragma once

#include <cmath>
#include <concepts>
#include <limits>

namespace rtow {

template <class T>
T lerp(T a, T b, double t) {
  return (1.0 - t) * a + t * b;
}

template <class T>
  requires std::floating_point<T>
bool approx_equal(T a, T b) {
  return std::fabs(a - b) <= std::numeric_limits<T>::epsilon();
}

double to_radians(double degrees);

}  // namespace rtow
