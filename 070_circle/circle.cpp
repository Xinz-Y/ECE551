#include "circle.hpp"

#include <algorithm>
#include <cmath>
//#include "point.hpp"

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = center.distanceFrom(otherCircle.center);
  // intersect
  if (d < radius + otherCircle.radius) {
    double as = radius * radius;
    double bs = otherCircle.radius * otherCircle.radius;
    double x = (as - bs + d * d) / (2 * d);
    double zs = x * x;
    double y = std::sqrt(as - zs);
    // a includes in b or otherwise
    if (d <= std::abs(radius - otherCircle.radius)) {
      return M_PI * std::min(as, bs);
    }
    return as * (std::asin(y / radius)) + bs * std::asin(y / otherCircle.radius) -
           y * (x + std::sqrt(zs + bs - as));
  }
  return 0;
}
