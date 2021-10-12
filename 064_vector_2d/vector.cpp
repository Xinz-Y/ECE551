#include "vector.hpp"

#include <cmath>
#include <cstdio>

// write your class implementation in this file
Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D ans;
  ans.x = x + rhs.x;
  ans.y = y + rhs.y;
  return ans;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x = x + rhs.x;
  y = y + rhs.y;
  return *this;
}

double Vector2D::dot(const Vector2D & rhs) const {
  double ans = x * rhs.x + y * rhs.y;
  return ans;
}
