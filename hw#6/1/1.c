#include <stdio.h>
#include <stdlib.h>

size_t fib(int n)
{
    int first = 1, second = 0;
    for (int i = 0; i < n; i++)
    {
        first += second;
        second = first - second;
    }
    return first;
}

int main()
{
    size_t n;
    printf("write number of Fib: ");
    scanf("%d", &n);
    printf("%d ", fib(n));
    return 0;
}
