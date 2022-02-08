#ifndef _VEC2D_H_
#define _VEC2D_H_

class vec2d {
 public:
  typedef float value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  value_type x, y;

  /* Constructor */
  explicit vec2d() : x(0.0f), y(0.0f) {}
  vec2d(const_reference x, const_reference y);
  vec2d(const vec2d& v);

  /* Operators */
  vec2d operator+(const vec2d& v) const;
  vec2d operator-(const vec2d& v) const;
  vec2d operator*(const_reference scale) const;
  vec2d operator/(const_reference scale) const;

  vec2d& operator+=(const vec2d& v);
  vec2d& operator-=(const vec2d& v);
  vec2d& operator*=(const_reference scale);
  vec2d& operator/=(const_reference scale);
};

#endif /* _VEC2D_H_ */