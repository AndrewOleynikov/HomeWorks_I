#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

struct Node
{
    int value;
    struct Node *next;
};

struct List
{
    struct Node *head;
};

struct Node* createNode(int value);
struct List* createList();
void addHead(struct List *list, int value);
void addTail(struct List *list, int value);
void addAfter(struct List *list, int after, int value);
void deleteNode(struct List *list, int value);
void eraseList(struct List *list);
void makeCycle(struct List *list, int from, int to);
int haveLoop(struct List *list);
void printList(struct List *list);


#endif // LIST_H_INCLUDED
