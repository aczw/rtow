#pragma once

#include "intersection.hpp"
#include "ray.hpp"

#include <optional>

namespace rtow {

class IHittable {
 public:
  IHittable() = default;

  IHittable(const IHittable&) = default;
  IHittable& operator=(const IHittable&) = default;

  IHittable(IHittable&&) noexcept = default;
  IHittable& operator=(IHittable&&) noexcept = default;

  virtual ~IHittable() = default;

  virtual std::optional<Intersection> hit(const Ray& ray, double t_min, double t_max) const = 0;
};

}  // namespace rtow
