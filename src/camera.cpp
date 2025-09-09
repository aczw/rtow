#include "camera.hpp"

#include "interval.hpp"
#include "material/base_material.hpp"
#include "ray.hpp"
#include "utils.hpp"

#include <algorithm>
#include <iostream>

namespace rtow {

Camera::Camera(double aspect_ratio, int image_width)
    : aspect_ratio(aspect_ratio),
      image_width(image_width),
      image_height(std::max(1, static_cast<int>(this->image_width / this->aspect_ratio))),
      max_depth(50),
      samples_per_pixel(100),
      pixel_samples_scale(1.0 / samples_per_pixel),
      focal_length(1.0),
      viewport_height(2.0),
      viewport_width(viewport_height * (static_cast<double>(this->image_width) / image_height)),
      viewport_x(viewport_width, 0.0, 0.0),
      viewport_y(0.0, -viewport_height, 0.0),
      center(),
      pixel_delta_x(viewport_x / this->image_width),
      pixel_delta_y(viewport_y / image_height),
      viewport_upper_left(center - Vec3(0.0, 0.0, focal_length) - (viewport_x * 0.5) - (viewport_y * 0.5)),
      first_pixel(viewport_upper_left + 0.5 * (pixel_delta_x + pixel_delta_y)) {}

Ray Camera::construct_ray(int x, int y) const {
  Point3 offset = sample_square();
  Point3 sample_point = first_pixel + ((x + offset.x()) * pixel_delta_x) + ((y + offset.y()) * pixel_delta_y);

  // Ray direction is not normalized, which is fine
  return Ray(center, sample_point - center);
}

Color Camera::calculate_ray_color(const Ray& ray, const IHittable& world, int bounce_number) {
  // Start a very small interval amount away from the intersection point to avoid self intersections
  static const Interval interval_to_check(0.001, Interval<>::infinity_value);

  // If we've exceeded the maximum number of bounces, then consider this ray hopeless
  if (bounce_number > max_depth) {
    return constants::black_color;
  }

  if (std::optional<Intersection> isect_opt = world.hit(ray, interval_to_check); isect_opt) {
    // We've hit an object!
    const Intersection& isect = isect_opt.value();

    // Use the geometry's material to calculate the next ray and attentuation
    if (std::optional<ScatterResult> result_opt = isect.get_material()->scatter(ray, isect); result_opt) {
      const ScatterResult& result = result_opt.value();
      return result.attenuation * calculate_ray_color(result.scattered, world, bounce_number + 1);
    }

    // If the ray was not scattered, then it was absorbed by this geometry
    return constants::black_color;
  }

  // Else, draw the background (sky)
  Vec3 direction = ray.get_direction().normalized();
  double t = 0.5 * (direction.y() + 1.0);

  return lerp(constants::white_color, Color(0.5, 0.7, 1.0), t);
}

void Camera::render(const IHittable& world) {
  std::cout << std::format("P3\n{} {}\n255\n", image_width, image_height);

  for (int y = 0; y < image_height; ++y) {
    std::clog << std::format("\rScanlines remaining: {} ", image_height - y) << std::flush;

    for (int x = 0; x < image_width; ++x) {
      Color pixel_color;

      for (int sample_num = 0; sample_num < samples_per_pixel; ++sample_num) {
        Ray ray = construct_ray(x, y);
        pixel_color += calculate_ray_color(ray, world, 0);
      }

      write_color(std::cout, pixel_samples_scale * pixel_color);
    }
  }

  std::clog << std::format("\rFinished processing image with resolution {}x{}.\n", image_width, image_height);
}

}  // namespace rtow
