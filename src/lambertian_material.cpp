#include "lambertian_material.hpp"

namespace rtow {

LambertianMaterial::LambertianMaterial(const Color& albedo) : albedo(albedo) {}

std::optional<ScatterResult> LambertianMaterial::scatter(const Ray&, const Intersection& isect) const {
  Vec3 isect_normal = isect.get_normal();

  // Pick a point on the unit sphere that is tangent to the geometry's surface at the intersection point
  Vec3 scatter_direction = isect_normal + Vec3::get_random_unit_vector();

  // Catch degenerate scatter direction
  if (scatter_direction.near_zero()) {
    scatter_direction = isect_normal;
  }

  return ScatterResult{
      .scattered = Ray(isect.get_point(), scatter_direction),
      .attenuation = albedo,
  };
}

}  // namespace rtow
