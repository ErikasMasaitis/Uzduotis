#ifndef mainlab_h
#define mainlab_h

#include <stdlib.h>

struct Node
{
    char *data;
    struct Node *next;
};

struct Node *head;
struct Node *current;

extern void push(char *x);
extern void printList();
extern int length();

#endif