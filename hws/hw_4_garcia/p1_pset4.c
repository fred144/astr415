#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "./given_scripts/random_1.c"

float cum_dist(float n){
    float cumulative = 1 - pow(M_E, -pow(n,2) / 2);

    return cumulative;

}

float rayleigh(float n){
    float ray = sqrt(-2 * log(-n + 1)); 
    return ray;
}


int main(){

    FILE *fp = fopen("./p1_data.txt", "w");
    
    long i = 218941289; // seed
    int N = 1e5 ; 
    // make a for loop of # random numbers
    
    for (int n = 0 ; n < N; n++){
        float random_number = random_1(&i);
        float ray = rayleigh(random_number); 
        fprintf(fp, "%4.12e \t  %4.12e \n", random_number, ray);
    }

    fclose(fp);
    printf("See p1_data.txt\n ");
    return 0;
}

