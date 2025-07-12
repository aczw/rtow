#include "utils.hpp"

#include <numbers>

namespace rtow {

double to_radians(double degrees) {
  return degrees * std::numbers::pi / 180.0;
}

Point3 sample_square() {
  return Point3(get_random() - 0.5, get_random() - 0.5, 0.0);
}

}  // namespace rtow
