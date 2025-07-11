#pragma once

#include <cmath>
#include <concepts>
#include <limits>

namespace rtow {

constexpr int NUM_EPSILONS = 5;

template <class T>
T lerp(T a, T b, double t) {
  return (1.0 - t) * a + t * b;
}

template <class T>
  requires std::floating_point<T>
bool approx_equal(T a, T b) {
  return std::fabs(a - b) < NUM_EPSILONS * std::numeric_limits<T>::epsilon();
}

double to_radians(double degrees);

}  // namespace rtow
