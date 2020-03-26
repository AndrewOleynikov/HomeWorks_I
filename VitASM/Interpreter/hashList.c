//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <limits.h>
#include "hashList.h"

struct Node* createNode(int value, char *word)
{
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    if (!node)
    {
        printf("ERRORm\n");
        return NULL;
    }
    node->value = value;
    node->next = NULL;
    strcpy(node->word, word);
    return node;
}

struct List* createList()
{
    struct List *list = (struct List*)malloc(sizeof(struct List));
    if (!list)
    {
        printf("ERRORm\n");
        return NULL;
    }
    list->head = NULL;
    return list;
}

void addHead(struct List *list, int value, char *word)
{
    struct Node *node = createNode(value, word);
    node->next = list->head;
    list->head = node;
}

void addTail(struct List *list, int value, char *word)
{
   /// struct Node *node = (struct Node*)malloc(sizeof(struct Node));-------------------ОШИБКА
    /*if (list->head)///!node NNN
    {
        struct Node *node = (struct Node*)malloc(sizeof(struct Node));
        printf("ERRORm\n");
        return;
    }*/
    if (list->head)
    {
        struct Node *node = (struct Node*)malloc(sizeof(struct Node));///-----------ИСПРАВЛЕНИЕ
        if (!node)
        {
            printf("ERRORm\n");
            return;
        }
        node = list->head;
        /*if (strcmp(node->word, word) == 0 && node->value)
        {
            node->value++;
            return;
        }*/
        while (node->next)
        {
            /*if (strcmp(node->word, word) == 0 && node->value)
            {
                node->value++;
                return;
            }*/
            node = node->next;
        }
       /* if (strcmp(node->word, word) == 0 && node->value)
        {
            node->value++;
            return;
        }*/
        node->next = createNode(value, word);
        strcpy(node->next->word, word);
    } else {
        list->head = createNode(value, word);
    }
}

void addAfter(struct List *list, int after, int value, char *word)
{
    struct Node *node = list->head;
    while (node)
    {
        if (node->value == after)
        {
            struct Node* newNode = createNode(value, word);
            newNode->next = node->next;
            node->next = newNode;
            strcpy(node->word, word);
            break;
        }
        node = node->next;
    }
}

void deleteNode(struct List *list, char *word)
{
    if (list->head->next)
    {
        struct Node *before = (struct Node*)malloc(sizeof(struct Node));
        if (!before)
        {
            printf("ERRORm\n");
            return;
        }
        strcpy(before->word, list->head->word);
        before = list->head;
        struct Node *after = (struct Node*)malloc(sizeof(struct Node));
        if (!after)
        {
            printf("ERRORm\n");
            return;
        }
        strcpy(after->word, list->head->word);
        after = list->head->next;
        while (after)
        {
            if (!strcmp(after->word, word))
            {
                struct Node *toDelete = (struct Node*)malloc(sizeof(struct Node));
                if (!toDelete)
                {
                    printf("ERRORm\n");
                    return;
                }
                toDelete = after;
               /* if (after->value > 1)
                {
                    after->value--;
                    return;
                }*/
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
        if (strcmp(list->head->word, word) == 0)
        {
            /*if (list->head->value > 1){
                list->head->value--;
                return;
            }*/
            struct Node *toDelete = (struct Node*)malloc(sizeof(struct Node));
            if (!toDelete)
            {
                printf("ERRORm\n");
                return;
            }
            toDelete->next = NULL;
            list->head = toDelete->next;
            free(toDelete);
            return;
        }
    }
    if (strcmp(list->head->word, word) == 0)
    {/*
        if (list->head->value > 1)
        {
            list->head->value--;
            return;
        }*/
        struct Node *toDelete = (struct Node*)malloc(sizeof(struct Node));
        if (!toDelete)
        {
            printf("ERRORm\n");
            return;
        }

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
    struct Node *one = createNode(list->head->value, " ");
    struct Node *two = createNode(list->head->value, " ");
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
    free(one);
    free(two);
}

size_t listSize(struct List *list)
{
    if (list->head)
    {
        struct Node *node = list->head;
        size_t size = 0;
        while (node->next)
        {
            size++;
            node = node->next;
        }
        if (node)
        {
            return size + 1;
        }
        return 0;
    }
}

size_t countIndividuals(struct List *list)
{
    if (list->head)
    {
        size_t ans = 0;
        struct Node *node = list->head;
        while (node->next)
        {
            ans++;
            node = node->next;
        }
        return ans + 1;
    } else {
        return 0;
    }
}

void printList(struct List *list)
{
    if (list->head && !haveLoop(list))
    {
        struct Node *node = list->head;
        while (node->next)
        {
            printf("%d %s\n", node->value, node->word);
            node = node->next;

        }
        printf("%d %s\n", node->value, node->word);
    }
    if (list->head && haveLoop(list))
    {
        printf("List have cycle\n");
    }
}
