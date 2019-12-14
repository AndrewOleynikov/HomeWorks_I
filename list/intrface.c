#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "list.h"

int main()
{
    printf("Print List - 1\n");
    printf("Create List - 2\n");
    printf("Add Head - 3\n");
    printf("Add Tail - 4\n");
    printf("Add After (value) - 5\n");
    printf("Delete Element (value) - 6\n");
    printf("Erase List - 7\n");
    printf("Exit - 0\n\n");

    struct List *list;

    int x = -1;
    int value;
    int after;

    while (x)
    {
        scanf("%d", &x);
        switch (x)
        {
        case 1:
            printList(list);
            printf("\n");
            break;
        case 2:
            list = createList();
            printf("List was created\n");
            break;
        case 3:
            printf("Your value: ");
            scanf("%d", &value);
            addHead(list, value);
            break;
        case 4:
            printf("Your value: ");
            scanf("%d", &value);
            addHead(list, value);
            break;
        case 5:
            printf("After element with value: ");
            scanf("%d", &after);
            printf("Add value: ");
            scanf("%d", &value);
            addAfter(list, after, value);
            break;
        case 6:
            printf("Your value: ");
            scanf("%d", &value);
            deleteNode(list, value);
            break;
        case 7:
            eraseList(list);
            printf("list was erased");
            break;
        }
    }
    free(list);
    return 0;
}
