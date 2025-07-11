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

  std::optional<HitResult> hit(const Ray& ray, double t_min, double t_max) const override;
};

}  // namespace rtow
