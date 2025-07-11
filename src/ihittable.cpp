#include "ihittable.hpp"

namespace rtow {

HitResult::HitResult(const Point3& intersection_point, const Vec3& normal, double t)
    : intersection_point(intersection_point), normal(normal), t(t) {}

}  // namespace rtow
