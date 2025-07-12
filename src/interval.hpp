#pragma once

#include <cassert>
#include <limits>

namespace rtow {

template <class Real = double>
  requires std::numeric_limits<Real>::has_infinity
class Interval {
 private:
  Real min;
  Real max;

 public:
  static constexpr Real infinity_value = std::numeric_limits<Real>::infinity();

  Interval() : min(-infinity_value), max(infinity_value) {};
  Interval(Real min, Real max) : min(min), max(max) {};

  Real get_min() const { return min; }
  Real get_max() const { return max; }

  bool contains(Real num) const { return min <= num && num <= max; }
  bool surrounds(Real num) const { return min < num && num < max; }

  Real clamp(Real num) const {
    if (num < min) return min;
    if (num > max) return max;
    return num;
  }

  Real length() const { return max - min; }

  static const Interval empty;
  static const Interval universe;
};

template <class Real>
  requires std::numeric_limits<Real>::has_infinity
const Interval<Real> Interval<Real>::empty(infinity_value, -infinity_value);

template <class Real>
  requires std::numeric_limits<Real>::has_infinity
const Interval<Real> Interval<Real>::universe(-infinity_value, infinity_value);

}  // namespace rtow
