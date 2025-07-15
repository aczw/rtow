#include "intersection.hpp"

#include "utils.hpp"

#include <cassert>

namespace rtow {

Intersection::Intersection(double t,
                           const Point3& point,
                           const Ray& ray,
                           const Vec3& outward_normal,
                           std::shared_ptr<const BaseMaterial> material)
    : t(t),
      point(point),
      side(Vec3::dot(ray.get_direction(), outward_normal) < 0.0 ? Surface::Front : Surface::Back),
      normal(side == Surface::Front ? outward_normal : -outward_normal),
      material(material) {
  assert(approx_equal(outward_normal.length(), 1.0));
}

double Intersection::get_t() const {
  return t;
}

const Vec3& Intersection::get_point() const {
  return point;
}

const Vec3& Intersection::get_normal() const {
  return normal;
}

}  // namespace rtow
