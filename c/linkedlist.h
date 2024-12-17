/**
 * Derek Hessinger
 * Prof. Ying Li
 * CS 333
 * 10/28/24
 * 
 * Header file for linked list in C
**/
#include <stdlib.h>

typedef struct Node{
    // arbitrary data pointer
    void *data_ptr;
    // pointer to next node
    struct Node *next_ptr;
    // pointer to last node
    struct Node *last_ptr;
    // int counter for word (task 4)
    int count;

}Node;


typedef struct LinkedList{
    Node *head_ptr;
    // field to track size of ll
    int size;
}LinkedList;

// creates a new LinkedList struct, initializes it, and returns it.
LinkedList *ll_create();

// adds a node to the front of the list, storing the given data in the node.
void ll_push(LinkedList *l, void *data);

// removes the node at the front of the list and returns the associated data.
void *ll_pop(LinkedList *l);

// adds a node to the end of the list, storing the given data in the node.
void ll_append(LinkedList *l, void *data);

/*removes the first node in the list whose data matches target given the 
comparison function. The function returns the pointer to the data in the removed node.*/
void *ll_remove(LinkedList *l, void *target, int (*compfunc)(void *, void *));

/*finds the first node in the list whose data matches target given the comparison function.
The function returns the pointer to the data in the node. If the target is not in the list, then the function returns NULL.*/
void *ll_find(LinkedList *l, void *target, int (*compfunc)(void *, void *));

// returns the size of the list.
int ll_size(LinkedList *l);

// removes all of the nodes from the list, freeing the associated data using the given function.
void ll_clear(LinkedList *l, void (*freefunc)(void *));

// traverses the list and applies the given function to the data at each node.
void ll_map(LinkedList *l, void (*mapfunc)(void *));