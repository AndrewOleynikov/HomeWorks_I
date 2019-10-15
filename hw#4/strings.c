#include <stdio.h>

size_t strlen(char* str){
   size_t len = 0;
   while(str[len]){
     len++;
   }
   return len;
}

void strcpy(char* dst, char* src){
  char new[strlen(src)];
  int i = 0;
  for(size_t i = 0; i < strlen(src); i++){
    new[i] = src[i];
  }
  for(size_t i = 0; i < strlen(new); i++){
    dst[i] = new[i];
  }
  dst[strlen(new)] = 0;
}

size_t strcmp(char* s1, char* s2) {
  size_t i = 0;
  while(s1[i] || s2[i]){
    if(s1[i] < s2[i]){
      return -1;
    }
    if(s1[i] > s2[i]){
      return 1;
    }
    i++;
  }
    return 0;
}

void strcat(char* dst, char* src){
  char catStr[strlen(dst) + strlen(src)];
  for(size_t i = 0; i < strlen(dst); i++){
    catStr[i] = dst[i];
  }
  int i = strlen(dst), size = 0;
  while(size < strlen(src)){
    catStr[i] = src[size];
    size++;
    i++;
  }
  for(int i = 0; i < strlen(catStr); i++){
    dst[i] = catStr[i];
  }
}

/*int main(int argc, char const *argv[]) {
  char str1[] = "abc";
  char str2[] = "aabc";
  strcat(str2, str1);
  printf("%s\n", str2);
  //printf("%d\n" ,sttrcmp(str1, str2));
  return 0;
}
*/
