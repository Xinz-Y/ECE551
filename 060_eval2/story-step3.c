#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "wrong number of argv");
    return EXIT_FAILURE;
  }
  // first we create catarray-t from cate/words file
  FILE * f = openfile(argv[1]);
  catarray_t * pcataArr = getCataArr(f);
  //create a new catarray_t to save words showing up
  wordsArr_t * wordsArr = createWordsArr();
  //secondly we read the template file and get all new lines which has been filled
  FILE * f2 = openfile(argv[2]);
  lines_t * newLines = getNewLines(f2, pcataArr, wordsArr, 0);
  for (size_t i = 0; i < newLines->n_row; i++) {
    printf("%s\n", newLines->lines[i]);
  }
  freeNewLines(newLines);
  freeWordsArr(wordsArr);
  freeCataArr(pcataArr);
  closefile(f);
  closefile(f2);
  return EXIT_SUCCESS;
}
