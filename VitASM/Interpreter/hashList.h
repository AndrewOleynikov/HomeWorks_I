#ifndef HASHLIST_H_INCLUDED
#define HASHLIST_H_INCLUDED

struct Node
{
    int value;
    char word[50];
    struct Node *next;
};

struct List
{
    struct Node *head;
};


struct Node* createNode(int value, char *word);
struct List* createList();
void addHead(struct List *list, int value, char *word);
void addTail(struct List *list, int value, char *word);
void addAfter(struct List *list, int after, int value, char *word);
void deleteNode(struct List *list, char *word);
void eraseList(struct List *list);
void makeCycle(struct List *list, int from, int to);
int haveLoop(struct List *list);
size_t listSize(struct List *list);
void printList(struct List *list);

#endif // HASHLIST_H_INCLUDED
