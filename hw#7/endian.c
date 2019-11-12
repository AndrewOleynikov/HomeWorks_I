#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x = 1;
    if (*((char *)(&x))
    {
        printf("little Endian");
    } else {
        printf("Big Endian");
    }
    return 0;
}
