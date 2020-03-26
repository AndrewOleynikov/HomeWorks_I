//#define _CRT_SECURE_NO_WARNINGS
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

    table->entries = (struct List**)malloc(sizeof(struct List) * size);
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
    free(table->entries);/// ОШИБКА (ОТСУТСТВИЕ ЭТОЙ ОПЕРАЦИИ)
    free(table);
}

void addToTable(struct HashTable *table, char *word, size_t numb)
{
    size_t it = table->fn(word);
    it %= table->size;
    addTail(table->entries[it], numb, word);
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

void printHashTable(struct HashTable *table)
{
    for (size_t i = 0; i < table->size; i++)
    {
        printList(table->entries[i]);
    }
}
