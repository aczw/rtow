#include "utils.hpp"

#include <cmath>
#include <numbers>

namespace rtow {

constexpr double GAMMA_VALUE = 2.2;
constexpr double INVERSE_GAMMA_VALUE = 1.0 / GAMMA_VALUE;

double to_radians(double degrees) {
  return degrees * std::numbers::pi / 180.0;
}

Point3 sample_square() {
  return Point3(get_random() - 0.5, get_random() - 0.5, 0.0);
}

double linear_to_gamma(double linear_component) {
  if (linear_component > 0.0) {
    return std::pow(linear_component, INVERSE_GAMMA_VALUE);
  }

  return 0.0;
}

}  // namespace rtow
