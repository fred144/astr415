#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "./given_scripts/nr.h"
#include "./given_scripts/rk4.c"
#include "./given_scripts/nrutil.c"
#include "./given_scripts/nrutil.h"



void coupled_first_order(float time, float position[], float output_vec[]){
    // time is a a float containing the time step
    // position is a 2-element vector with the first index having the velocit
    // and the second having the acceleration. 
    // you feed this into runge kuta 4. 
    
    output_vec[1] = position[2]; // dx/dt 
    output_vec[2] = -position[1]; // dv/dt
}

float accel( float position){
    return -position;
}

float vel(float velocity){
    return velocity;
}

void euler(float prev_pos, float prev_vel, float *new_pos, float *new_vel, float step){
    *new_pos = prev_pos + step * prev_vel; // note, can change this depending on the system
    // *new_vel = prev_vel + step * +  accel(*new_pos); // note, can change this depending on the system
    *new_vel = prev_vel + step * +  accel(prev_pos); 
}

void leapfrog(float prev_pos, float prev_vel, float *new_pos, float *new_vel, float step){
    float half_vel = prev_vel + 0.5*step*accel(prev_pos);
    *new_pos = prev_pos + step* half_vel; 
    *new_vel = half_vel + 0.5*step*accel(*new_pos); 
}

int main(int arg_count, char **argv){
    if (arg_count != 2){
        printf("> Usage: %s step size \n", argv[0]);
    }
    float step_size = atof(argv[1]);

    float end_time = 15; 
    // float step_size = 1; 
    float num_iter = end_time / step_size; 
    // intial values
    float position = 0; // m 
    float velocity = 1; // m/s
    float time = 0;

    float eu_prev_vel, eu_prev_pos; 
    float lf_prev_vel, lf_prev_pos; 
    float rk_prev_vel, rk_prev_pos; 
    float *rk_new  = vector(1,2); 
    float *rk_old = vector(1,2); 
    
    printf("# Time \t Euler Position \t Leap Position  \t RK4 Position \n");
    for(float n = 1; n <= num_iter; n++){
        if (n == 1){
            printf("%3.12e \t %3.12e \t  %3.12e \t  %3.12e \n", time, position, position, position);
            eu_prev_vel = velocity;
            eu_prev_pos = position; 
            lf_prev_vel = velocity;
            lf_prev_pos = position; 
            // derivatives of position and velocity for rk4 
            rk_old[1] = velocity;
            rk_old[2] = -position;
           
            rk_new[1] = position;
            rk_new[2] = velocity;
        } 
        
        time = step_size * n; 
        float eu_new_vel, eu_new_pos;
        float lf_new_vel, lf_new_pos;
        // float rk_new_vel, rk_new_pos;

        euler(eu_prev_pos , eu_prev_vel, &eu_new_pos, &eu_new_vel, step_size);
        leapfrog(lf_prev_pos,  lf_prev_vel, &lf_new_pos, &lf_new_vel, step_size);
        rk4(rk_new, rk_old, 2, time, step_size, rk_new, coupled_first_order);
        
        printf("%3.12e \t %3.12e \t  %3.12e \t  %3.12e \n", time, eu_new_pos, lf_new_pos, rk_new[1]);

        eu_prev_pos = eu_new_pos; 
        eu_prev_vel = eu_new_vel; 

        lf_prev_pos = lf_new_pos; 
        lf_prev_vel = lf_new_vel; 

        rk_old[1] =  rk_new[2]; 
        rk_old[2] = - rk_new[1];

        // // euler's method
        // position =  position + step_size * velocity;
        // velocity = velocity + step_size * accel(position); 
    
    }

    return 0;
}