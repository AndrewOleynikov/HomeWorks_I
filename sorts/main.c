#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include <time.h>

unsigned const N = 600;

void merge(unsigned *arr, unsigned first, unsigned last)
{
    unsigned *b;
    b = (unsigned*)malloc((last - first + 1)*sizeof(unsigned));
    if (b == NULL)
    {
        printf("ERROR\n");
    }

    unsigned left, right, middle;
    middle = (first + last) / 2;
    left = first;
    right = middle + 1;

    unsigned i = 0;
    while (left <= middle && right <= last)
    {
        if (arr[left] < arr[right])
        {
            b[i] = arr[left];
            left++;
            i++;
        } else {
            b[i] = arr[right];
            right++;
            i++;
        }
    }

    while (left <= middle)
    {
        b[i] = arr[left];
        i++;
        left++;
    }

    while (right <= last)
    {
        b[i] = arr[right];
        i++;
        right++;
    }

    for (unsigned i = first; i <= last; i++)
    {
        arr[i] = b[i - first];
    }

    free(b);
}

void subMergeSort(unsigned *arr, unsigned first, unsigned last)
{
    if (first == last)
    {
        return;
    }

    subMergeSort(arr, first, (first + last) / 2);
    subMergeSort(arr, (first + last) / 2 + 1, last);

    merge(arr, first, last);
}

void mergeSort(unsigned *arr, unsigned size)
{
    subMergeSort(arr, 0, size);
}

void bblSort(unsigned *arr, unsigned size)
{
    for (size_t i = size - 1; i > 0; i--)
    {
        for (size_t j = 0; j < i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                arr[j] ^= arr[j + 1];
                arr[j + 1] ^= arr[j];
                arr[j] ^= arr[j + 1];
            }
        }
    }
}

void countSort(unsigned *arr, unsigned size)
{
    unsigned *numbers;
    numbers = (unsigned*)malloc(N*sizeof(size_t));
    if (numbers == NULL)
    {
        printf("ERROR\n");
    }
    for (size_t i = 0; i < N; i++)
    {
        numbers[i] = 0;
    }

    for (size_t i = 0; i < size; i++)
    {
        numbers[arr[i]]++;
    }

    size_t l = 0;
    for (size_t i = 0; i < N; i++)
    {
        if (numbers[i])
        {
            for (size_t j = 0; j < numbers[i]; j++)
            {
                arr[l] = i;
                l++;
            }
        }
    }
    free(numbers);
}

void showTime(unsigned *a, unsigned size, void(*fn)(unsigned,unsigned))
{
    clock_t begin = clock();
    fn(a, size);
    clock_t end = clock();
    printf("size: %d time: %f\n", size, (double)(end - begin) / CLOCKS_PER_SEC);
}

int main()
{
    int count[] = {5 , 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

    srand(300);

    for (size_t i = 0; i < sizeof(count) / sizeof(count[0]); i++)
    {
        unsigned *a = (unsigned*)malloc(count[i]*sizeof(unsigned));
        unsigned *b = (unsigned*)malloc(count[i]*sizeof(unsigned));
        unsigned *c = (unsigned*)malloc(count[i]*sizeof(unsigned));
        if (!a || !b || !c)
        {
            printf("ERRORm\n");
            exit(1);
        }
        for (size_t j = 0; j < count[i]; j++)
        {
            unsigned value = rand() % N;
            a[j] = value;
            b[j] = value;
            c[j] = value;
        }
        printf("Count sort: ");
        showTime(a, count[i], countSort);
        printf("Merge sort: ");
        showTime(b, count[i], mergeSort);
        printf("Buble sort: ");
        showTime(c, count[i], bblSort);
        free(a);
        free(b);
        free(c);
    }
    return 0;
}
