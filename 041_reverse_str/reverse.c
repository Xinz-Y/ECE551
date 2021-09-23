#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  if (!str) {
    return;
  }
  const char * p = str;
  int count = 0;
  while (*p != '\0') {
    count = count + 1;
    p++;
  }

  char str_n[count + 1];

  str_n[count] = '\0';

  for (int i = 0; i < count; i++) {
    str_n[i] = str[count - 1 - i];
  }
  if (count != 0) {
    strncpy(str, str_n, count + 1);
  }
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be "
                "no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
