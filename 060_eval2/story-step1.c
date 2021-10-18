#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

/* int main(int argc, char ** argv) { */
/*   if (argc != 2) { */
/*     fprintf(stderr, "Wrong number of argc\n"); */
/*     return EXIT_FAILURE; */
/*   } */
int main() {
  // FILE * f = openfile(argv[1]);
  FILE * f = openfile("story.txt");
  step1(f);
  closefile(f);
  return EXIT_SUCCESS;
}
