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
  //secondly we read the template file
  FILE * f2 = openfile(argv[2]);
  char * line = NULL;
  char ** lines = NULL;
  size_t sz = 0;
  size_t n = 0;
  while (getline(&line, &sz, f2) >= 0) {
    char * ptr = line;
    char * start = NULL;
    char * end = NULL;
    int num = 0;
    int isfirst = 0;
    while (*ptr != '\0') {
      if (*ptr == '_') {
        if (isfirst == 0) {
          start = ptr;
          isfirst = 1;
        }
        else {
          end = ptr;
          isfirst = 0;

          //check if the cataName a number or non-number
          char * cataName = strndup(start + 1, end - start - 1);
          const char * word;
          if (atoi(cataName) == 0) {
            // This is a non_number catagory, we choose word from cataArr and save the
            // word in the wordsArr
            word = chooseWord(cataName, pcataArr);
          }
          else {
            // Read from the wordsArr
            int num = atoi(cataName);
            if ((num < 1) | (num > (int)wordsArr->n_words)) {
              fprintf(stderr, "Wrong index");
              return EXIT_FAILURE;
            }
            word = wordsArr->words[wordsArr->n_words - num];
          }
          // save it to wordsArr
          addWord2Arr(word, wordsArr);

          size_t newNum;
          // compute the length of the new line
          if (strlen(cataName) + 2 < strlen(word)) {
            newNum = sz + strlen(word) - (2 + strlen(cataName));
          }
          else {
            newNum = sz;
          }
          // realloc a new line
          char * newLine = NULL;
          newLine = malloc(newNum * sizeof(*newLine));
          *start = '\0';
          char * string1 = line;
          strcpy(newLine, string1);
          strcat(newLine, word);
          size_t backlen = strlen(end + 1);
          strncat(newLine, end + 1, backlen + 1);
          free(line);
          line = newLine;
          free(cataName);
          ptr = line;
        }
        num++;
      }
      ptr++;
    }
    if (num % 2 != 0) {
      fprintf(stderr, "The second '_' is missing\n");
      exit(EXIT_FAILURE);
    }
    lines = realloc(lines, (n + 1) * sizeof(*lines));
    lines[n] = line;
    line = NULL;
    n++;
  }
  free(line);
  lines_t * newLines = malloc(sizeof(*newLines));
  newLines->lines = lines;
  newLines->n_row = n;
  for (size_t i = 0; i < newLines->n_row; i++) {
    printf("%s\n", newLines->lines[i]);
  }
  freeNewLines(newLines);
  freeWordsArr(wordsArr);
  freeCataArr(pcataArr);
  closefile(f);
  return EXIT_SUCCESS;
}
