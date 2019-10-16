#include <stdlib.h>

int fib(int a){
  if (a == 0){
    return 0;
  }
  if (a == 1){
    return 1;
  }
  return fib(a - 1) + fib(a - 2);
}

int main(int argc, char const *argv[]){
  int input = 0;
  scanf("%d", &input);
  printf("%d\n", fib(input));
  return 0;
}
