#include "vec2d.h"

/* Constructors */

vec2d::vec2d(vec2d::const_reference x, vec2d::const_reference y) {
  this->x = x;
  this->y = y;
}

vec2d::vec2d(const vec2d& v) {
  this->x = v.x;
  this->y = v.y;
}

/* Operators */
vec2d vec2d::operator+(const vec2d& v) const { return vec2d(x + v.x, y + v.y); }

vec2d vec2d::operator-(const vec2d& v) const { return vec2d(x - v.x, y - v.y); }

vec2d vec2d::operator*(const_reference scale) const {
  return vec2d(x * scale, y * scale);
}

vec2d vec2d::operator/(const_reference scale) const {
  return vec2d(x / scale, y / scale);
}

vec2d& vec2d::operator+=(const vec2d& v) {
  x += v.x;
  y += v.y;
  return *this;
}

vec2d& vec2d::operator-=(const vec2d& v) {
  x -= v.x;
  y -= v.y;
  return *this;
}

vec2d& vec2d::operator*=(vec2d::const_reference scale) {
  x *= scale;
  y *= scale;
  return *this;
}

vec2d& vec2d::operator/=(vec2d::const_reference scale) {
  x /= scale;
  y /= scale;
  return *this;
}