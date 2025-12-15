#pragma once

#include "base_material.hpp"

namespace rtow {

class DieletricMaterial : public BaseMaterial {
 public:
  explicit DieletricMaterial(double refraction_index);

  /// This dielectric material always refracts the ray, never reflects it.
  std::optional<ScatterResult> scatter(const Ray& incoming_ray,
                                       const Intersection& isect) const override;

 private:
  /// Either the refractive index in vaccuum or air, or the ratio of the material's
  /// refractive index over the refractive index of the enclosing medium.
  double refraction_index;
};

}  // namespace rtow
