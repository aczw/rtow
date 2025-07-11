#include "intersection.hpp"

namespace rtow {

Intersection::Intersection(double t, const Point3& point, const Ray& ray, const Vec3& outward_normal)
    : t(t),
      point(point),
      side(Vec3::dot(ray.get_direction(), outward_normal) < 0.0 ? Surface::Front : Surface::Back),
      normal(side == Surface::Front ? outward_normal : -outward_normal) {}

}  // namespace rtow
