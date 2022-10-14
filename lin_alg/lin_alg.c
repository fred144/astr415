#include <stdio.h>
#include <math.h>
#include "./gaussj.c"
#include "./nr.h"
#include "./nrutil.h" 

int main(){
    float **a = matrix(1,3,1,3); 
    float **b = matrix(1,3,1,1);
    float *w = vector(1,3); 

    
    a[1][1] = -3; 
    a[1][2] = 2;
    a[1][3] = -5;
    a[2][1] = 2; 
    a[2][2] = -3;
    a[2][3] = 4;
    a[3][1] = 1;
    a[3][2] = 1; 
    a[3][3] = 1; 

    b[1][1] = -14;
    b[2][1] = 10;
    b[3][1] = 4.0; 
    svdcmp(a, 3, 1, w, b);
    // gaussj(a, 3, b, 1);
    printf("%g \n", b[1][1]);
    printf("%g \n ", b[1][2]);
    printf("%g \n", b[1][3]);

    printf("%g \n", w[1][3]);
    printf("%g \n", w[1][3]);
    // single variable decomposition

}
