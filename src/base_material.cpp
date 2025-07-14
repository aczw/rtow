#include "base_material.hpp"

namespace rtow {

std::optional<ScatterResult> BaseMaterial::scatter(const Ray&, const Intersection&) const {
  return std::nullopt;
}

}  // namespace rtow
