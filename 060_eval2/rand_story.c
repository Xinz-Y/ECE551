#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE * openfile(char * filename) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("Can't open the file\n");
    exit(EXIT_FAILURE);
  }
  return f;
}

void closefile(FILE * f) {
  if (fclose(f) != 0) {
    perror("fail to close fire");
    exit(EXIT_FAILURE);
  }
}

void changeWord(char ** line, size_t n, char * start, char * end, catarray_t * cats) {
  // get the catagoty name
  size_t len = end - start + 1;
  char * cataName = strndup(start, len);
  //match the catName with word
  const char * word = chooseWord(cataName, cats);
  size_t newNum;
  // compute the length of the new line
  if (strlen(cataName) < strlen(word)) {
    newNum = n + strlen(word) - strlen(cataName);
  }
  else {
    newNum = n;
  }
  // realloc a new line
  char * newLine = malloc(newNum * sizeof(*newLine));
  *start = '\0';
  char * string1 = *line;
  strcpy(newLine, string1);
  strcat(newLine, word);
  size_t backlen = strlen(end + 1);
  strncat(newLine, end + 1, backlen + 1);
  free(*line);
  *line = newLine;
  free(cataName);
}

void step1(FILE * f) {
  char * line = NULL;
  char ** lines = NULL;
  size_t sz = 0;
  size_t n = 0;
  while (getline(&line, &sz, f) >= 0) {
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
          changeWord(&line, sz, start, end, NULL);
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
  for (size_t i = 0; i < n; i++) {
    printf("%s\n", lines[i]);
    free(lines[i]);
  }
  free(lines);
}
