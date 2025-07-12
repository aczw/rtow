#include "camera.hpp"

#include "utils.hpp"

#include <algorithm>
#include <iostream>

namespace rtow {

Camera::Camera(double aspect_ratio, int image_width)
    : aspect_ratio(aspect_ratio),
      image_width(image_width),
      image_height(std::max(1, static_cast<int>(image_width / this->aspect_ratio))),
      focal_length(1.0),
      viewport_height(2.0),
      viewport_width(viewport_height * (static_cast<double>(image_width) / image_height)),
      viewport_x(viewport_width, 0.0, 0.0),
      viewport_y(0.0, -viewport_height, 0.0),
      center(),
      pixel_delta_x(viewport_x / image_width),
      pixel_delta_y(viewport_y / image_height),
      viewport_upper_left(center - Vec3(0.0, 0.0, focal_length) - (viewport_x * 0.5) - (viewport_y * 0.5)),
      first_pixel(viewport_upper_left + 0.5 * (pixel_delta_x + pixel_delta_y)) {}

Color Camera::calculate_ray_color(const Ray& ray, const IHittable& world) {
  if (std::optional<Intersection> isect_opt = world.hit(ray, Interval(0.0, Interval::Limits::infinity())); isect_opt) {
    // We've hit an object!
    const Intersection& isect = isect_opt.value();

    // Map normal vector [-1, 1] to color [0, 1]
    return 0.5 * (isect.get_normal() + Color(1.0, 1.0, 1.0));
  }

  // Else, draw the background (sky)
  Vec3 direction = ray.get_direction().normalized();
  double t = 0.5 * (direction.y() + 1.0);

  return lerp(Color(1.0, 1.0, 1.0), Color(0.5, 0.7, 1.0), t);
}

void Camera::render(const IHittable& world) {
  std::cout << std::format("P3\n{} {}\n255\n", image_width, image_height);

  for (int y = 0; y < image_height; y++) {
    std::clog << std::format("\rScanlines remaining: {} ", image_height - 1) << std::flush;

    for (int x = 0; x < image_width; x++) {
      Point3 pixel_center = first_pixel + (x * pixel_delta_x) + (y * pixel_delta_y);

      // Ray direction is not normalized, which is fine
      Ray ray(center, pixel_center - center);
      Color pixel_color = calculate_ray_color(ray, world);

      write_color(std::cout, pixel_color);
    }
  }

  // Extra spaces are a hack to overwrite previous text
  std::clog << "\rDone.                       \n";
}

}  // namespace rtow
