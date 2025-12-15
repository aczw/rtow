#include "dielectric_material.hpp"

#include "../utils.hpp"

namespace rtow {

DieletricMaterial::DieletricMaterial(double refraction_index)
    : refraction_index(refraction_index) {}

std::optional<ScatterResult> DieletricMaterial::scatter(const Ray& incoming_ray,
                                                        const Intersection& isect) const {
  // The refraction index used depends on which direction we're intersecting the material from. If
  // the incoming ray is coming from outside the material, then we need to inverse the refraction
  // index because how it's stored in the class assumes the initial index is the material, when in
  // this case it's the surrounding medium.
  double ri_in_ctx = isect.get_side() == Surface::Front ? 1.0 / refraction_index : refraction_index;

  Vec3 incoming_ray_dir = incoming_ray.get_direction().normalized();
  double cos_theta = std::fmin(Vec3::dot(-incoming_ray_dir, isect.get_normal()), 1.0);
  double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

  Vec3 new_ray_dir = [&]() -> Vec3 {
    // Check if total internal reflection has occurred
    bool cannot_refract = ri_in_ctx * sin_theta > 1.0;

    // Factor in Fresnel term by randomly choosing to reflect the incoming ray
    if (cannot_refract || reflectance(cos_theta, ri_in_ctx) > get_random()) {
      return Vec3::reflect_about_normal(incoming_ray_dir, isect.get_normal());
    } else {
      return Vec3::refract_about_normal(incoming_ray_dir, isect.get_normal(), ri_in_ctx);
    }
  }();

  return ScatterResult{
      .attenuation = constants::color::WHITE,
      .scattered = Ray(isect.get_point(), new_ray_dir),
  };
}

double DieletricMaterial::reflectance(double cosine, double refraction_index) {
  double r0 = (1.0 - refraction_index) / (1.0 + refraction_index);
  r0 = r0 * r0;

  return r0 + (1.0 - r0) * std::pow(1.0 - cosine, 5.0);
}

}  // namespace rtow
