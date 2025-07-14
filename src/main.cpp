#include "base_material.hpp"
#include "camera.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "vec3.hpp"

#include <memory>

constexpr double ASPECT_RATIO = 16.0 / 9.0;
constexpr int IMAGE_WIDTH = 500;

using namespace rtow;

int main() {
  std::shared_ptr base_material = std::make_shared<const BaseMaterial>();

  HittableList world;
  world.push_back(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, base_material));
  world.push_back(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, base_material));

  Camera camera(ASPECT_RATIO, IMAGE_WIDTH);
  camera.render(world);

  return 0;
}
