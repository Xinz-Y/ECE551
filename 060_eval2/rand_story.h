#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
//any functions you want your main to use
FILE * openfile(char * filename);
void changeWord(char ** line, size_t n, char * start, char * end, catarray_t * cats);
void step1(FILE * f);
void closefile(FILE * f);

//function written in step2
catarray_t * createCataArr(void);
void freeCataArr(catarray_t * cataArr);
void addWord(char * cataName, char * word, catarray_t * cataArr);
catarray_t * getCataArr(FILE * f);
//void freeLines(char *** lines, size_t n);
#endif
