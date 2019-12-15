#include <stdio.h>
#include <stdlib.h>

int int0g;
char char0g;
int float0g;

int fn1(int a)
{
    int j = 13;
    printf("LOCAL IN FN %p\n\n", &j);
    return a;
}

char fn2(char a)
{
    int *dynFn = (int*)malloc(sizeof(int)*2);
    printf("DYN IN FN %p \n\n", dynFn);
    free(dynFn);
    return a;
}

void fn3()
{
    static const size_t size_tc;
    printf("STATIC IN FN %p \n\n", &size_tc);
}

const float floatc;

int main()
{
    static int intc;
    static char charc;
    int int0;
    char char0;
    int float0;
    int *x = (int*)malloc(sizeof(int)*2);
    if (!x)
    {
        printf("ERRORm \n");
    }
    char *y = (char*)malloc(sizeof(char)*2);
    if (!y)
    {
        printf("ERRORm \n");
    }
    float *z = (float*)malloc(sizeof(float)*2);
    if (!z)
    {
        printf("ERRORm \n");
    }
    printf("LOCAL: \n");
    printf("%p \n", &int0);
    printf("%p \n", &char0);
    printf("%p \n", &float0);
    fn1(5);
    printf("GLOBAL: \n");
    printf("%p \n", &int0g);
    printf("%p \n", &char0g);
    printf("%p \n", &floatc);
    printf("%p \n\n", &float0g);
    printf("USR FN: \n");
    printf("%p \n", &fn1);
    printf("%p \n", &fn2);
    printf("%p \n\n", &fn3);
    printf("SYS FN: \n");
    printf("%p \n", &printf);
    printf("%p \n", &scanf);
    printf("%p \n\n", &getc);
    printf("DINAMIC: \n");
    printf("%p \n", x);
    printf("%p \n", y);
    printf("%p \n", z);
    fn2('a');
    printf("STATIC")
    printf("%p \n", &intc);
    printf("%p \n", &charc);
    fn3();

    free(x);
    free(y);
    free(z);
    return 0;
}
