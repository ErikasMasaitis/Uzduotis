#include <stdio.h>
#include <stdlib.h>

#include "dynamiclibrary.h"

struct Node *head = NULL;
struct Node *current = NULL;

/** Adds element to list
 */
void push(char *x)
{
	struct Node *temp;
	
	temp = (struct Node*)malloc(sizeof(struct Node));
	
    temp->data = x;
    temp->next = NULL;
    current = head;
	

    if(head == NULL) {
        head = temp;
    }
	else {
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = temp;
    }
}

/** Prints list values
 */
void printList() 
{
    struct Node *ptr = head;
    printf("Print list elements:\n");
    while(ptr != NULL) {
        printf("%s\n",ptr->data);
        ptr = ptr->next;
    }
}

/** Elements count of list
 */
int length() {
    int count = 0;
    struct Node *current = head;

    while(current != NULL) {
        count++;
		current = current->next;
    }

    return count;
}
