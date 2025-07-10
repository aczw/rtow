#include "color.hpp"

namespace rtow {

constexpr double MAX_RGB_COLOR = 255.0;

void write_color(std::ostream& out, const Color& pixel_color) {
  double r = pixel_color.x();
  double g = pixel_color.y();
  double b = pixel_color.z();

  // Map [0, 1] component values to byte range [0, 255].
  long mapped_r = std::lround(MAX_RGB_COLOR * r);
  long mapped_g = std::lround(MAX_RGB_COLOR * g);
  long mapped_b = std::lround(MAX_RGB_COLOR * b);

  out << std::format("{} {} {}\n", mapped_r, mapped_g, mapped_b);
}

}  // namespace rtow
