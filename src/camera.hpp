#pragma once

#include "color.hpp"
#include "ihittable.hpp"
#include "ray.hpp"
#include "vec3.hpp"

namespace rtow {

class Camera {
 private:
  double aspect_ratio;  ///< Ideal ratio of image width over height.
  int image_width;      ///< Actual rendered image width in pixel count.
  int image_height;     ///< Actual rendered image height in pixel height.
  double focal_length;  ///< Distance between camera center and viewport.
  double viewport_height;
  double viewport_width;
  Vec3 viewport_x;
  Vec3 viewport_y;
  Point3 center;
  Vec3 pixel_delta_x;        ///< Horizontal offset from pixel to pixel.
  Vec3 pixel_delta_y;        ///< Vertical offset from pixel to pixel.
  Vec3 viewport_upper_left;  ///< Coordinate of upper left most viewport corner.
  Point3 first_pixel;        ///< Location of the first pixel at (0, 0).

 public:
  Camera(double aspect_ratio, int image_width);

  Color calculate_ray_color(const Ray& ray, const IHittable& world);
  void render(const IHittable& world);
};

}  // namespace rtow
