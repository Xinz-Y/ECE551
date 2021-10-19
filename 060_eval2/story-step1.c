#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong number of argc\n");
    return EXIT_FAILURE;
  }
  FILE * f = openfile(argv[1]);
  //FILE * f = openfile("story.txt");
  lines_t * newLines = getNewLines(f);
  for (size_t i = 0; i < newLines->n_row; i++) {
    printf("%s\n", newLines->lines[i]);
  }
  freeNewLines(newLines);
  closefile(f);
  return EXIT_SUCCESS;
}
