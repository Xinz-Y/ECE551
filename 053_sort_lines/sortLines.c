#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

//void print_sorted_lines ();

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  // read from the standard input
  if (argc < 1) {
    fprintf(stderr, "Usage:Wrong number of argv\n");
    return EXIT_FAILURE;
  }
  else {
    char ** lines = NULL;
    char * line = NULL;
    size_t sz = 0;
    size_t i = 0;

    if (argc == 1) {
      //read from standard input
      printf("Please enter a line:\n");
      while (getline(&line, &sz, stdin) >= 0) {
        lines = realloc(lines, (i + 1) * sizeof(*lines));
        lines[i] = line;
        i++;
        line = NULL;
      }
      free(line);
      // lines store all the strings
      sortData(lines, i);
      for (size_t j = 0; j < i; j++) {
        printf("%s\n", lines[j]);
        free(lines[j]);
      }
      free(lines);
    }

    // read from the files
    else {
      for (int k = 0; k < argc - 1; k++) {
        FILE * f = fopen(argv[k + 1], "r");
        if (f == NULL) {
          perror("Could not open file");
          return EXIT_FAILURE;
        }
        lines = NULL;
        line = NULL;
        i = 0;
        while (getline(&line, &sz, f) >= 0) {
          lines = realloc(lines, (i + 1) * sizeof(*lines));
          lines[i] = line;
          i++;
          line = NULL;
        }
        free(line);
        sortData(lines, i);
        for (size_t j = 0; j < i; j++) {
          printf("%s\n", lines[j]);
          free(lines[j]);
        }
        free(lines);
      }
    }
  }
  return EXIT_SUCCESS;
}
