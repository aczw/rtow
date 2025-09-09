#pragma once

#include "ihittable.hpp"
#include "material/base_material.hpp"
#include "vec3.hpp"

#include <memory>

namespace rtow {

class Sphere : public IHittable {
 private:
  Point3 center;
  double radius;
  std::shared_ptr<const BaseMaterial> material;

 public:
  Sphere(const Point3& center, double radius, std::shared_ptr<const BaseMaterial> material);

  std::optional<Intersection> hit(const Ray& ray, Interval<> ray_t) const override;
};

}  // namespace rtow
