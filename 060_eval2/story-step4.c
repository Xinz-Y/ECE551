#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if ((argc != 3) & (argc != 4)) {
    fprintf(stderr, "wrong number of argv");
    return EXIT_FAILURE;
  }
  if (argc == 3) {
    // first we create catarray-t from cate/words file
    FILE * f = openfile(argv[1]);
    catarray_t * pcataArr = getCataArr(f);
    //create a new catarray_t to save words showing up
    wordsArr_t * wordsArr = createWordsArr();
    //secondly we read the template file and get new lines which has been filled
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

  else {
    // check is -n is right
    if (strcmp(argv[1], "-n") != 0) {
      fprintf(stderr, "This option choiceis not -n ");
    }
    FILE * f = openfile(argv[2]);
    catarray_t * pcataArr = getCataArr(f);
    wordsArr_t * wordsArr = createWordsArr();
    FILE * f2 = openfile(argv[3]);
    lines_t * newLines = getNewLines(f2, pcataArr, wordsArr, 1);
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
}
