
#include <stdio.h>
#include "./ran1.c"

// float ran1(12121212);


int main(){
    // long *seed = 218941289;
    long i = 1231313; 
    // make a for loop of # random numbers
    for (int n = 0 ; n < 10; n++){
        float random_number = ran1(&i); 
        printf("%f",random_number);
    }


    // float random_number = ran1();
    // printf("%f",random_number );
}

