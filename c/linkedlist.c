/**
 * Derek Hessinger
 * Prof. Ying Li
 * CS 333
 * 10/28/24
 * 
 * Linked List in C 
 * 
**/

#include <stdio.h>
#include "linkedlist.h"

// creates a new LinkedList struct, initializes it, and returns it.
LinkedList *ll_create(){
    // initialize linked list
    LinkedList *ll = (LinkedList*)malloc(sizeof(LinkedList));
    ll->head_ptr = (Node*)malloc(sizeof(Node));
    ll->size = 0;
    return ll;
}

// adds a node to the front of the list, storing the given data in the node.
void ll_push(LinkedList *l, void *data){
    // create a new node
    Node *new = (Node*)malloc(sizeof(Node));
    new->data_ptr = data;
    new->next_ptr = l->head_ptr;
    new->count = 0;
    // add previous pointer to head
    l->head_ptr->last_ptr = new;
    // update head
    l->head_ptr = new;
    l->size++;
}

//  removes the node at the front of the list and returns the associated data.
void *ll_pop(LinkedList *l){
    // get node from head
    Node *tmp = l->head_ptr;

    // set head pointer in ll to be the next node
    l->head_ptr = tmp->next_ptr;
    // return the contents of tmp
    void *data = tmp->data_ptr;
    free(tmp);
    l->size--;
    return data;
}

// adds a node to the end of the list, storing the given data in the node.
void ll_append(LinkedList *l, void *data){
    // create new node
    Node *new  = (Node*)malloc(sizeof(Node));
    // add data to new
    new->data_ptr = data;

    // check for null linked list
    if (l->head_ptr==NULL){
        l->head_ptr = new;
        l->size++;
        return;
    }
    // create temp node pointer
    Node *tmp = l->head_ptr;
    // iterate through the ll
    // while (tmp->next_ptr!=NULL){
    //     tmp = tmp->next_ptr;
    // }
    for (int i = 0; i<l->size-1; i++){
        tmp = tmp->next_ptr;
    }
    // add new node to list
    tmp->next_ptr = new;
    new->last_ptr = tmp;

    l->size++;
}

void *ll_remove(LinkedList *l, void *target, int (*compfunc)(void *, void *)) {

    // set temp node to head
    Node *tmp = l->head_ptr;

    // iterate through the linked list
    for (int i = 0; i < l->size; i++) {
        
        // Check if current node's data matches the target
        if (compfunc(tmp->data_ptr, target) != 0) {
            // Handle head node case
            if (tmp == l->head_ptr) {
                // set the head pointer of the ll to the next node
                l->head_ptr = tmp->next_ptr;
                if (l->head_ptr != NULL) {  // Update the new head's last_ptr if it exists
                    l->head_ptr->last_ptr = NULL;
                }
            } else {
                // Set the next pointer for the previous node
                tmp->last_ptr->next_ptr = tmp->next_ptr;
            }

            // Handle non-last node case
            if (tmp->next_ptr != NULL) {
                // Set the last pointer for the next node
                tmp->next_ptr->last_ptr = tmp->last_ptr;
            }

            // Return data and free the node
            void *data = tmp->data_ptr;
            free(tmp);
            l->size--;

            //printf("Found and removed node\n");
            return data;
        }

        tmp = tmp->next_ptr;
    }

    printf("Target not found\n");
    return NULL;  // Target not found
}


/*finds the first node in the list whose data matches target given the comparison function. 
The function returns the pointer to the data in the node. If the target is not in the list, 
then the function returns NULL.*/
void *ll_find(LinkedList *l, void *target, int (*compfunc)(void *, void *)){
    Node *tmp = l->head_ptr;

    for (int i = 0; i < l->size; i++) {
        if (compfunc(target, tmp->data_ptr)==1){
            return tmp->data_ptr;
        }
        tmp = tmp->next_ptr;
    }
    return NULL;
}

// returns the size of the list.
int ll_size(LinkedList *l){
    return l->size;
}

// removes all of the nodes from the list, freeing the associated data using the given function.
void ll_clear(LinkedList *l, void (*freefunc)(void *)){

    for(int i = 0; i<l->size; i++){
        Node *tmp = l->head_ptr;
        l->head_ptr = tmp->next_ptr; 
        freefunc(tmp); 
    }
    // set the size back to 0
    l->size = 0;
}

//  traverses the list and applies the given function to the data at each node.
void ll_map(LinkedList *l, void (*mapfunc)(void *)){
    Node *tmp = l->head_ptr;
    // loop through all nodes in the LL
    for(int i = 0; i<l->size && tmp != NULL; i++){
        mapfunc(tmp->data_ptr);
        tmp = tmp->next_ptr;
    }
}
/*
int main(){
    LinkedList *l;
    l = ll_create();
    printf("%p\n", l->head_ptr);
    printf("%p\n", l->head_ptr->last_ptr);
    printf("%p\n", l->head_ptr->next_ptr);
    int *a = malloc(sizeof(int));
    *a= 12;
    ll_push(l, a);
    printf("%p\n", l->head_ptr);
    printf("%p\n", l->head_ptr->last_ptr);
    printf("%p\n", l->head_ptr->next_ptr);
    Node *tmp = l->head_ptr;
    tmp = tmp->next_ptr;
    printf("%p\n", tmp);
    printf("%p\n", tmp->last_ptr);
    printf("%p\n", tmp->next_ptr);
}
*/