/**
 * Derek Hessinger
 * Prof. Ying Li
 * CS 333
 * 10/28/24
 * 
 * Header file for linked list in C++
**/
#include <stdlib.h>
#include <stdio.h>
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <class T>
class Node {
    public:
        // Arbitrary data pointer
        T* data_ptr;
        // Pointer to the next node
        Node<T>* next_ptr;
        // Pointer to the last node
        Node<T>* last_ptr;
};

template <class T>
class LinkedList{
    private:
        // Head pointer
        Node<T> *head_ptr;
        // field to track size of ll
        int size;
    public:

        // Constructor to initialize size to 0
        LinkedList() : head_ptr(nullptr), size(0) {}

        // adds a node to the front of the list, storing the given data in the node.
        void ll_push(T* );

        // removes the node at the front of the list and returns the associated data.
        T *ll_pop();

        // adds a node to the end of the list, storing the given data in the node.
        void ll_append(T*);

        /*removes the first node in the list whose data matches target given the 
        comparison function. The function returns the pointer to the data in the removed node.*/
        T *ll_remove(T*, int (*compfunc)(T*, T*));

        /*finds the first node in the list whose data matches target given the comparison function.
        The function returns the pointer to the data in the node. If the target is not in the list, then the function returns NULL.*/
        T *ll_find(T*, int (*compfunc)(T*, T*));

        // returns the size of the list.
        int ll_size();

        // removes all of the nodes from the list, freeing the associated data using the given function.
        void ll_clear(void (*freefunc)(T*));

        // traverses the list and applies the given function to the data at each node.
        void ll_map(void(*mapfunc)(T*));
};
#endif