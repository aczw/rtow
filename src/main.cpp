#include "camera.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "vec3.hpp"

#include <memory>

constexpr double ASPECT_RATIO = 16.0 / 9.0;
constexpr int IMAGE_WIDTH = 1200;

using namespace rtow;

int main() {
  HittableList world;
  world.push_back(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5));
  world.push_back(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0));

  Camera camera(ASPECT_RATIO, IMAGE_WIDTH);
  camera.render(world);

  return 0;
}
