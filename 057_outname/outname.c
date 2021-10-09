#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  size_t n = strlen(inputName) + 1 + 7;
  char * out_name = malloc(n * sizeof(out_name));
  /* for(size_t i =0; i <strlen(inputName);i++ ){ */
  /*   out_name[i] = inputName[i]; */
  /* } */
  strcpy(out_name, inputName);
  char * end = ".counts";
  strcat(out_name, end);

  return out_name;
}
