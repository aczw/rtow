#pragma once

#include "../color.hpp"
#include "base_material.hpp"

namespace rtow {

/// A material that always randomly scatters the incoming ray. Attenuates the light with
/// its own reflectance, also known as albedo.
class LambertianMaterial : public BaseMaterial {
 public:
  explicit LambertianMaterial(const Color& albedo);

  std::optional<ScatterResult> scatter(const Ray& incoming_ray,
                                       const Intersection& isect) const override;

 private:
  Color albedo;
};

}  // namespace rtow
