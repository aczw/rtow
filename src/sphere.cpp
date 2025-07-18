#include "sphere.hpp"

#include "vec3.hpp"

#include <cmath>
#include <optional>

namespace rtow {

Sphere::Sphere(const Point3& center, double radius, std::shared_ptr<const BaseMaterial> material)
    : center(center), radius(std::fmax(0.0, radius)), material(material) {}

std::optional<Intersection> Sphere::hit(const Ray& ray, Interval<> ray_t) const {
  Vec3 origin_to_sphere = center - ray.get_origin();
  Vec3 ray_direction = ray.get_direction();

  // Calculate terms to find discriminant
  double a = Vec3::dot(ray_direction, ray_direction);
  double h = Vec3::dot(ray_direction, origin_to_sphere);
  double c = origin_to_sphere.length_squared() - (radius * radius);

  double discriminant = (h * h) - (a * c);

  if (discriminant < 0.0) {
    return std::nullopt;
  }

  double sqrt_discriminant = std::sqrt(discriminant);

  // Find the nearest root that lies in the acceptable interval
  double root = (h - sqrt_discriminant) / a;
  if (!ray_t.surrounds(root)) {
    root = (h + sqrt_discriminant) / a;

    if (!ray_t.surrounds(root)) {
      return std::nullopt;
    }
  }

  Point3 intersection_point = ray.at(root);
  Vec3 outward_normal = (intersection_point - center) / radius;

  return Intersection(root, intersection_point, ray, outward_normal, material);
}

}  // namespace rtow
