#pragma once

#include "base_material.hpp"
namespace rtow

{

class MetalMaterial : public BaseMaterial {
 public:
  MetalMaterial(const Color& albedo);

  std::optional<ScatterResult> scatter(const Ray& ray_in, const Intersection& isect) const override;

 private:
  Color albedo;
};

}  // namespace rtow
