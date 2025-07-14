#pragma once

#include <array>
#include <format>
#include <string_view>

namespace rtow {

class Vec3 {
 private:
  std::array<double, 3> data;

 public:
  Vec3();
  Vec3(double v0, double v1, double v2);

  double x() const;
  double y() const;
  double z() const;

  double length() const;
  double length_squared() const;
  Vec3 normalized() const;

  Vec3 operator-() const;

  double operator[](int index) const;
  double& operator[](int index);

  Vec3& operator+=(const Vec3& v);
  Vec3& operator-=(const Vec3& v);
  Vec3& operator*=(double n);
  Vec3& operator/=(double n);

  static double dot(const Vec3& v1, const Vec3& v2);
  static Vec3 cross(const Vec3& v1, const Vec3& v2);
  static Vec3 normalize(const Vec3& v);

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
