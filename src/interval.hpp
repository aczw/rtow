#pragma once

#include <cassert>
#include <limits>

namespace rtow {

template <class Num>
  requires std::numeric_limits<Num>::has_infinity
class IntervalBase {
 private:
  Num min;
  Num max;

 public:
  using Limits = std::numeric_limits<Num>;

  IntervalBase() : min(-Limits::infinity()), max(Limits::infinity()) {};
  IntervalBase(Num min, Num max) : min(min), max(max) {};

  Num get_min() const { return min; }
  Num get_max() const { return max; }

  bool contains(Num num) const { return min <= num && num <= max; }
  bool surrounds(Num num) const { return min < num && num < max; }

  Num length() const { return max - min; }

  static const IntervalBase<Num> empty;
  static const IntervalBase<Num> universe;
};

template <class Num>
  requires std::numeric_limits<Num>::has_infinity
const IntervalBase<Num> IntervalBase<Num>::empty(-Limits::infinity(), Limits::infinity());

template <class Num>
  requires std::numeric_limits<Num>::has_infinity
const IntervalBase<Num> IntervalBase<Num>::universe(Limits::infinity(), -Limits::infinity());

using Interval = IntervalBase<double>;

}  // namespace rtow
