#include "camera.hpp"
#include "hittable_list.hpp"
#include "material/dielectric_material.hpp"
#include "material/lambertian_material.hpp"
#include "material/metal_material.hpp"
#include "sphere.hpp"
#include "vec3.hpp"

#include <memory>

constexpr double ASPECT_RATIO = 16.0 / 9.0;
constexpr int IMAGE_WIDTH = 500;

using namespace rtow;

int main() {
  std::shared_ptr material_ground =
      std::make_shared<const LambertianMaterial>(Color(0.8, 0.8, 0.0));
  std::shared_ptr material_center =
      std::make_shared<const LambertianMaterial>(Color(0.1, 0.2, 0.5));
  std::shared_ptr material_left = std::make_shared<const DieletricMaterial>(1.5);
  std::shared_ptr material_right = std::make_shared<const MetalMaterial>(Color(0.8, 0.6, 0.2), 1.0);

  HittableList world;
  world.push_back(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
  world.push_back(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5, material_center));
  world.push_back(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
  world.push_back(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

  Camera camera(ASPECT_RATIO, IMAGE_WIDTH);
  camera.render(world);

  return 0;
}
