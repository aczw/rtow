#pragma once

#include <cassert>
#include <cmath>
#include <concepts>
#include <limits>
#include <random>

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

/// Returns a random real in [0.0, 1.0).
template <class Real = double>
  requires std::floating_point<Real>
Real get_random() {
  static const std::uniform_real_distribution<Real> distribution(0.0, 1.0);
  static const std::mt19937 generator;

  return distribution(generator);
}

/// Returns a random real in `[min, max)`.
template <class Real = double>
  requires std::floating_point<Real>
Real get_random(Real min, Real max) {
  assert(min <= max);

  return min + (max - min) * get_random<Real>();
}

}  // namespace rtow
