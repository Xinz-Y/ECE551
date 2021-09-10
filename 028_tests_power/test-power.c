#include <stdio.h>
#include <stdlib.h>

#include "power.h"

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned answer = power(x, y);
  if (answer != expected_ans) {
    printf("%s", "There is something wrong with power function\n");
    exit(EXIT_FAILURE);
  }
  printf("%s", "There is nothing wrong with power function\n");
}

int main(void) {
  //run_check(0, 0, 0);
  run_check(0, 0, 1);
  run_check(0, 1, 0);
  run_check(1, 0, 1);
  run_check(2, 0, 1);
  run_check(3, 3, 27);
  run_check(5, 4, 625);
  run_check(100000, 1, 100000);
  run_check(1, 100000, 1);

  printf("%s", "test are run\n");
  return EXIT_SUCCESS;
}
