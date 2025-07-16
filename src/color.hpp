#pragma once

#include "vec3.hpp"

#include <ostream>

namespace rtow {

/// Useful for semantic meaning.
using Color = Vec3;

void write_color(std::ostream& out, const Color& pixel_color);

namespace constants {

constexpr Color black_color = Color(0.0, 0.0, 0.0);
constexpr Color white_color = Color(1.0, 1.0, 1.0);

}  // namespace constants

}  // namespace rtow
