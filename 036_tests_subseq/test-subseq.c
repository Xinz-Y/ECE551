#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void run_check(int * array, size_t n, size_t expected_size) {
  size_t answer = maxSeq(array, n);
  if (answer == expected_size) {
    printf("%s", "There is nothing wrong with maxseq function\n");
  }
  else {
    printf("%s", "There is something wrong with maxseq function\n");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int array1[1] = {1};
  run_check(array1, 1, 1);
  int array2[1] = {-1};
  run_check(array2, 1, 1);
  int array3[2] = {-1, 0};
  run_check(array3, 2, 2);
  int array4[2] = {-1, 1};
  run_check(array4, 2, 2);
  int array5[2] = {-1, -3};
  run_check(array5, 1, 1);
  int array6[3] = {1, 1, 1};
  run_check(array6, 3, 1);
  run_check(NULL, 0, 0);
  int array7[5] = {-1, -2, 1, 2, 3};
  run_check(array7, 5, 4);
}
