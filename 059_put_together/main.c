#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"
//delete \n
void deln_main(char * string) {
  char * p = strchr(string, '\n');
  *p = '\0';
}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }
  // read file line by line
  char * line = NULL;
  size_t sz;
  size_t n = 0;
  char ** value_arr = NULL;
  char * value = NULL;
  while (getline(&line, &sz, f) >= 0) {
    deln_main(line);
    value = lookupValue(kvPairs, line);
    value_arr = realloc(value_arr, (n + 1) * sizeof(*value_arr));
    value_arr[n] = value;
    n++;
    free(line);
    line = NULL;
  }
  free(line);
  fclose(f);
  counts_t * count_one_file = createCounts();

  for (size_t i = 0; i < n; i++) {
    addCount(count_one_file, value_arr[i]);
  }
  free(value_arr);
  return count_one_file;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc < 3) {
    fprintf(stderr, "Wrong number o argv\n");
    return EXIT_FAILURE;
  }
  kvarray_t * readkvs = readKVs(argv[1]);

  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], readkvs);

    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    fclose(f);
    //free the memory for outName and c
    freeCounts(c);
    free(outName);
  }
  //free the memory for kv
  freeKVs(readkvs);
  return EXIT_SUCCESS;
}
