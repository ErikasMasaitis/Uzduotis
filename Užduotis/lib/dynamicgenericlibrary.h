#ifndef mainlab_h
#define mainlab_h

#include <stdlib.h>

struct Node
{
    void *data
    struct Node *next;
};

struct Node *head;
struct Node *current;

extern void push(struct Node** head_ref, void *new_data, size_t data_size);
extern void printList(struct Node *node, void (*fptr)(void *));
//extern int length();

#endif