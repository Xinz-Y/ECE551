#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned answer = power(x, y);
  if (answer != expected_ans) {
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  run_check(0, 2, 0);
  run_check(1, 0, 1);
  run_check(10000, 0, 1);

  run_check(0, 0, 0);
  run_check(0, 1, 0);
  run_check(0, 1000000000, 0);
  run_check(3, 4, 81);
  run_check(1, 1, 1);
  run_check(2, 2, 4);
  run_check(2, 10, 1024);
  run_check(1, 100000000, 1);
  run_check(1000000, 1, 1000000);
  return EXIT_SUCCESS;
}
