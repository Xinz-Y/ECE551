#include "point.hpp"

#include <cmath>
#include <cstdio>

// write your class implementation in this file
void Point::move(double dx, double dy) {
  x = x + dx;
  y = y + dy;
}

double Point::distanceFrom(const Point & p) {
  double ans = std::sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y));

  return ans;
}
