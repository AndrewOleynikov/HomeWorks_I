#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "list.h"

#define PRINT 1
#define CREATE 2
#define HEADADD 3
#define TAILADD 4
#define AFTERADD 5
#define NODEDELETE 6
#define LISTERASE 7
#define HELPLIST 9

void help()
{
    printf("Print List - 1\n");
    printf("Create List - 2\n");
    printf("Add Head - 3\n");
    printf("Add Tail - 4\n");
    printf("Add After (value) - 5\n");
    printf("Delete Element (value) - 6\n");
    printf("Erase List - 7\n");
    printf("Exit - 0\n\n");
}

int main()
{
    help();

    struct List *list;
    int x = -1;
    int value;
    int after;
    int ch = 0;

    while (x)
    {
        scanf("%d", &x);

        switch (x)
        {
        case PRINT:
            if (ch){
                printList(list);
                printf("\n");
                printf("help - 9 \n");
            } else {
                printf("Firstly create list \n");
                printf("help - 9 \n");
            }
            break;
        case CREATE:
            list = createList();
            printf("List was created\n");
            printf("help - 9 \n");
            ch = 1;
            break;
        case HEADADD:
            if (ch)
            {
                printf("Your value: ");
                scanf("%d", &value);
                addHead(list, value);
                printf("help - 9 \n");
            } else {
                printf("Firstly create list \n");
                printf("help - 9 \n");
            }
            break;
        case TAILADD:
            if (ch)
            {
                printf("Your value: ");
                scanf("%d", &value);
                addTail(list, value);
                printf("help - 9 \n");
            } else {
                printf("Firstly create list \n");
                printf("help - 9 \n");
            }
            break;
        case AFTERADD:
            if (ch){
                printf("After element with value: ");
                scanf("%d", &after);
                printf("Add value: ");
                scanf("%d", &value);
                addAfter(list, after, value);
                printf("help - 9 \n");
            } else {
                printf("Firstly create list \n");
                printf("help - 9 \n");
            }
            break;
        case NODEDELETE:
            if (ch)
            {
                printf("Your value: ");
                scanf("%d", &value);
                deleteNode(list, value);
                printf("help - 9 \n");
            } else {
                printf("Firstly create list \n");
                printf("help - 9 \n");
            }
            break;
        case LISTERASE:
            if (ch)
            {
                eraseList(list);
                printf("list was erased");
                printf("help - 9 \n");
            } else {
                printf("Firstly create list \n");
                printf("help - 9 \n");
            }
            break;
        case HELPLIST:
            help();
        }
    }
    if (ch)
    {
        free(list);
    }
    return 0;
}
