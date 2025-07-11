#pragma once

#include "ray.hpp"
#include "vec3.hpp"

namespace rtow {

enum class Surface { Back, Front };

class Intersection {
 private:
  double t;
  Point3 point;
  Surface side;
  Vec3 normal;

 public:
  Intersection(double t, const Point3& point, const Ray& ray, const Vec3& outward_normal);
};

}  // namespace rtow
