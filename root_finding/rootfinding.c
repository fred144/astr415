#include <stdio.h> 
#include <math.h>  
#include "rtnewt.c"

double func(double x){
    return pow(x, 2) - 612;
}

double first_deriv(double x){
    return 2*x;
}

int main(){
    double guess = 10; 
    int iters = 10;
    double delta_x;
    for (int n = 0; n < iters; n++) {
        delta_x = guess - (func(guess) / first_deriv(guess));
        guess = delta_x;
        printf("%.25f \n", delta_x);
    }
    return 0;    


}