#include "vec3.hpp"

#include <cmath>
#include <format>
#include <iostream>

namespace rtow {

Vec3::Vec3() : data({0.0, 0.0, 0.0}) {}

Vec3::Vec3(double v0, double v1, double v2) : data({v0, v1, v2}) {}

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
  return std::sqrt(dot(*this, *this));
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
  return Vec3(v1.data[1] * v2.data[2] - v1.data[2] * v2.data[1],
              v1.data[2] * v2.data[0] - v1.data[0] * v2.data[2],
              v1.data[0] * v2.data[1] - v1.data[1] * v2.data[0]);
}

Vec3 Vec3::normalized(const Vec3& v) {
  return v / v.length();
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
