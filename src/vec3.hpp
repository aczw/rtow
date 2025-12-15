#pragma once

#include <array>
#include <format>
#include <string_view>

namespace rtow {

class Vec3 {
 private:
  std::array<double, 3> data;

 public:
  constexpr Vec3() : data({0.0, 0.0, 0.0}) {}

  constexpr Vec3(double v0, double v1, double v2) : data({v0, v1, v2}) {}

  double x() const;
  double y() const;
  double z() const;

  double length() const;
  double length_squared() const;
  Vec3 normalized() const;

  /// Returns true if all components of the vector are near zero.
  bool near_zero() const;

  Vec3 operator-() const;

  double operator[](size_t index) const;
  double& operator[](size_t index);

  Vec3& operator+=(const Vec3& v);
  Vec3& operator-=(const Vec3& v);
  Vec3& operator*=(double n);
  Vec3& operator/=(double n);

  static double dot(const Vec3& v1, const Vec3& v2);
  static Vec3 cross(const Vec3& v1, const Vec3& v2);
  static Vec3 normalize(const Vec3& v);

  /// Reflects `vector` about a `normal`. Assumes `normal` is a unit vector.
  static Vec3 reflect_about_normal(const Vec3& vector, const Vec3& normal);

  /// Refracts an incoming `vector` using `normal` as a frame of reference. The direction of
  /// `normal` should be perpendicular to the initial and final material's surface. It's assumed the
  /// two materials meet each other at a straight line.
  static Vec3 refract_about_normal(const Vec3& vector, const Vec3& normal, double eta_i_over_eta_f);

  static Vec3 get_random_unit_vector();
  static Vec3 get_random_on_hemisphere(const Vec3& normal);
  static Vec3 get_random();
  static Vec3 get_random(double min, double max);
};

Vec3 operator+(const Vec3& v1, const Vec3& v2);
Vec3 operator-(const Vec3& v1, const Vec3& v2);
Vec3 operator*(const Vec3& v1, const Vec3& v2);
Vec3 operator*(double n, const Vec3& v2);
Vec3 operator*(const Vec3& v1, double n);
Vec3 operator/(const Vec3& v1, double n);

std::ostream& operator<<(std::ostream& out, const Vec3& v);

/// Useful for semantic meaning.
using Point3 = Vec3;

}  // namespace rtow

template <>
struct std::formatter<rtow::Vec3> : std::formatter<std::string_view> {
  auto format(const rtow::Vec3& v, auto& ctx) const {
    return std::format_to(ctx.out(), "[{:.3f}, {:.3f}, {:.3f}]", v[0], v[1], v[2]);
  }
};
