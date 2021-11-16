#include <iostream>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  //check if low and high are different sigh
  if (low == high) {
    return low;
  }
  int left = low;
  int right = high;
  /*  if (f->invoke(left) < 0 && f->invoke(right) < 0) {
    return high - 1;
  }
  if (f->invoke(left) > 0 && f->invoke(right) > 0) {
    return low;
    }*/
  // since we assumen the function is monotonic, f(left)<f(right)
  while (left < right) {
    int mid = left + (right - left) / 2;
    int val = f->invoke(mid);
    // we assume the
    if (val > 0) {
      right = mid;
    }
    else if (val < 0) {
      left = mid + 1;
    }
    else {
      return mid;
    }
  }
  return (low == left) ? low : high - 1;
}
