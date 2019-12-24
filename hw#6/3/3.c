#include <stdio.h>
#include <stdlib.h>

int main()
{
    const int arrSize = 256;
    printf("write count of numbers: ");
    int N = 0;
    scanf("%d", &N);
    int mas[arrSize] = {0}, check[arrSize] = {0};
    int to = 0;
    printf("write your numbers: ");
    for (int i = 0; i < N; i++)
    {
        int x = 0;
        scanf("%d", &x);
        if (!check[x])
        {
            to++;
            check[x] = 1;
            mas[i] = x;
        }
    }
    for (int i = 0; i < to; i++)
    {
        printf("%d ", mas[i]);
    }
    return 0;
}
