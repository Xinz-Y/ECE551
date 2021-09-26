#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
int decrypt(FILE * f) {
  int c;
  int key;
  int freq[26] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c -= 'a';
      freq[c]++;
    }

    int max = 0;
    int id;
    for (int i = 0; i < 26; i++) {
      if (freq[i] > max) {
        max = freq[i];
        id = i;
      }
    }

    if (id - 4 > 0) {
      key = id - 4;
    }
    else {
      key = id - 4 + 26;
    }
  }
  return key;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: Wrong unmber of argv\n");
    return EXIT_FAILURE;
  }

  int key;
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  key = decrypt(f);
  printf("%d\n", key);
  if (fclose(f) != 0) {
    perror("fail to close fire");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
