#pragma once

#include "ray.hpp"
#include "vec3.hpp"

#include <optional>

namespace rtow {

class HitResult {
 private:
  Point3 intersection_point;
  Vec3 normal;
  double t;

 public:
  HitResult(const Point3& intersection_point, const Vec3& normal, double t);
};

class IHittable {
 public:
  IHittable() = default;

  IHittable(const IHittable&) = default;
  IHittable& operator=(const IHittable&) = default;

  IHittable(IHittable&&) noexcept = default;
  IHittable& operator=(IHittable&&) noexcept = default;

  virtual ~IHittable() = default;

  virtual std::optional<HitResult> hit(const Ray& ray, double t_min, double t_max) const = 0;
};

}  // namespace rtow
