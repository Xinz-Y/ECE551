#include "pandemic.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;
  // check the line ends
  if (strchr(line, '\n') == NULL) {
    fprintf(stderr, "Line in the file is too long\n");
    exit(EXIT_FAILURE);
  }
  //check if the line is in the right format
  //comma is inside
  if (strchr(line, ',') == NULL) {
    fprintf(stderr, "No comma in your line\n");
    exit(EXIT_FAILURE);
  }
  //check there is only one comma
  if (strchr(line, ',') != strrchr(line, ',')) {
    fprintf(stderr, "More than one comma\n ");
    exit(EXIT_FAILURE);
  }
  //make sure there is sting before comma
  if (strchr(line, ',') == line) {
    fprintf(stderr, "There is no country name");
    exit(EXIT_FAILURE);
  }

  // split the string
  char * token = strtok(line, ",");
  //check if the line exceed 64 chars
  if (strlen(token) > 63) {
    fprintf(stderr, "name is more than 64 bit");
    exit(EXIT_FAILURE);
  }
  strncpy(ans.name, token, 64);
  // check if char-only
  //while
  printf("The country name is %s\n", ans.name);
  char * string_n = strtok(NULL, ",");
  char * ptr_char;
  long pop;
  pop = strtol(string_n, &ptr_char, 10);
  ans.population = pop;
  printf("Population is %d\n", (int)ans.population);

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
