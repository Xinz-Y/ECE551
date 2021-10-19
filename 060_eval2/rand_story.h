#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

struct lines_tag {
  char ** lines;
  size_t n_row;
};
typedef struct lines_tag lines_t;

//any functions you want your main to use
FILE * openfile(char * filename);
void changeWord(char ** line, size_t n, char * start, char * end, catarray_t * cats);
lines_t * getNewLines(FILE * f);
void freeNewLines(lines_t * lines);
void closefile(FILE * f);

//function written in step2
catarray_t * createCataArr(void);
void freeCataArr(catarray_t * cataArr);
void addWord(char * cataName, char * word, catarray_t * cataArr);
catarray_t * getCataArr(FILE * f);
//void freeLines(char *** lines, size_t n);
#endif
