#include "utils.hpp"

#include <numbers>

namespace rtow {

double to_radians(double degrees) {
  return degrees * std::numbers::pi / 180.0;
}

}  // namespace rtow
