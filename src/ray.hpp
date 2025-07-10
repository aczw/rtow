#pragma once

#include "vec3.hpp"

namespace rtow {

class Ray {
 private:
  Point3 origin;
  Vec3 direction;

 public:
  Ray(const Point3& origin, const Vec3& direction);

  const Point3& get_origin() const;
  const Vec3& get_direction() const;

  Point3 at(double t) const;
};

}  // namespace rtow
