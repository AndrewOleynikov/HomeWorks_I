#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "list.h"

struct Node* createNode(int value)
{
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->value = value;                                           ///Почему нельзя писать *(node).value = value?????
    node->next = NULL;
    return node;
}

struct List* createList()
{
    struct List *list = (struct List*)malloc(sizeof(struct List));
    list->head = NULL;
    return list;
}

void addHead(struct List *list, int value)
{
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->value = value;
    node->next = list->head;
    list->head = node;
}

void addTail(struct List *list, int value)
{
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    if (list->head)
    {
        node = list->head;
        while (node->next)
        {
            node = node->next;
        }
        node->next = createNode(value);
    } else {
        list->head = createNode(value);
    }
}

void addAfter(struct List *list, int after, int value)
{
    struct Node *node = list->head;
    while (node)
    {
        if (node->value == after)
        {
            struct Node* newNode = createNode(value);
            newNode->next = node->next;
            node->next = newNode;
            break;
        }
        node = node->next;
    }
}

void deleteNode(struct List *list, int value)
{
    if (list->head->next)
    {
        struct Node *before = (struct Node*)malloc(sizeof(struct Node));
        before->value = list->head->value;
        before = list->head;
        struct Node *after = (struct Node*)malloc(sizeof(struct Node));
        after->value = list->head->value;
        after = list->head->next;

        while (after)
        {
            if (after->value == value)
            {
                struct Node *toDelete = (struct Node*)malloc(sizeof(struct Node));
                toDelete = after;
                if (toDelete->next)
                {
                    after = toDelete->next;
                    before->next = after;
                    free(toDelete);
                } else {
                    after = NULL;
                    before->next = after;
                    free(toDelete);
                }
            } else {
                after = after->next;
                before= before->next;
            }
        }
    } else {
        if (list->head->value == value)
        {
            struct Node *toDelete = (struct Node*)malloc(sizeof(struct Node));
            toDelete->next = NULL;
            list->head = toDelete->next;
            free(toDelete);
            return;
        }
    }
    if (list->head->value == value)
    {
        struct Node *toDelete = (struct Node*)malloc(sizeof(struct Node));
        toDelete = list->head;
        list->head = toDelete->next;
        free(toDelete);
    }
}


void eraseList(struct List *list)
{
    struct Node *node = list->head;
    while (node)
    {
        struct Node *toDelete = node;
        node = node->next;
        free(toDelete);
    }
    list->head = NULL;
    free(list);
}

void makeCycle(struct List *list, int from, int to)
{
    if (!list->head->next)
    {
        printf("Need more elements\n");
        return;
    } else {
        struct Node *node = list->head;
        struct Node *nodeFrom = NULL;
        while (node->next)
        {
            if (node->value == from)
            {
                nodeFrom = node;
            }
            if (node->value == to && nodeFrom)
            {
                node->next = nodeFrom;
                return;
            }
            node = node->next;
        }
        if ( node->value == to)
        {
            node->next = nodeFrom;
        }
    }
}

int haveLoop(struct List *list)
{
    struct Node *one = createNode(list->head->value);
    struct Node *two = createNode(list->head->value);
    while(1)
    {
        if ((one->next == NULL) || (two->next->next == NULL))
        {
            return 0;
        }
        one = one->next;
        two = two->next->next;
        if (one == two)
        {
            return 1;
        }
    }
}

void printList(struct List *list)
{
    if (list->head && !haveLoop(list))
    {
        struct Node *node = list->head;
        while (node->next)
        {
            printf("%d ", node->value);
            node = node->next;
        }
        printf("%d ", node->value);
    }
    if (list->head && haveLoop(list))
    {
        printf("List have cycle\n");
    }
}
