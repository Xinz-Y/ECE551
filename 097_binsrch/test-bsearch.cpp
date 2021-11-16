#include <cmath>
#include <cstdlib>
#include <iostream>

#include "function.h"
//#include "search.cpp"
//extern int binarySearchForZero(Function<int, int> * f, int low, int high);

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  //check if low and high are different sigh
  if (low == high) {
    return low;
  }
  int left = low;
  int right = high;

  while (left < right) {
    int mid = left + (right - left) / 2;
    int val = f->invoke(mid);
    // we assume the
    if (val > 0) {
      right = mid;
    }
    else if (val < 0) {
      left = mid;
    }
    else {
      return mid;
    }
  }
  return (low == left) ? low : low - 1;
}

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;
  // mesg is the description of the current funtcion(name,what's inside the func)
 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      std::cerr << "Too many function invocations in " << mesg << '\n';
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  //  if (high < low) {
  //  std::cerr << "This low is higher than high" << '\n';
  //   exit(EXIT_FAILURE);
  // }
  if (high > low) {
    CountedIntFn * wrap = new CountedIntFn(log2(high - low) + 1, f, mesg);
    int ans = binarySearchForZero(wrap, low, high);
    delete wrap;
    if (ans != expected_ans) {
      std::cerr << "The final answer is not expected in " << mesg << '\n';
      exit(EXIT_FAILURE);
    }
  }
  // low = high, only one element, invoke one time
  else {
    CountedIntFn * wrap = new CountedIntFn(1, f, mesg);
    int ans = binarySearchForZero(wrap, low, high);
    delete wrap;
    if (ans != expected_ans) {
      std::cerr << "The final answer is not expected in " << mesg << '\n';
      exit(EXIT_FAILURE);
    }
  }
}

int main() {
  //example in the next mlp
  class SinFunction : public Function<int, int> {
   public:
    virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
  };
  class LinearFunction : public Function<int, int> {
   public:
    virtual int invoke(int arg) { return arg; }
  };

  Function<int, int> * g = new LinearFunction();
  check(g, -3, 10, 0, "linear x");
  std::cout << "pass one" << '\n';
  //  check(g, 9, 3, 0, "low > high");
  check(g, -100000, 1000000000, 0, "big number");
  std::cout << "pass two" << '\n';
  check(g, 5, 9, 5, "all positive");
  std::cout << "pass three" << '\n';
  check(g, -100, -4, -5, "all negative");
  check(g, 0, 1, 0, "two element");
  check(g, 3, 3, 3, "only one postive element");
  check(g, 0, 0, 0, "0");
  check(g, -5, -5, -5, "only one negative element");
  check(g, -5, 1, 0, "0 is left node");
  //check(g, 0, 5, 0, "right side");
  check(g, -1, 100, 0, "extra case");
  check(g, -3, 0, -1, "test1");
  //  check(g, 0, 2, 0, "correct");
  delete g;
  return EXIT_SUCCESS;
}
