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
  //check if the line is in the right format
  //comma is inside
  if (strchr(line, ',') == NULL) {
    fprintf(stderr, "No comma in your line\n");
    exit(EXIT_FAILURE);
  }

  // if there is no string before comma,accpet
  if (strchr(line, ',') == line) {
    // Do nothing to the name
    // but we have to check if nothing after comma
    if (*(line + 1) == '\0') {
      fprintf(stderr, "nothing after comma\n");
      exit(EXIT_FAILURE);
    }
    char * ptr_char2;
    ans.population = (uint64_t)strtoll(line + 1, &ptr_char2, 10);
    // printf("Population is %" PRIu64 "\n", ans.population);
  }
  else {
    // split the string
    char * token = strtok(line, ",");
    strncpy(ans.name, token, 64);
    char * end = strchr(token, '\0');
    // check if the string after comma is empty
    if (*(end + 1) == '\0') {
      fprintf(stderr, "Nothing after comma\n");
      exit(EXIT_FAILURE);
    }
    // printf("The country name is %s\n", ans.name);
    char * string_n = strtok(NULL, ",");
    char * ptr_char;
    long long pop;
    pop = strtoll(string_n, &ptr_char, 10);
    if (pop == 0) {
      fprintf(stderr, "No number in the population\n");
      exit(EXIT_FAILURE);
    }
    ans.population = (uint64_t)pop;
    // printf("Population is %" PRIu64 "\n", ans.population);
  }
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  double sum = 0;
  for (int i = 0; i < n_days; i++) {
    sum += data[i];
  }
  *avg = sum / n_days;
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
