#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int main()
{
    const size_t N = 50;
    char str[N];
    for (int i = 0; i < N; i++) {
        str[i] = NULL;
    }
    printf("%s","write number: ");
    scanf("%s", str);
    int correct = 1;
    int sign = 0;
    int i = 0;
    if (str[0] == '-') {
        sign = 1;
        i = 1;
    }
    unsigned ans = 0;
    for (; i < strlen(str); i++) {
        if (str[i] < '0' || str[i] > '9') {
            printf("%s", "Error input");
            correct = 0;
            break;
        }
        int numb = str[i] - '0';
      //  printf("%d", numb);
        ans = ans * 10 + numb;
        if (ans > INT_MAX) {
            correct = 0;
            printf("%s", "Error overflow");
            break;
        }
    }
    if (correct == 1) {
        if (sign) {
            printf("%d", ans * (-1));
        } else {
            printf("%d5", ans);
        }
    }

    return 0;
}
