#include <cmath>
#include <cstdlib>
#include <iostream>

#include "function.h"
#include "search.h"
extern int binarySearchForZero(Function<int, int> * f, int low, int high);

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
    if (ans != expected_ans) {
      std::cerr << "The final answer is not expected in " << mesg << '\n';
      exit(EXIT_FAILURE);
    }
  }
  // low = high, only one element, invoke one time
  else {
    CountedIntFn * wrap = new CountedIntFn(1, f, mesg);
    int ans = binarySearchForZero(wrap, low, high);
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
  /*
  Function<int, int> * f = new SinFunction();
  check(f, 0, 150000, 52359, "sin funciton");
  //check(f, 0, -1, 1000, "low>high");
  check(f, 0, 1, 0, "all negative");
  check(f, 100000, 150000, 100000, "all positive");
  check(f, 0, 0, -2, "only one negative element");
  check(f, 100000, 100000, 100000, "only one postive element");
  */

  Function<int, int> * g = new LinearFunction();
  check(g, -3, 10, 0, "linear x");
  //  check(g, 9, 3, 0, "low > high");
  check(g, -100000, 1000000000, 0, "big number");
  check(g, 5, 9, 5, "all positive");
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
