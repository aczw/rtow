#include "hittable_list.hpp"

#include <iostream>
#include <memory>
#include <optional>
#include <utility>
#include "ihittable.hpp"
#include "intersection.hpp"

namespace rtow {

HittableList::HittableList(std::shared_ptr<IHittable> object) : objects({object}) {}

void HittableList::clear() {
  objects.clear();
}

void HittableList::push_back(std::shared_ptr<IHittable> object) {
  objects.push_back(std::move(object));
}

void HittableList::push_back(std::shared_ptr<IHittable>&& object) {
  std::cerr << "move-version of push_back used!" << std::endl;
  objects.push_back(std::move(object));
}

std::optional<Intersection> HittableList::hit(const Ray& ray, double t_min, double t_max) const {
  std::optional<Intersection> result;
  double closest = t_max;

  for (const std::shared_ptr<IHittable>& object : objects) {
    if (std::optional<Intersection> result_opt = object->hit(ray, t_min, closest); result_opt) {
      const Intersection& object_result = result_opt.value();

      result = object_result;
      closest = object_result.get_t();
    }
  }

  return result;
}

}  // namespace rtow
