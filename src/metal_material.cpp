#include "metal_material.hpp"

#include <algorithm>

namespace rtow {

MetalMaterial::MetalMaterial(const Color& albedo) : albedo(albedo), fuzz(0.0) {}

MetalMaterial::MetalMaterial(const Color& albedo, double fuzz) : albedo(albedo), fuzz(std::clamp(fuzz, 0.0, 1.0)) {}

std::optional<ScatterResult> MetalMaterial::scatter(const Ray& incoming_ray, const Intersection& isect) const {
  Vec3 isect_normal = isect.get_normal();
  Vec3 reflected_direction = Vec3::reflect_about_normal(incoming_ray.get_direction(), isect_normal);
  reflected_direction = reflected_direction.normalized() + (fuzz * Vec3::get_random_unit_vector());

  // For particular fuzz values, the resulting ray might travel "through" the geometry. In this case,
  // simply act as if the scattered ray has been absorbed
  if (Vec3::dot(reflected_direction, isect_normal) < 0.0) return std::nullopt;

  return ScatterResult{
      .attenuation = albedo,
      .scattered = Ray(isect.get_point(), reflected_direction),
  };
}

}  // namespace rtow
