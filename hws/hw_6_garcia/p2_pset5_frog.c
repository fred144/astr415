#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "./given_scripts/nr.h"
#include "./given_scripts/rk4.c"
#include "./given_scripts/nrutil.c"
#include "./given_scripts/nrutil.h"


float xaccel(float x, float y){
    return -(2 * x) / pow(2*x*x + 2*y*y + 1, 3/2);
}

float yaccel(float x, float y){
    return -(2 * y) / pow(2*x*x + 2*y*y + 1, 3/2);
}

void leapfrog(float prev_xpos, float prev_xvel, float prev_ypos, float prev_yvel,
            float *new_xpos, float *new_xvel,  float *new_ypos, float *new_yvel, 
            float step){
    float half_xvel = prev_xvel + 0.5*step*xaccel(prev_xpos, prev_ypos);
    float half_yvel = prev_yvel + 0.5*step*yaccel(prev_xpos, prev_ypos);
    *new_xpos = prev_xpos + step* half_xvel; 
    *new_ypos = prev_ypos + step* half_yvel; 
    
    // new velocity should be using the newly calculated one, not the input
    *new_yvel = half_yvel + 0.5*step*yaccel(*new_xpos, *new_ypos); 
    *new_xvel = half_xvel + 0.5*step*xaccel(*new_xpos, *new_ypos); 
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

    float rk_prev_vel, rk_prev_pos; 
    float *rk_new  = vector(1,2); 
    float *rk_old = vector(1,2); 
    
    printf("# Time \t x_position\t  y_position\t x_velocit\t y_velocity\n");
    for(float n = 1; n <= num_iter; n++){
        if (n == 1){
            printf("%3.12e \t %3.12e \t  %3.12e \t  %3.12e \t  %3.12e  \n", 
                time,  x_position,  y_position, x_velocity, y_velocity);
            
            lf_prev_xvel = x_velocity;
            lf_prev_xpos = x_position; 
            lf_prev_yvel = y_velocity;
            lf_prev_ypos = y_position; 

           
            // derivatives of position and velocity for rk4 
            // rk_old[1] = velocity;
            // rk_old[2] = -position;
           
            // rk_new[1] = position;
            // rk_new[2] = velocity;
        } 
        
        time = step_size * n; 
        
        float lf_new_xvel, lf_new_xpos;
        float lf_new_yvel, lf_new_ypos;
      
        leapfrog(lf_prev_xpos,  lf_prev_xvel, lf_prev_ypos,  lf_prev_yvel, 
                &lf_new_xpos, &lf_new_xvel, &lf_new_ypos, &lf_new_yvel, step_size);

        // rk4(rk_new, rk_old, 2, time, step_size, rk_new, coupled_first_order);
        
        printf("%3.12e \t %3.12e \t  %3.12e \t  %3.12e \t %3.12e \n", 
                time, lf_new_xpos, lf_new_ypos, lf_new_xvel, lf_new_yvel);

        lf_prev_xpos = lf_new_xpos; 
        lf_prev_xvel = lf_new_xvel; 

        lf_prev_ypos = lf_new_ypos; 
        lf_prev_yvel = lf_new_yvel; 

        rk_old[1] =  rk_new[2]; 
        rk_old[2] = - rk_new[1];

        // // euler's method
        // position =  position + step_size * velocity;
        // velocity = velocity + step_size * accel(position); 
    
    }

    return 0;
}