/* write your class interface in this file
   write function definitions only if they are very short
 */
#include <cmath>
#include <cstdio>
using namespace std;
class Vector2D {
 private:
  double x;
  double y;

 public:
  Vector2D() : x(0), y(0){};
  Vector2D(double a, double b) : x(a), y(b){};
  double getMagnitude() const {
    double answer = sqrt(x * x + y * y);
    return answer;
  }
  Vector2D operator+(const Vector2D & rhs) const;
  Vector2D & operator+=(const Vector2D & rhs);
  double dot(const Vector2D & rhs) const;
  void print() const { printf("<%.2f,%.2f>", x, y); }
};
