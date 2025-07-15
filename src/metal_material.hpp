#pragma once

#include "base_material.hpp"
namespace rtow

{

class MetalMaterial : public BaseMaterial {
 public:
  MetalMaterial(const Color& albedo);
  MetalMaterial(const Color& albedo, double fuzz);

  std::optional<ScatterResult> scatter(const Ray& ray_in, const Intersection& isect) const override;

 private:
  Color albedo;
  double fuzz;  ///< Value between 0 and 1 that adds variation to the reflected ray, creating fuzzy surfaces.
};

}  // namespace rtow
