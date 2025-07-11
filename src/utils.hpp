#pragma once

namespace rtow {

template <class T>
T lerp(T a, T b, double t) {
  return (1.0 - t) * a + t * b;
}

}  // namespace rtow
