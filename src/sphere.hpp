#pragma once

#include "ihittable.hpp"
#include "vec3.hpp"

namespace rtow {

class Sphere : public IHittable {
 private:
  Point3 center;
  double radius;

 public:
  Sphere(const Point3& center, double radius);

  std::optional<Intersection> hit(const Ray& ray, Interval ray_t) const override;
};

}  // namespace rtow
