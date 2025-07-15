#include "metal_material.hpp"

namespace rtow {

MetalMaterial::MetalMaterial(const Color& albedo) : albedo(albedo) {}

std::optional<ScatterResult> MetalMaterial::scatter(const Ray& ray_in, const Intersection& isect) const {
  Vec3 reflected_direction = Vec3::reflect_about_normal(ray_in.get_direction(), isect.get_normal());

  return ScatterResult{
      .scattered = Ray(isect.get_point(), reflected_direction),
      .attenuation = albedo,
  };
}

}  // namespace rtow
