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

  // if there is no string before comma, we do nothing and accpet
  if (strchr(line, ',') == line) {
    // But we have to check if something after comma. If not, then reject.
    if (*(line + 1) == '\0') {
      fprintf(stderr, "Nothing after comma\n");
      exit(EXIT_FAILURE);
    }
    char * ptr_string;
    // return a long long type, and in decimal
    ans.population = (uint64_t)strtoll(line + 1, &ptr_string, 10);
  }
  else {
    // if there is somthing before comma, then split the string by strtok function
    char * token = strtok(line, ",");
    strncpy(ans.name, token, 64);
    char * end = strchr(token, '\0');
    // check if the string after comma is empty
    if (*(end + 1) == '\0') {
      fprintf(stderr, "Nothing after comma\n");
      exit(EXIT_FAILURE);
    }
    //since it is accepted more than one comma,strtok fucntnion
    //will return the second string and ignore the strings after
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
  for (size_t i = 0; i < n_days - 6; i++) {
    double sum = 0.0;
    for (size_t day = i; day < i + 7; day++) {
      sum += data[day];
    }
    avg[i] = sum / 7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  double sum = 0;
  for (uint i = 0; i < n_days; i++) {
    sum += data[i];
    cum[i] = (sum / pop) * 100000;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME

  for (size_t col = 0; col < n_days; col++) {
    int tie = 0;
    size_t row_max = 0;
    for (size_t row = 1; row < n_countries; row++) {
      if (data[row][col] > data[row_max][col]) {
        row_max = row;
        tie = 0;
      }
      else if (data[row][col] == data[row_max][col]) {
        tie++;
      }
    }
    if (tie > 0) {
      printf("%s\n", "There is a tie between at least two countries");
    }
    else {
      char * country_name = countries[row_max].name;
      int number_cases = data[row_max][col];
      printf("%s has the most daily cases with %u\n", country_name, number_cases);
    }
  }
}
