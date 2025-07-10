#pragma once

#include "vec3.hpp"

#include <ostream>

namespace rtow {

/// Useful for semantic meaning.
using Color = Vec3;

void write_color(std::ostream& out, const Color& pixel_color);

}  // namespace rtow
