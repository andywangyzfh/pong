#include "vec2d.h"

/* Constructors */

Vec2d::Vec2d(Vec2d::const_reference x, Vec2d::const_reference y) {
  this->x = x;
  this->y = y;
}

Vec2d::Vec2d(const Vec2d& v) {
  this->x = v.x;
  this->y = v.y;
}

/* Operators */
Vec2d Vec2d::operator+(const Vec2d& v) const { return Vec2d(x + v.x, y + v.y); }

Vec2d Vec2d::operator-(const Vec2d& v) const { return Vec2d(x - v.x, y - v.y); }

Vec2d Vec2d::operator*(const_reference scale) const {
  return Vec2d(x * scale, y * scale);
}

Vec2d Vec2d::operator/(const_reference scale) const {
  return Vec2d(x / scale, y / scale);
}

Vec2d& Vec2d::operator+=(const Vec2d& v) {
  x += v.x;
  y += v.y;
  return *this;
}

Vec2d& Vec2d::operator-=(const Vec2d& v) {
  x -= v.x;
  y -= v.y;
  return *this;
}

Vec2d& Vec2d::operator*=(Vec2d::const_reference scale) {
  x *= scale;
  y *= scale;
  return *this;
}

Vec2d& Vec2d::operator/=(Vec2d::const_reference scale) {
  x /= scale;
  y /= scale;
  return *this;
}

Vec2d& Vec2d::normalize(void) {
  *this /= sqrt(x * x + y * y);
  return *this;
}