#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"

#include <algorithm>
#include <format>
#include <iostream>

constexpr double ASPECT_RATIO = 16.0 / 9.0;

constexpr int IMAGE_WIDTH = 400;
constexpr int IMAGE_HEIGHT = std::max(1, static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO));

constexpr double FOCAL_LENGTH = 1.0;
constexpr double VIEWPORT_HEIGHT = 2.0;
constexpr double VIEWPORT_WIDTH = VIEWPORT_HEIGHT * (static_cast<double>(IMAGE_WIDTH) / IMAGE_HEIGHT);

using namespace rtow;

namespace {

bool hit_sphere(const Point3& sphere_center, double radius, const Ray& ray) {
  Vec3 origin_to_sphere = ray.get_origin() - sphere_center;
  Vec3 ray_direction = ray.get_direction();

  // Calculate terms to find discriminant
  double a = Vec3::dot(ray_direction, ray_direction);
  double b = -2.0 * Vec3::dot(ray_direction, origin_to_sphere);
  double c = Vec3::dot(origin_to_sphere, origin_to_sphere) - (radius * radius);
  double discriminant = (b * b) - (4.0 * a * c);

  // Ray intersects sphere at least once
  return discriminant >= 0;
}

Color calculate_ray_color(const Ray& ray) {
  static const Color white(1.0, 1.0, 1.0);
  static const Color blue(0.5, 0.7, 1.0);

  static Point3 sphere_center(0.0, 0.0, -1.0);
  static double sphere_radius = 0.5;

  if (hit_sphere(sphere_center, sphere_radius, ray)) {
    return Color(1.0, 0.0, 0.0);
  }

  Vec3 direction = ray.get_direction().normalized();
  double t = 0.5 * (direction.y() + 1.0);

  return (1.0 - t) * white + t * blue;
}

}  // namespace

int main() {
  Point3 camera_center;

  // Calculate vectors across the horizontal and down the vertical viewport edges
  Vec3 viewport_x(VIEWPORT_WIDTH, 0.0, 0.0);
  Vec3 viewport_y(0.0, -VIEWPORT_HEIGHT, 0.0);

  // Calculate horizontal and vertical deltas from pixel to pixel
  Vec3 pixel_delta_x = viewport_x / IMAGE_WIDTH;
  Vec3 pixel_delta_y = viewport_y / IMAGE_HEIGHT;

  // Calculate coordinate of upper left viewport pixel
  Point3 viewport_upper_left = camera_center - Vec3(0.0, 0.0, FOCAL_LENGTH) - (viewport_x * 0.5) - (viewport_y * 0.5);
  Point3 pixel_00 = viewport_upper_left + (pixel_delta_x * 0.5) + (pixel_delta_y * 0.5);

  std::cout << std::format("P3\n{} {}\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

  for (int y = 0; y < IMAGE_HEIGHT; y++) {
    std::clog << std::format("\rScanlines remaining: {} ", IMAGE_HEIGHT - 1) << std::flush;

    for (int x = 0; x < IMAGE_WIDTH; x++) {
      Point3 pixel_center = pixel_00 + (x * pixel_delta_x) + (y * pixel_delta_y);

      // Ray direction is not normalized, which is fine
      Ray ray(camera_center, pixel_center - camera_center);
      Color pixel_color = calculate_ray_color(ray);

      write_color(std::cout, pixel_color);
    }
  }

  // Extra spaces are a hack to overwrite previous text
  std::clog << "\rDone.                       \n";

  return 0;
}
