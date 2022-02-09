#ifndef _VEC2D_H_
#define _VEC2D_H_

class Vec2d {
 public:
  typedef float value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  value_type x, y;

  /* Constructor */
  explicit Vec2d() : x(0.0f), y(0.0f) {}
  Vec2d(const_reference x, const_reference y);
  Vec2d(const Vec2d& v);

  /* Operators */
  Vec2d operator+(const Vec2d& v) const;
  Vec2d operator-(const Vec2d& v) const;
  Vec2d operator*(const_reference scale) const;
  Vec2d operator/(const_reference scale) const;

  Vec2d& operator+=(const Vec2d& v);
  Vec2d& operator-=(const Vec2d& v);
  Vec2d& operator*=(const_reference scale);
  Vec2d& operator/=(const_reference scale);
};

#endif /* _VEC2D_H_ */