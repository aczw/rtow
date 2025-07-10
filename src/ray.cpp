#include "ray.hpp"

namespace rtow {

Ray::Ray(const Point3& origin, const Vec3& direction) : origin(origin), direction(direction) {}

const Point3& Ray::get_origin() const {
  return origin;
}

const Vec3& Ray::get_direction() const {
  return direction;
}

Point3 Ray::at(double t) const {
  return origin + t * direction;
}

}  // namespace rtow
