#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <malloc.h>
#include <sys/stat.h>
#include "mman.h"
/*
int strCmp(void* p1, void* p2)
{
	char* s1, * s2;
	s1 = *(char**)p1;
	s2 = *(char**)p2;
	return strcmp(s1, s2);
}
*/
int strCmp(const void* p1, const void* p2)
{
	char* s1 = *(char**)p1;
	char* s2 = *(char**)p2;
	for (int i = 0; s1[i] != '\r' && s2[i] != '\r' && s1[i] != '\n' && s2[i] != '\n'; i++)
	{
		if (s1[i] < s2[i])
		{
			return -1;
		}
		if (s1[i] > s2[i])
        {
			return 1;
        }
	}
	return 0;
}

void copyAdressStr(char **strings, char *input)
{
    size_t i = 0, iStr = 0, iInp = 0;
    while (input[i])
    {
        if (input[i] == '\n')
        {
            strings[iStr] = &input[iInp];
            iStr++;
            iInp = i + 1;
        }
        i++;
    }
}

int main() {
    int mFile = open("text.txt", O_RDWR, 0);
    if (mFile < 0)
    {
        printf("ERRORo");
        exit(1);
    }
    FILE* fout = fopen("output.txt", "w");
    if (fout == NULL)
    {
        printf("ERRORm");
        exit(1);
    }

    struct stat info;
	fstat(mFile, &info);
	size_t size = info.st_size;
    char* input = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, mFile, 0);
    int inputL = strlen(input);

    int maxi = 0, helper = 0, N = 0;
    for (size_t i = 0; i < inputL; i++)
    {
        if (input[i] == '\n')
        {
            N++;
        }
    }

    char **str = (char**)malloc(N * sizeof(char*));
    if (str == NULL)
    {
        printf("ERRORm");
        exit(1);
    }

    copyAdressStr(str, input);
    qsort(str, N, sizeof(char*), strCmp);

    for (size_t i = 0; i < N; i++)
    {
        size_t j = 0;
        while (str[i][j] != '\n')
        {
            fputc(str[i][j], fout);
            j++;
        }
    }

    close(mFile);
    fclose(fout);
    free(str);
    munmap(input, inputL);

    return 0;
}
