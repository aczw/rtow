#include "vec3.hpp"

#include "utils.hpp"

#include <cassert>
#include <cmath>
#include <format>
#include <iostream>

namespace rtow {

/// The biggest value where multiplication between two of these may underflow to zero due to
/// finite precision issues.
constexpr double WILL_UNDERFLOW = 1e-160;

double Vec3::x() const {
  return data[0];
}

double Vec3::y() const {
  return data[1];
}

double Vec3::z() const {
  return data[2];
}

double Vec3::length() const {
  return std::sqrt(length_squared());
}

double Vec3::length_squared() const {
  return dot(*this, *this);
}

Vec3 Vec3::normalized() const {
  return Vec3::normalize(*this);
}

bool Vec3::near_zero() const {
  return approx_equal(data[0], 0.0) && approx_equal(data[1], 0.0) && approx_equal(data[2], 0.0);
}

Vec3 Vec3::operator-() const {
  return Vec3(-data[0], -data[1], -data[2]);
}

double Vec3::operator[](int index) const {
  return data[index];
}

double& Vec3::operator[](int index) {
  return data[index];
}

Vec3& Vec3::operator+=(const Vec3& v) {
  data[0] += v.data[0];
  data[1] += v.data[1];
  data[2] += v.data[2];

  return *this;
}

Vec3& Vec3::operator-=(const Vec3& v) {
  return operator+=(-v);
}

Vec3& Vec3::operator*=(double n) {
  data[0] *= n;
  data[1] *= n;
  data[2] *= n;

  return *this;
}

Vec3& Vec3::operator/=(double n) {
  return operator*=(1.0 / n);
}

double Vec3::dot(const Vec3& v1, const Vec3& v2) {
  return v1.data[0] * v2.data[0] + v1.data[1] * v2.data[1] + v1.data[2] * v2.data[2];
}

Vec3 Vec3::cross(const Vec3& v1, const Vec3& v2) {
  return Vec3(v1.data[1] * v2.data[2] - v1.data[2] * v2.data[1], v1.data[2] * v2.data[0] - v1.data[0] * v2.data[2],
              v1.data[0] * v2.data[1] - v1.data[1] * v2.data[0]);
}

Vec3 Vec3::normalize(const Vec3& v) {
  return v / v.length();
}

Vec3 Vec3::reflect_about_normal(const Vec3& vector, const Vec3& normal) {
  assert(approx_equal(normal.length(), 1.0));

  // Find the length of the projection of `vector` on to `normal` and construct a new vector using it
  double length = dot(vector, normal);
  Vec3 b = length * normal;

  // In our system, `vector` is always pointing into the surface while `normal` is pointing out.
  // Therefore the projection direction is backwards and we need to flip it.
  b = -b;

  return vector + 2 * b;
}

Vec3 Vec3::refract_about_normal(const Vec3& vector, const Vec3& normal, double eta_i_over_eta_f) {
  assert(approx_equal(vector.length(), 1.0));
  assert(approx_equal(normal.length(), 1.0));

  // Derived from Snell's Law
  double cos_theta = std::fmin(dot(-vector, normal), 1.0);
  Vec3 refracted_ray_perp = eta_i_over_eta_f * (vector + cos_theta * normal);
  Vec3 refracted_ray_parallel = -std::sqrt(std::fabs(1.0 - refracted_ray_perp.length_squared())) * normal;

  return refracted_ray_perp + refracted_ray_parallel;
}

Vec3 Vec3::get_random_unit_vector() {
  while (true) {
    Point3 generated_point = get_random(-1.0, 1.0);
    double length_squared = generated_point.length_squared();

    // Check whether x^2 + y^2 + z+2 <= 1, aka we're inside the unit sphere
    if (WILL_UNDERFLOW < length_squared && length_squared <= 1.0) {
      return generated_point / std::sqrt(length_squared);
    }
  }
}

Vec3 Vec3::get_random_on_hemisphere(const Vec3& normal) {
  Vec3 unit_vector = get_random_unit_vector();

  // If dot product is positive, then generated sample is in the hemisphere represented by the normal
  if (dot(unit_vector, normal) > 0.0) {
    return unit_vector;
  } else {
    return -unit_vector;
  }
}

Vec3 Vec3::get_random() {
  return Vec3(rtow::get_random(), rtow::get_random(), rtow::get_random());
}

Vec3 Vec3::get_random(double min, double max) {
  return Vec3(rtow::get_random(min, max), rtow::get_random(min, max), rtow::get_random(min, max));
}

Vec3 operator+(const Vec3& v1, const Vec3& v2) {
  return Vec3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

Vec3 operator-(const Vec3& v1, const Vec3& v2) {
  return Vec3(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

Vec3 operator*(const Vec3& v1, const Vec3& v2) {
  return Vec3(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}

Vec3 operator*(double n, const Vec3& v2) {
  return Vec3(n * v2[0], n * v2[1], n * v2[2]);
}

Vec3 operator*(const Vec3& v1, double n) {
  return n * v1;
}

Vec3 operator/(const Vec3& v1, double n) {
  return (1.0 / n) * v1;
}

std::ostream& operator<<(std::ostream& out, const Vec3& v) {
  return out << std::format("{}", v);
}

}  // namespace rtow
