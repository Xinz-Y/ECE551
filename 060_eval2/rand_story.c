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
//make some changes for step3, s.t. adding an argument that save the word shown
// make new change for step4, s.t. if isReuse is 0, then update the cats to a new cats

void changeWord(char ** line,
                size_t n,
                char * start,
                char * end,
                catarray_t * cats,
                wordsArr_t * wordsArr,
                int isReuse) {
  // get the catagoty name
  size_t len = end - start - 1;
  char * cataName = strndup(start + 1, len);
  // in case of step1
  // if wordsArr is NULL , do not need to read from wordsArr and add shown cataName to wordsArr
  char * word;
  if (wordsArr == NULL) {
    word = strdup(chooseWord(cataName, cats));
    if (isReuse == 1) {
      updateCataArr(cats, word, cataName);
    }
  }
  else {
    //in case of stpe3,step4
    //match the catName with word
    if (atoi(cataName) == 0) {
      // This mean cataName is not a number, we choose word from cataArr
      // check whether this is a valid cataName,i.e. exists in the cataArr
      if (checkExist(cataName, cats) == -1) {
        fprintf(stderr, "Wrong catagory!--Does not eixt in the cataArray!\n");
        exit(EXIT_FAILURE);
      }
      word = strdup(chooseWord(cataName, cats));
      if (isReuse == 1) {
        updateCataArr(cats, word, cataName);
      }
    }
    else {
      // read from the wordsArr
      int num = atoi(cataName);
      if ((num < 1) | (num > (int)wordsArr->n_words)) {
        fprintf(stderr, "Wrong index!\n");
        exit(EXIT_FAILURE);
      }
      word = strdup(wordsArr->words[wordsArr->n_words - num]);
    }
    // save the word to wordsArr
    addWord2Arr(word, wordsArr);
  }
  size_t newNum;
  // compute the length of the new line
  if (strlen(cataName) < strlen(word)) {
    newNum = n + strlen(word) - strlen(cataName);
  }
  else {
    newNum = n;
  }
  // realloc a new line
  char * newLine = NULL;
  newLine = malloc(newNum * sizeof(*newLine));
  *start = '\0';
  char * string1 = *line;
  strcpy(newLine, string1);
  strcat(newLine, word);
  size_t backlen = strlen(end + 1);
  strncat(newLine, end + 1, backlen + 1);
  free(*line);
  *line = newLine;
  free(cataName);
  free(word);
}

/* void changeWord2(char ** line, */
/*                 size_t n, */
/*                 char * start, */
/*                 char * end, */
/*                 catarray_t * cats, */
/*                 wordsArr_t * wordsArr) { */
/*   // get the catagoty name */
/*   size_t len = end - start - 1; */
/*   char * cataName = strndup(start + 1, len); */
/*   // if wordsArr is NULL , do not need to read from wordsArr and add shown cataName to wordsArr */
/*   const char * word; */
/*   if (wordsArr == NULL) { */
/*     word = chooseWord(cataName, cats); */
/*   } */
/*   else { */
/*     //match the catName with word */
/*     if (atoi(cataName) == 0) { */
/*       // This mean cataName is not a number, we choose word from cataArr */
/*       word = chooseWord(cataName, cats); */
/*     } */
/*     else { */
/*       // read from the wordsArr */
/*       int num = atoi(cataName); */
/*       if ((num < 1) | (num > (int)wordsArr->n_words)) { */
/*         fprintf(stderr, "Wrong index!\n"); */
/*         exit(EXIT_FAILURE); */
/*       } */
/*       word = wordsArr->words[wordsArr->n_words - num]; */
/*     } */
/*     // save the word to wordsArr */
/*     addWord2Arr(word, wordsArr); */
/*   } */
/*   size_t newNum; */
/*   // compute the length of the new line */
/*   if (strlen(cataName) < strlen(word)) { */
/*     newNum = n + strlen(word) - strlen(cataName); */
/*   } */
/*   else { */
/*     newNum = n; */
/*   } */
/*   // realloc a new line */
/*   char * newLine = NULL; */
/*   newLine = malloc(newNum * sizeof(*newLine)); */
/*   *start = '\0'; */
/*   char * string1 = *line; */
/*   strcpy(newLine, string1); */
/*   strcat(newLine, word); */
/*   size_t backlen = strlen(end + 1); */
/*   strncat(newLine, end + 1, backlen + 1); */
/*   free(*line); */
/*   *line = newLine; */
/*   free(cataName); */
/* } */

// change arguments to  get newlines in stpe3;for step1 pcataArr and wordsArr both are NULL
// change argumen to no reuse in step3; for step3 isReuse is 0;
lines_t * getNewLines(FILE * f,
                      catarray_t * pcataArr,
                      wordsArr_t * wordsArr,
                      int isReuse) {
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
          changeWord(&line, sz, start, end, pcataArr, wordsArr, isReuse);
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
  return newLines;
}

void freeNewLines(lines_t * lines) {
  for (size_t i = 0; i < lines->n_row; i++) {
    free(lines->lines[i]);
  }
  free(lines->lines);
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
  int isExist = -1;
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
  if (isExist != -1) {
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

void deln(char * word) {
  size_t len = strlen(word);
  word[len - 1] = '\0';
}
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
      deln(word);
    }

    addWord(cataName, word, pcataArr);
    free(line);
    line = NULL;
  }
  free(line);
  return pcataArr;
}

// do step3

wordsArr_t * createWordsArr(void) {
  wordsArr_t * wordsArr = malloc(sizeof(*wordsArr));
  wordsArr->n_words = 0;
  wordsArr->words = NULL;
  return wordsArr;
}

void addWord2Arr(char * word, wordsArr_t * wordsArr) {
  wordsArr->words =
      realloc(wordsArr->words, (wordsArr->n_words + 1) * sizeof(*(wordsArr->words)));
  (wordsArr->words)[wordsArr->n_words] = strdup(word);
  wordsArr->n_words++;
}

void freeWordsArr(wordsArr_t * wordsArr) {
  for (size_t i = 0; i < wordsArr->n_words; i++) {
    free(wordsArr->words[i]);
  }
  free(wordsArr->words);
  free(wordsArr);
}
// do step4

void updateCataArr(catarray_t * cats, const char * word, char * cataName) {
  // search for the catagory
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp((cats->arr)[i].name, cataName) == 0) {
      // malloc a new words list, copy the old words list except the word used
      char ** newWords = NULL;
      newWords = malloc(((cats->arr)[i].n_words - 1) * sizeof(*newWords));
      for (size_t j = 0; j < (cats->arr)[i].n_words - 1; j++) {
        newWords[j] = NULL;
      }
      size_t m = 0;
      for (size_t k = 0; k < (cats->arr)[i].n_words; k++) {
        if (strcmp((cats->arr)[i].words[k], word) == 0) {
          free((cats->arr)[i].words[k]);
          continue;
        }
        newWords[m] = (cats->arr)[i].words[k];
        m++;
      }
      //free the old one,then point to the new words list
      free((cats->arr)[i].words);
      (cats->arr)[i].words = newWords;
      (cats->arr)[i].n_words--;
      break;
    }
  }
}
