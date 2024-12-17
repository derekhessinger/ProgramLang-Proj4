/**
 * Derek Hessinger
 * Prof. Ying Li
 * CS 333
 * 10/28/24
 * 
 * Linked List in C++
**/
#include <stdio.h>
#include "linkedlist.hpp"
#include <stdlib.h>
#include <iostream>
using namespace std;

// adds a node to the front of the list, storing the given data in the node.
template <class T>
void LinkedList<T>::ll_push(T *data)
{
	Node<T>* newNode = new Node<T>;
    newNode->data_ptr = data;
    newNode->next_ptr = nullptr;

    if (head_ptr == nullptr) {
        // List is empty, so head and tail should both point to the new node
        head_ptr = newNode;
    }
    else{
        Node<T> *newNode=new Node<T>;
	    newNode->data_ptr = data;
	    newNode->next_ptr= head_ptr;
	    head_ptr=newNode;
    }
    ++size;
}

// removes the node at the front of the list and returns the associated data.
template <class T>
T * LinkedList<T>::ll_pop(){
    // create a node pointer at head
    Node<T>* removedNode=head_ptr;
    // set head to the next ptr
    head_ptr = removedNode->next_ptr;
    head_ptr->last_ptr = NULL;
    removedNode->next_ptr = NULL;
    size--;
    return removedNode->data_ptr;
}

// adds a node to the end of the list, storing the given data in the node.
template <class T> 
void LinkedList<T>::ll_append(T *data){
    Node<T> *newNode=new Node<T>;
    newNode->data_ptr = data;

     // check for null linked list
    if (head_ptr==NULL){
        head_ptr = newNode;
        size++;
        return;
    }

    // create temp pointer
    Node<T> *tmp = head_ptr;
    for (int i = 0; i<size-1; i++){
        tmp = tmp->next_ptr;
    }   
    tmp->next_ptr = newNode;
    newNode->last_ptr = tmp;
    size++;
}

/*removes the first node in the list whose data matches target given the 
comparison function. The function returns the pointer to the data in the removed node.*/
template <class T>
T* LinkedList<T>::ll_remove(T* target, int (*compfunc)(T*, T*)) {
    // create node pointer at head of ll
    Node<T>* tmp = head_ptr;
    Node<T>* prev = nullptr;

    // iterate through list
    for (int i = 0; i < ll_size(); i++) {
        // Check if current node's data matches the target
        if (compfunc(tmp->data_ptr, target) == 0) {
            // Handle head node case
            if (tmp == head_ptr) {
                // set the head pointer of the ll to the next node
                head_ptr = tmp->next_ptr;
            } else {
                // Set the next pointer for the previous node
                // Have to access previous pointer instead of next one to prevent seg fault
                prev->next_ptr = tmp->next_ptr;
            }

            // Handle non-last node case
            if (tmp->next_ptr != nullptr) {
                // Set the last pointer for the next node
                tmp->next_ptr->last_ptr = prev;
            }

            T* data = tmp->data_ptr;
            delete tmp;
            --size;
            return data;
        }

        prev = tmp;
        tmp = tmp->next_ptr;
    }
    cout<<"Targer not found";
    return nullptr; // Target not found
}

/*finds the first node in the list whose data matches target given the comparison function.
The function returns the pointer to the data in the node. If the target is not in the list, then the function returns NULL.*/
template <class T>
T*  LinkedList<T>::ll_find( T *target, int (*compfunc)(T*, T*)){
    // create node pointer
    Node<T>* tmp = head_ptr;
    // iterate through list
    for (int i = 0; i<size; i++){
        // if there is a match
        if (compfunc(target, tmp)!=0){
            return tmp->data_ptr;
        }
        tmp = tmp->next_ptr;
    }
    return NULL;
}

// returns the size of the list.
template <class T>
int LinkedList<T>::ll_size() {
    return size;
}

// removes all of the nodes from the list, freeing the associated data using the given function.
template <class T>
void LinkedList<T>::ll_clear(void (*freefunc)(T *)) {

    for(int i = 0; i<size; i++){
        // create temp node at head
        Node<T>* tmp = head_ptr;
        // move the head forward and free temp
        head_ptr = tmp->next_ptr; 
        freefunc(tmp->data_ptr); 
    }
    // set the size back to 0
    size = 0;
}

// traverses the list and applies the given function to the data at each node.
template <class T>
void LinkedList<T>::ll_map(void (*mapfunc)(T *)){
    Node<T> *current=head_ptr;
	for(int i=0;i<size;i++)
	{     
		mapfunc(current->data_ptr);
		current = current->next_ptr;
	} 
}
