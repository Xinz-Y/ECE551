#include "pandemic.h"

#include <ctype.h>
#include <errno.h>
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
    // return a unsigned long long type(max is 2^64 -1), and in decimal
    uint64_t population = (uint64_t)strtoull(line + 1, &ptr_string, 10);
    //check if the population is no more than 2^64-1
    if (errno != 0) {
      perror("string to number errors");
      exit(EXIT_FAILURE);
    }
    // check if the population start with non-number
    ans.population = population;
  }

  // check if the population lagrer than 2^64 -1
  // *ptr_string='\0';
  // char * pop_star;
  // while(*(line +1 ))
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
    uint64_t pop;
    pop = (uint64_t)strtoull(string_n, &ptr_char, 10);
    if (pop == 0) {
      fprintf(stderr, "No number in the population\n");
      exit(EXIT_FAILURE);
    }
    if (errno != 0) {
      perror("string to number errors");
      exit(EXIT_FAILURE);
    }

    ans.population = pop;
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

  size_t period_max = 0;
  uint64_t max = 0;
  int tie = 0;
  for (size_t col = 0; col < n_days; col++) {
    size_t row_max = 0;
    for (size_t row = 1; row < n_countries; row++) {
      if (data[row][col] > data[row_max][col]) {
        row_max = row;
      }
    }
    if (data[row_max][col] > max) {
      max = data[row_max][col];
      period_max = row_max;
      tie = 0;
    }
    else if (data[row_max][col] == max) {
      tie++;
    }
  }
  if (tie > 0) {
    printf("%s\n", "There is a tie between at least two countries");
  }
  else {
    char * country_name = countries[period_max].name;
    int number_cases = max;
    printf("%s has the most daily cases with %u\n", country_name, number_cases);
  }
}
