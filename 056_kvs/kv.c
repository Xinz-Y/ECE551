#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// close file
FILE * open_file(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }
  return f;
}
void close_file(FILE * f) {
  if (fclose(f) != 0) {
    perror("File can not be closed");
    exit(EXIT_FAILURE);
  }
}
void deln(char * string) {
  char * p = strchr(string, '\n');
  *p = '\0';
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = open_file(fname);
  char * line = NULL;
  size_t sz;
  size_t i = 0;
  kvarray_t * readkvs = malloc(sizeof(*readkvs));
  while (getline(&line, &sz, f) >= 0) {
    char * delimiter = strchr(line, '=');
    //no delimiter
    if (delimiter == NULL) {
      printf("No = in the line");
      exit(EXIT_FAILURE);
    }
    if (delimiter == line) {
      printf("No key in the line");
      exit(EXIT_FAILURE);
    }
    *delimiter = '\0';
    readkvs->kvarray = realloc(readkvs->kvarray, (i + 1) * sizeof(*(readkvs->kvarray)));
    readkvs->kvarray[i].key = line;
    readkvs->kvarray[i].value = delimiter + 1;
    deln(readkvs->kvarray[i].value);
    i++;
    line = NULL;
  }
  readkvs->n_kv = i;
  free(line);
  close_file(f);
  return readkvs;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  size_t n = pairs->n_kv;
  for (size_t i = 0; i < n; i++) {
    free(pairs->kvarray[i].key);
    // free(pairs->kvarray[i].value);//Not sure here if double free...
  }
  free(pairs->kvarray);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->n_kv; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvarray[i].key, pairs->kvarray[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->n_kv; i++) {
    if (strcmp(pairs->kvarray[i].key, key) == 0) {
      return pairs->kvarray[i].value;
    }
  }
  return NULL;
}
