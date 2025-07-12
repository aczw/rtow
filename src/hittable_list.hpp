#pragma once

#include "ihittable.hpp"
#include "interval.hpp"

#include <memory>
#include <vector>

namespace rtow {

class HittableList : public IHittable {
 private:
  std::vector<std::shared_ptr<IHittable>> objects;

 public:
  HittableList() = default;
  HittableList(std::shared_ptr<IHittable> object);

  void clear();

  void push_back(std::shared_ptr<IHittable> object);

  std::optional<Intersection> hit(const Ray& ray, Interval<> ray_t) const override;
};

}  // namespace rtow
