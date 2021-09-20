#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  int num = 1;
  int ans = 1;
  for (int i = 0; i < n - 1; i++) {
    if (array[i] < array[i + 1]) {
      num = num + 1;
      if (ans < num) {
        ans = num;
      }
    }
    else {
      num = 1;
    }
  }
  return ans;
}
