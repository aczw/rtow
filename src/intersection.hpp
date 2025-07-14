#pragma once

#include "ray.hpp"
#include "vec3.hpp"

#include <memory>

namespace rtow {

/// Both files reference each other, so we break circular dependency here.
class BaseMaterial;

enum class Surface { Back, Front };

class Intersection {
 private:
  double t;
  Point3 point;
  Surface side;
  Vec3 normal;                                   ///< Normalized normal vector.
  std::shared_ptr<const BaseMaterial> material;  ///< Pointer to the material at the intersection point.

 public:
  Intersection(double t,
               const Point3& point,
               const Ray& ray,
               const Vec3& outward_normal,
               std::shared_ptr<const BaseMaterial> material);

  double get_t() const;
  const Vec3& get_point() const;
  const Vec3& get_normal() const;
};

}  // namespace rtow
