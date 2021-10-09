#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  counts->string_arr = NULL;
  counts->n = 0;
  counts->count_unk = 0;

  return counts;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->count_unk++;
  }
  else {
    // if name is not in the string_arr then create a one_count struct
    for (size_t i = 0; i < c->n; i++) {
      if (strcmp(c->string_arr[i].string, name) == 0) {
        c->string_arr[i].count++;
        break;
      }
      else {
        c->n++;
        c->string_arr = realloc(c->string_arr, (c->n) * sizeof(*(c->string_arr)));
        c->string_arr[(c->n) - 1].string = malloc((strlen(name) + 1) * sizeof(char));
        strcpy(c->string_arr[(c->n) - 1].string, name);
        c->string_arr[(c->n) - 1].count = 1;
      }
    }
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  if (outFile == NULL) {
    perror("The file can not be written");
    exit(EXIT_FAILURE);
  }
  // fprintf(outFile, "%d\n", (int)c->n);
  for (size_t i = 0; i < c->n; i++) {
    // fprintf(outFile, "Checking");
    fprintf(outFile, "%s: %d\n", c->string_arr[i].string, c->string_arr[i].count);
  }
  if (c->count_unk != 0) {
    fprintf(outFile, "<unknown> : %d\n", c->count_unk);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->n; i++) {
    free(c->string_arr[i].string);
  }
  free(c->string_arr);
  free(c);
}
