/**
 * Given an array of random integers, sort it in such a way that the even 
 * numbers appear first and the odd numbers appear later. The even numbers 
 * should be sorted in descending order and the odd numbers should be sorted 
 * in ascending order.
 *
 * Ying Li
 * 08/02/2016
 * 
 * edited by Derek Hessinger
 * 10/21/24
 * 
 * gcc -o quicksort quicksort.c
 * ./quicksort
 */

#include <stdio.h>
#include <stdlib.h>

/* the comparator funciton used in qsort */
int comparator (const void *p, const void *q) {
	// Your code here
	// cast the void pointers to int pointers
    int p_int = *(const int *)p;
    int q_int = *(const int *)q;
	// If both numbers are even, sort in descending order
    if (p_int % 2 == 0 && q_int % 2 == 0) {
        return q_int - p_int;  // Descending order for even numbers
    }
    // If both numbers are odd, sort in ascending order
    else if (p_int % 2 == 1 && q_int % 2 == 1) {
        return p_int - q_int;  // Ascending order for odd numbers
    }
    // If p is even and q is odd, p should come first
    else if (p_int % 2 == 0 && q_int % 2 == 1) {
        return -1;  // p comes before q (even before odd)
    }
    // If p is odd and q is even, q should come first
    else {
        return 1;  // q comes before p (even before odd)
    }
}

int main (int argc, char **argv) {
	int ary[] = {10, 11, 1, 8, 9, 0, 13, 4, 2, 7, 6, 3, 5, 12};
	
	int size = sizeof(ary) / sizeof(int);
	
	qsort((void *) ary, size, sizeof(int), comparator);
	
	printf("The sorted array is: ");
	for (int i = 0; i < size; i++) {
		printf("%d ", ary[i]);
	}
	printf("\n");
	
	return 0;
}