#pragma once

#include "vec3.hpp"

#include <cassert>
#include <cmath>
#include <concepts>
#include <limits>
#include <random>

namespace rtow {

/// Constant not used anywhere else, so let's enforce internal linkage for now
static constexpr int NUM_EPSILONS = 1'000'000;

template <class T>
T lerp(T a, T b, double t) {
  return (1.0 - t) * a + t * b;
}

template <class T>
  requires std::floating_point<T>
bool approx_equal(T a, T b) {
  return std::fabs(a - b) < static_cast<T>(NUM_EPSILONS) * std::numeric_limits<T>::epsilon();
}

double to_radians(double degrees);

/// Returns a random real value in [0.0, 1.0).
template <class Real = double>
  requires std::floating_point<Real>
Real get_random() {
  static std::random_device rd;
  static std::mt19937 generator(rd());
  static std::uniform_real_distribution<Real> distribution(0.0, 1.0);

  return distribution(generator);
}

/// Returns a random real value in `[min, max)`.
template <class Real = double>
  requires std::floating_point<Real>
Real get_random(Real min, Real max) {
  assert(min <= max);

  return min + (max - min) * get_random<Real>();
}

/// Returns a random point in a unit square centered at the origin.
///
/// @note This means the bounds of the square are [-0.5, -0.5] to [0.5, 0.5].
Point3 sample_square();

double linear_to_gamma(double linear_component);

}  // namespace rtow
