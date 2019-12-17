#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

struct HashTable
{
    struct List **entries;
    size_t (*fn)(char *word);
    size_t size;
    size_t countElements;
};

struct HashTable *createHashTable(size_t size, size_t(*fn)(char* word));
void deleteHashTable(struct HashTable *table);
void addToTable(struct HashTable *table, char *word);
void deleteFromTable(struct HashTable *table, char *word);
int find(struct HashTable *table, char *word);
void showTableInfo(struct HashTable *table);

#endif // HASHTABLE_H_INCLUDED
