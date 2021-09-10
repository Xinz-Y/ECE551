#include "power.h"

#include <stdio.h>
#include <stdlib.h>

unsigned helper(unsigned x, unsigned y, unsigned ans);

unsigned power(unsigned x, unsigned y) {
  return helper(x, y, 1);
}

unsigned helper(unsigned x, unsigned y, unsigned ans) {
  if (y <= 0) {
    return ans;
  }
  return helper(x, y - 1, ans * x);
}
