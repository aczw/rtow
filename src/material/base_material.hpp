#pragma once

#include "../color.hpp"
#include "../intersection.hpp"
#include "../ray.hpp"

#include <optional>

namespace rtow {

struct ScatterResult {
  Color attenuation;
  Ray scattered;
};

class BaseMaterial {
 public:
  BaseMaterial() = default;

  BaseMaterial(const BaseMaterial&) = default;
  BaseMaterial& operator=(const BaseMaterial&) = default;

  BaseMaterial(BaseMaterial&&) noexcept = default;
  BaseMaterial& operator=(BaseMaterial&&) noexcept = default;

  virtual ~BaseMaterial() = default;

  virtual std::optional<ScatterResult> scatter(const Ray& incoming_ray,
                                               const Intersection& isect) const;
};

}  // namespace rtow
