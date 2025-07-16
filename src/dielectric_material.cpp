#include "dielectric_material.hpp"

namespace rtow {

DieletricMaterial::DieletricMaterial(double refraction_index) : refraction_index(refraction_index) {}

std::optional<ScatterResult> DieletricMaterial::scatter(const Ray& incoming_ray, const Intersection& isect) const {
  // The refraction index used depends on which direction we're intersecting the material from. If the incoming
  // ray is coming from outside the material, then we need to inverse the refraction index because how it's stored
  // in the class assumes the initial index is the material, when in this case it's the surrounding medium.
  double ri_in_context = isect.get_side() == Surface::Front ? 1.0 / refraction_index : refraction_index;

  Vec3 incoming_ray_direction = incoming_ray.get_direction().normalized();
  Vec3 refracted_ray = Vec3::refract_about_normal(incoming_ray_direction, isect.get_normal(), ri_in_context);

  return ScatterResult{
      .attenuation = constants::white_color,
      .scattered = Ray(isect.get_point(), refracted_ray),
  };
}

}  // namespace rtow
