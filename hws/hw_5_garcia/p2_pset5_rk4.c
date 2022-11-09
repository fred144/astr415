#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "./given_scripts/nr.h"
#include "./given_scripts/rk4.c"
#include "./given_scripts/nrutil.c"
#include "./given_scripts/nrutil.h"

void coupled_first_order(float time, float input_vec[], float output_vec[]){
    // time is a a float containing the time step
    // input_vec is a 2-element vector with the first index having the velocit
    // and the second having the acceleration. 
    // you feed this into runge kuta 4. 
    
    // input vector has the format [x, vx, y, vy]
    // input vector has the index  [1, 2, 3, 4]
    
    // dx/dt 
    output_vec[1] = input_vec[2]; 
    
    // dv_x/dt
    output_vec[2] = - (2 * input_vec[1]) / pow(2*input_vec[1]* input_vec[1] + 2*input_vec[3]*input_vec[3] + 1, 3/2);

    // dy/dt 
    output_vec[3] = input_vec[4];  

    // dv_y/dt
    output_vec[4] = - (2 * input_vec[3]) / pow(2*input_vec[1]* input_vec[1] + 2*input_vec[3]*input_vec[3] + 1, 3/2);

}

float xaccel(float x, float y){
    return -(2 * x) / pow(2*x*x + 2*y*y + 1, 3/2);
}

float yaccel(float x, float y){
    return -(2 * y) / pow(2*x*x + 2*y*y + 1, 3/2);
}


int main(int arg_count, char **argv){
    if (arg_count != 2){
        printf("> Usage: %s step size \n", argv[0]);
    }
    float step_size = atof(argv[1]);

    float end_time = 100; 
    // float step_size = 1; 
    float num_iter = end_time / step_size; 
    // intial values
    float x_position = 1; 
    float x_velocity = 0; 
    float y_position = 0; 
    float y_velocity = 0.1; 
    float time = 0;

   
    float lf_prev_xvel, lf_prev_xpos, lf_prev_yvel, lf_prev_ypos; 

   
    float *rk_new  = vector(1,4); 
    float *rk_old = vector(1,4); 
    
     printf("# Time \t x_position\t  y_position\t x_velocit\t y_velocity\n");
    for(float n = 1; n <= num_iter; n++){
        if (n == 1){
            printf("%3.12e \t %3.12e \t  %3.12e \t  %3.12e \t  %3.12e  \n", 
                time,  x_position,  y_position, x_velocity, y_velocity);
            
         

            // input vector has the format [x, vx, y, vy]
            
            // derivatives of position and velocity for rk4 
            rk_old[1] = x_velocity;
            rk_old[2] = xaccel(x_position, y_position);
            rk_old[3] = y_velocity;
            rk_old[4] = yaccel(x_position, y_position);

            // the output vector (stored in rk_new) has the format [x, vx, y, vy]
            rk_new[1] = x_position;
            rk_new[2] = x_velocity;
            rk_new[3] = y_position;
            rk_new[4] = y_velocity;
        } 
        
        time = step_size * n; 
        
        rk4(rk_new, rk_old, 4, time, step_size, rk_new, coupled_first_order);
        // the output vector (stored in rk_new) has the format [x, vx, y, vy]
        printf("%3.12e \t %3.12e \t  %3.12e \t  %3.12e \t %3.12e \n", 
                time, rk_new[1], rk_new[3], rk_new[2], rk_new[4]);

        // update the derivatives
        rk_old[1] =  rk_new[2];  // x vel 
        rk_old[2] = xaccel(rk_new[1], rk_new[3]); // x accel
        rk_old[3] =  rk_new[4]; // y vel
        rk_old[4] = yaccel(rk_new[1], rk_new[3]); // y accel

    
    }

    return 0;
}