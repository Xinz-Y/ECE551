#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong number of argc\n");
    return EXIT_FAILURE;
  }
  FILE * f = openfile(argv[1]);
  catarray_t * pcataArr = getCataArr(f);
  printWords(pcataArr);
  freeCataArr(pcataArr);
  closefile(f);
  return EXIT_FAILURE;
}
