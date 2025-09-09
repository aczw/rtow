#pragma once

#include "base_material.hpp"
#include "color.hpp"

namespace rtow {

/// A material that always randomly scatters the incoming ray. Attenuates the light with
/// its own reflectance, also known as albedo.
class LambertianMaterial : public BaseMaterial {
 public:
  LambertianMaterial(const Color& albedo);

  std::optional<ScatterResult> scatter(const Ray& incoming_ray, const Intersection& isect) const override;

 private:
  Color albedo;
};

}  // namespace rtow
