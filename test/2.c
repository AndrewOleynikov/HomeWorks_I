#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

int main(int argc, char const *argv[]){
  const size_t N = 50;
  char str[N];
  scanf("%s", str);
  long ans = 0;
  int d = 1;
  for (int i = 0; i < N-1; i++){
    d *= 10;
  }
  int correct = 1;
  int sign = 0;
  if (str[0] == '-'){
    sign = 1;
  }
  int i = 0;
  if (sign == 1){
    i = 1;
  }
  for (; i < N; i++){
    int numb = str[i] - '0';
    if('0' > numb > '9'){
      correct = 0;
      break;
    }
    ans += d*numb;
    d /= 10;
    //printf("%d\n", numb);
  }
  if (sign == 1){
    ans /= 10 * (-1);
  }
  if(ans > INT_MAX || ans < INT_MIN){
    printf("%s\n", "ERROR");
  } else{
    printf("%d\n", ans);
  }
  return 0;
}
