#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "./given_scripts/nr.h"
#include "./given_scripts/rk4.c"
#include "./given_scripts/nrutil.c"
#include "./given_scripts/nrutil.h"



void system(float time, float position[], float output_vec[]){
    // time is a a float containing the time step
    // position is a 2-element vector with the first index having the velocit
    // and the second having the acceleration. 
    // you feed this into runge kuta 4. 
    
    output_vec[1] = position[2]; 
    output_vec[2] = -position[1];
}

int main(){
    

    return 0;
}