// A pointer is a variable that contains the address of a variable. 

int i,j; /* simple integer variables */
int *pi; /* pointer to an integer variable */

i = 10;  /* assign the value 10 to i */
// &i is the memory allocation of where i = 10 is stored
pi = &i; /* assign the address of i to pi */ 
// asterisk in front of the pointer is the value of the memory
// j is 10 here
j = *pi; /* assign the contents of address pi to j */

// example of using pointers

void swap(int x, int y)
  {
    // int x and int y is static
    // this is not going to work
    int temp; // temporary variable

    temp = x;
    x = y;
    y = temp;
  }

// pass the memeory locations
// input is a pointer
void swap(int *px, int *py)
  {
    int temp;
    // asterisk is  the value
    // & is the address of the memory
    temp = *px;
    *px = *py;
    *py = temp;
  }


///////////////////////
#include <stdio.h>
#include <assert.h>

void init_array(int *myarray,int nelem,int elem,int val)
{
    assert(myarray != NULL);
    assert(elem >= 0 && elem < nelem);
    myarray[elem] = val;
}

#define MAX_NELEM 15

void main(void)
{
    int myarray[MAX_NELEM];
    init_array(myarray,MAX_NELEM,0,12);
}


// another way to do it dynamically
// point to a double 
// 10 elements for an array
// mallic is a function it return a double
// size of means the size of the memory for one element. 
// name of array is a pointer to the first element 
// array [10] 
// array = &array[0]


double *x = (double *) malloc(10*sizeof(double));