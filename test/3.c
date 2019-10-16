#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  const int N = 5;
  int mas[256];
  for (int i = 0; i < 256; i++){
    mas[i] = 0;
  }
  for (int i = 0; i < N; i++){
    int x = 0;
    scanf("%d", &x);
    mas[x]++;
  }
  for (int i = 0; i < 256; i++){
    if(mas[i] == 1){
      printf("%d\n", i);
    }
  }
  return 0;
}
