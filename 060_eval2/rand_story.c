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

// do step2
catarray_t * createCataArr(void) {
  catarray_t * cataArr = malloc(sizeof(*cataArr));
  cataArr->n = 0;
  cataArr->arr = NULL;
  return cataArr;
}

void freeCataArr(catarray_t * pcataArr) {
  for (size_t i = 0; i < pcataArr->n; i++) {
    for (size_t j = 0; j < pcataArr->arr[i].n_words; j++) {
      free((pcataArr->arr)[i].words[j]);
    }
    free((pcataArr->arr)[i].name);
    free((pcataArr->arr)[i].words);
  }
  free(pcataArr->arr);
  free(pcataArr);
}

int checkExist(char * cataName, catarray_t * cataArr) {
  int isExist = 0;
  for (size_t i = 0; i < cataArr->n; i++) {
    if (strcmp(cataName, (cataArr->arr)[i].name) == 0) {
      isExist = i;
      return isExist;
    }
  }
  return isExist;
}

void addWord(char * cataName, char * word, catarray_t * cataArr) {
  int isExist = checkExist(cataName, cataArr);
  if (isExist != 0) {
    //free cataName
    free(cataName);
    int i = isExist;
    (cataArr->arr)[i].words =
        realloc((cataArr->arr)[i].words,
                ((cataArr->arr)[i].n_words + 1) * sizeof(*((cataArr->arr)[i]).words));
    (cataArr->arr)[i].words[(cataArr->arr)[i].n_words] = word;
    (cataArr->arr)[i].n_words++;
  }
  else {
    cataArr->arr = realloc(cataArr->arr, ((cataArr->n) + 1) * sizeof(*(cataArr->arr)));
    cataArr->arr[cataArr->n].name = cataName;
    cataArr->arr[cataArr->n].words = NULL;
    cataArr->arr[cataArr->n].words = malloc(sizeof(*cataArr->arr[cataArr->n].words));
    cataArr->arr[cataArr->n].words[0] = word;
    cataArr->arr[cataArr->n].n_words = 1;
    cataArr->n++;
  }
}

/* void addWord2(char * cataName, char * word, catarray_t * cataArr) { */
/*   if (cataArr->n == 0) { */
/*     cataArr->arr = realloc(cataArr->arr, ((cataArr->n) + 1) * sizeof(*(cataArr->arr))); */
/*     cataArr->arr[cataArr->n].name = cataName; */
/*     cataArr->arr[cataArr->n].words = NULL; */
/*     cataArr->arr[cataArr->n].words = malloc(sizeof(*cataArr->arr[cataArr->n].words)); */
/*     cataArr->arr[cataArr->n].words[0] = word; */
/*     cataArr->arr[cataArr->n].n_words = 1; */
/*     cataArr->n++; */
/*   } */
/*   for (size_t i = 0; i < cataArr->n; i++) { */
/*     if (strcmp(cataName, (cataArr->arr)[i].name) == 0) { */
/*       (cataArr->arr)[i].words = */
/*           realloc((cataArr->arr)[i].words, */
/*                   ((cataArr->arr)[i].n_words + 1) * sizeof(*((cataArr->arr)[i]).words)); */
/*       (cataArr->arr)[i].words[(cataArr->arr)[i].n_words] = word; */
/*       (cataArr->arr)[i].n_words++; */
/*       break; */
/*     } */
/*     else { */
/*       // add a new catagory_t */
/*       cataArr->arr = realloc(cataArr->arr, ((cataArr->n) + 1) * sizeof(*(cataArr->arr))); */
/*       cataArr->arr[cataArr->n].name = cataName; */
/*       cataArr->arr[cataArr->n].words = NULL; */
/*       cataArr->arr[cataArr->n].words = malloc(sizeof(*cataArr->arr[cataArr->n].words)); */
/*       cataArr->arr[cataArr->n].words[0] = word; */
/*       cataArr->arr[cataArr->n].n_words = 1; */
/*       cataArr->n++; */
/*     } */
/*   } */
/* } */

/* void freeLines(char *** lines, size_t n) { */
/*   for (size_t i = 0; i < n; i++) { */
/*     free((*lines)[i]); */
/*   } */
/*   free(*lines); */
/* } */
/*
void deln (char * word){
  size_t len = strlen(word);
  word[len-1] = '\0';
  
  }*/
catarray_t * getCataArr(FILE * f) {
  char * line = NULL;
  // to store the pointers of line for later free
  size_t sz = 0;
  catarray_t * pcataArr = createCataArr();
  while (getline(&line, &sz, f) >= 0) {
    char * cataName = NULL;
    char * word = NULL;
    //check if '=' is in the line
    char * ptr = strchr(line, ':');
    if (ptr == NULL) {
      fprintf(stderr, "There is no '=' in the line");
      exit(EXIT_FAILURE);
    }
    *ptr = '\0';
    cataName = strdup(line);
    if (*(ptr + 1) != '\0') {
      word = strdup(ptr + 1);
    }

    addWord(cataName, word, pcataArr);
    free(line);
    line = NULL;
  }
  free(line);
  return pcataArr;
}
