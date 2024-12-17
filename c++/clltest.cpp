/**
 * Derek Hessinger
 * Prof. Ying Li
 * CS 333
 * 11/10/24
 * 
 * Test file for linked list in c++
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#include "linkedlist.hpp"
#include "linkedlist.cpp"

// function that prints an integer
void printInt(int *i) {
    cout<<"value: "<<*i<< "\n";
}

// function that squares an integer
void squareInt(int *i) {
    *i = *i * *i;
}

// function that compares two integers and returns 1 if they are equal
int compInt(int *i, int *j) {

    return (*i == *j);
}

// function that prints an integer
void printFloat(float *i) {
    cout<< "value: "<<*i<<"\n";
}

// function that squares an integer
void squareFloat(float *i) {
    *i = *i * *i;
}

// function that compares two integers and returns 1 if they are equal
int compFloat(float *i, float *j) {
    return (*i == *j);
}

// frees the given int
void freeInt(int *i){
	free(i);
}

int main(int argc, char *argv[]) {
	LinkedList<int> l;
	int *a;
	int i;


	
	// push data on the list
	for(i=0;i<20;i+=2) {
		a=(int *)malloc(sizeof(int));
        *a=i;
		l.ll_push(a);
		
	}

	// printing the list and testing map
	cout<<"After initialization\n";
	l.ll_map(printInt);

	l.ll_map(squareInt);

	cout<<"\nAfter squaring\n";
	l.ll_map(printInt);

	
	int *ptr;
	
	// testing removing data
    int *target = (int*)malloc(sizeof(int));
	
	*target = 16;

	a = (int *)l.ll_remove(target, compInt);

	if(a != NULL){
        ptr = (int *) a;
		cout<<"\nremoved: "<< *ptr;
		cout<<" \n ";
    }
	else{
        ptr = (int *) a;
		cout<<"\nNo instance of "<< *ptr;
		cout<<" \n ";
    }
	*target = 11;
	a = l.ll_remove(target, compInt);
	if(a != NULL){
        ptr = a;
		cout<<"\nremoved: "<< *ptr;
		cout<<" \n ";
    }
	else{
        ptr = target;
	    cout<<"\nNo instance of "<< *ptr;
	    cout<<" \n ";
    }
	cout<<"\nAfter removals\n";
	l.ll_map(printInt);

	// testing appending data
	l.ll_append(target);

	cout<<"\nAfter append\n";
	l.ll_map(printInt);

	// test clearing
	l.ll_clear(freeInt);

	cout<<"\nAfter clear\n";
	l.ll_map(printInt);

	// rebuild and test append and pop
	for(i=0;i<5;i++) {
		a=(int *)malloc(sizeof(int));
        *a=i;
		l.ll_append(a);
	}

	cout<<"\nAfter appending\n";
	l.ll_map(printInt);

	a = (int *)l.ll_pop();
    ptr = (int *)a;
	cout<<"\npopped: "<< *ptr;
	cout<<" \n ";
	free(ptr);

	a = (int *)l.ll_pop();
    ptr = (int*)a;
	cout<<"popped: "<< *ptr;
	cout<<" \n ";
	free(ptr);

	cout<<"\nAfter popping\n";
	l.ll_map(printInt);

	cout<<"\nList size: \n"<< l.ll_size();
	cout<<" \n ";


	return(0);
}