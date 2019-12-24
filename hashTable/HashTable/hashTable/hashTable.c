#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "hashList.h"
#include "hashTable.h"

struct HashTable *createHashTable(size_t size, size_t(*fn)(char* word))
{
    struct HashTable *table = (struct HashTable*)malloc(sizeof(struct HashTable));

    table->entries = (struct List*)malloc(sizeof(struct List) * size);
    for (size_t i = 0; i < size; i++)
    {
       table->entries[i] = createList();
    }
    table->size = size;
    table->fn = fn;
    table->countElements = 0;
    return table;
}


void deleteHashTable(struct HashTable *table)
{
    for (size_t i = 0; i < table->size; i++)
    {
        eraseList(table->entries[i]);
    }
    memset(table, 0, sizeof(struct HashTable));
    free(table);
}

void addToTable(struct HashTable *table, char *word)
{
    size_t it = table->fn(word);
    it %= table->size;
    addTail(table->entries[it], 1, word);
    table->countElements++;
}

void deleteFromTable(struct HashTable *table, char *word)
{
    size_t it = table->fn(word);
    it %= table->size;
    deleteNode(table->entries[it], word);
    table->countElements--;
}

int find(struct HashTable *table, char *word)
{
    size_t it = table->fn(word);
    it %= table->size;
    if (!table->entries[it]->head)
    {
        return 0;
    }
    struct Node *node = table->entries[it]->head;
    while (node)
    {
        if (strcmp(node->word, word) == 0)
        {
            return node->value;
        }
        node = node->next;
    }
    return 0;
}

void showTableInfo(struct HashTable *table)
{
    printf("\n\n");
    size_t countUnempty = 0;
    size_t countElem = 0;
    size_t middleLength = 0;
    size_t minList = INT_MAX;
    size_t maxList = 0;
    size_t sum = 0;
    size_t countInd = 0;
    for (size_t i = 0; i < table->size; i++)
    {
        printList(table->entries[i]);
        size_t h = listSize(table->entries[i]);
        countInd += countIndividuals(table->entries[i]);
        if (h)
        {
            sum += h;
            countUnempty++;
        }
        if (maxList < h)
        {
            maxList = h;
        }
        if (minList > h)
        {
            minList = h;
        }
    }

    printf("Count of all elements: %d\n", table->countElements);
    printf("Count of different elements: %d\n ", countInd);
    printf("Count of unemptyes slots: %d\n", countUnempty);
    printf("Middle value of length of chain: %d\n", sum / countUnempty);
    printf("Max length of chain: %d\n", maxList);
    if (minList < INT_MAX)
    {
        printf("Min length of chain: %d\n", minList);
    } else {
        printf("Min length of chain: %d\n", 0);
    }
}
