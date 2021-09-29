#include "pandemic.h"

#include <ctype.h>
#include <inttypes.h>
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
  // if (strchr(line, ',') != strrchr(line, ',')) {
  // fprintf(stderr, "More than one comma\n ");
  // exit(EXIT_FAILURE);
  // }
  // if there is no string before comma,accpet
  if (strchr(line, ',') == line) {
    // Do nothing to the name
    printf("The country name is %s\n", ans.name);
    char * ptr_char2;
    ans.population = (uint64_t)strtoll(line + 1, &ptr_char2, 10);
    printf("Population is %" PRIu64 "\n", ans.population);
  }
  else {
    // split the string
    char * token = strtok(line, ",");
    //check if the line exceed 64 chars
    //if (strlen(token) > 63) {
    //  fprintf(stderr, "name is more than 64 bit");
    //  exit(EXIT_FAILURE);
    //}
    strncpy(ans.name, token, 64);
    printf("The country name is %s\n", ans.name);
    char * string_n = strtok(NULL, ",");
    char * ptr_char;
    long long pop;
    pop = strtoll(string_n, &ptr_char, 10);
    ans.population = (uint64_t)pop;
    printf("Population is %" PRIu64 "\n", ans.population);
  }
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
