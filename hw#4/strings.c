#include <stdio.h>

size_t strlen(char* str){
   size_t len = 0;
   while (str[len]) {
     len++;
   }
   return len;
}

void strcpy(char* dst, char* src) {
  const N = strlen(src);
  char new[N];
  int i = 0;
  for (size_t i = 0; i < N; i++) {
    new[i] = src[i];
  }
  for (size_t i = 0; i < N; i++) {
    dst[i] = new[i];
  }
  dst[N] = 0;
}

size_t strcmp(char* s1, char* s2) {
  size_t i = 0;
  while (s1[i] || s2[i]) {
    if (s1[i] < s2[i]) {
      return -1;
    }
    if (s1[i] > s2[i]) {
      return 1;
    }
    i++;
  }
    return 0;
}

void strcat(char* dst, char* src) {
  while (*dst) {
    dst++;
  }
  while (*src) {
    *dst = *src;
    src++;
    dst++;
  }
    *dst = *src;
}

/*int main (int argc, char const *argv[]) {
  char str1[10] = "abc";
  char str2[10] = "aabc";
  strcat(str1, str2);
  printf("%s\n", str1);
  //printf("%d\n" ,sttrcmp(str1, str2));
  return 0;
}
*/
