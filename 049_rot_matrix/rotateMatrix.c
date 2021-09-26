#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_SIZE 12

void rotateMatrix(char mat[10][10]) {
  char mat_r[10][10];
  for (int c = 0; c < 10; c++) {
    for (int r = 0; r < 10; r++) {
      mat_r[r][c] = mat[9 - c][r];
    }
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", mat_r[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: Wrong number of argv\n");
    return EXIT_FAILURE;
  }
  char mat[10][10];
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  char line[LINE_SIZE];
  int count = 0;
  while (fgets(line, LINE_SIZE, f) != NULL) {
    count = count + 1;
    //check if each line have the right number of elments
    if (strchr(line, '\n') == NULL) {
      fprintf(stderr, "Line in the file is too long\n");
      return EXIT_FAILURE;
    }
    else if (line[10] == '\0') {
      fprintf(stderr, "Line in the file is too short\n");
      return EXIT_FAILURE;
    }
    // now we get the right number of elemnts in the row
    if (count > 10) {
      fprintf(stderr, "The number of rows is too large\n");
      return EXIT_FAILURE;
    }
    for (int i = 0; i < 10; i++) {
      mat[count - 1][i] = line[i];
    }
  }
  // check if the number of rows is 10
  if (count != 10) {
    fprintf(stderr, "The number of rows is too small");
    return EXIT_FAILURE;
  }
  // now we have our matrix[10][10], then do rotate
  rotateMatrix(mat);
  if (fclose(f) != 0) {
    perror("fail to close fire");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
