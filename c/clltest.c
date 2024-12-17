/*
        Bruce Maxwell
        Fall 2012
        CS 333

        Linked list test function
 */

#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

// function that prints an integer
void printInt(void *i) {
    int *a = (int *)i;

    printf("value: %d\n", *a);
}

// function that squares an integer
void squareInt(void *i) {
    int *a = (int *)i;

    *a = *a * *a;
}

// function that compares two integers and returns 1 if they are equal
int compInt(void *i, void *j) {
    int *a = (int *)i;
    int *b = (int *)j;

    return (*a == *b);
}

// function that prints an integer
void printFloat(void *i) {
    float *a = (float *)i;

    printf("value: %f\n", *a);
}

// function that squares an integer
void squareFloat(void *i) {
    float *a = (float *)i;

    *a = *a * *a;
}

// function that compares two integers and returns 1 if they are equal
int compFloat(void *i, void *j) {
    float *a = (float *)i;
    float *b = (float *)j;

    return (*a == *b);
}

// test function for the various linked list functions
int main(int argc, char *argv[]) {
    LinkedList *l;
    int *a;
    int *target;
    int i;

    // create a list
    l = ll_create();

    // push data on the list
    for (i = 0; i < 20; i += 2) {
        a = malloc(sizeof(int));
        *a = i;

        ll_push(l, a);
    }

    // printing the list and testing map
    printf("After initialization\n");
    ll_map(l, printInt);

    ll_map(l, squareInt);

    printf("\nAfter squaring\n");
    ll_map(l, printInt);

    // testing removing data
    target = malloc(sizeof(int));
    *target = 16;
    a = ll_remove(l, target, compInt);
    if (a != NULL){
        printf("\nremoved: %d\n", *a);
        ll_map(l, printInt);}
    else
        printf("\nNo instance of %d\n", *target);
    
    *target = 11;


    a = ll_find(l, target, compInt);
    if (a != NULL)
        printf("\nFound: %d\n", *a);
    else
        printf("\nNo instance of %d\n", *target);
    
    a = ll_remove(l, target, compInt);
    if (a != NULL)
        printf("\nremoved: %d\n", *a);
    else
        printf("\nNo instance of %d\n", *target);

    printf("\nAfter removals\n");
    ll_map(l, printInt);

    // testing appending data
    ll_append(l, target);

    printf("\nAfter append\n");
    ll_map(l, printInt);

    // test clearing
    ll_clear(l, free);

    printf("\nAfter clear\n");
    ll_map(l, printInt);

    // rebuild and test append and pop
    for (i = 0; i < 5; i++) {
        a = malloc(sizeof(int));
        *a = i;
        ll_append(l, a);
    }

    printf("\nAfter appending\n");
    ll_map(l, printInt);

    a = ll_pop(l);
    printf("\npopped: %d\n", *a);
    free(a);

    a = ll_pop(l);
    printf("popped: %d\n", *a);
    free(a);

    printf("\nAfter popping\n");
    ll_map(l, printInt);

    printf("\nList size: %d\n", ll_size(l));

    // All of the tests again but using a float type instead
    // create a list
    LinkedList *l2;
    float *a2;
    float *target2;
    float i2;
    l2 = ll_create();

    // push data on the list
    for (i2 = 1.0; i2 < 20; i2 += 2) {
        a2 = malloc(sizeof(float));
        *a2 = i2;

        ll_push(l2, a2);
    }

    // printing the list and testing map
    printf("After initialization\n");
    ll_map(l2, printFloat);

    ll_map(l2, squareFloat);

    printf("\nAfter squaring\n");
    ll_map(l2, printFloat);

    // testing removing data
    target2 = malloc(sizeof(float));
    *target2 = 16;
    a2 = ll_remove(l2, target2, compFloat);
    if (a2 != NULL){
        printf("\nremoved: %f\n", *a2);
        ll_map(l, printFloat);}
    else
        printf("\nNo instance of %f\n", *target2);
    
    *target2 = 11;


    a2 = ll_find(l2, target2, compFloat);
    if (a2 != NULL)
        printf("\nFound: %f\n", *a2);
    else
        printf("\nNo instance of %f\n", *target2);
    
    a2 = ll_remove(l2, target2, compFloat);
    if (a2 != NULL)
        printf("\nremoved: %f\n", *a2);
    else
        printf("\nNo instance of %f\n", *target2);

    printf("\nAfter removals\n");
    ll_map(l2, printFloat);

    // testing appending data
    ll_append(l2, target2);

    printf("\nAfter append\n");
    ll_map(l2, printFloat);

    // test clearing
    ll_clear(l2, free);

    printf("\nAfter clear\n");
    ll_map(l2, printFloat);

    // rebuild and test append and pop
    for (i2 = 0; i2 < 5; i2++) {
        a2 = malloc(sizeof(float));
        *a2 = i2;
        ll_append(l2, a2);
    }

    printf("\nAfter appending\n");
    ll_map(l2, printInt);

    a2 = ll_pop(l2);
    printf("\npopped: %f\n", *a2);
    free(a2);

    a2 = ll_pop(l2);
    printf("popped: %f\n", *a2);
    free(a2);

    printf("\nAfter popping\n");
    ll_map(l2, printFloat);

    printf("\nList size: %d\n", ll_size(l2));

    return (0);
}