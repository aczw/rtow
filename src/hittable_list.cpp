#include "hittable_list.hpp"

#include "ihittable.hpp"
#include "intersection.hpp"
#include "interval.hpp"

#include <memory>
#include <optional>
#include <utility>

namespace rtow {

HittableList::HittableList(std::shared_ptr<IHittable> object) : objects({object}) {}

void HittableList::clear() {
  objects.clear();
}

void HittableList::push_back(std::shared_ptr<IHittable> object) {
  objects.push_back(std::move(object));
}

std::optional<Intersection> HittableList::hit(const Ray& ray, Interval<> ray_t) const {
  std::optional<Intersection> result;
  double min = ray_t.get_min();
  double closest = ray_t.get_max();

  for (const std::shared_ptr<IHittable>& object : objects) {
    if (std::optional<Intersection> isect_opt = object->hit(ray, Interval(min, closest)); isect_opt) {
      const Intersection& isect = isect_opt.value();
      result = isect;
      closest = isect.get_t();
    }
  }

  return result;
}

}  // namespace rtow
