#include <stdio.h>
#include <math.h>
#include <string.h>
#include "./given_scripts/nr.h"
#include "./given_scripts/rk4.c"
#include "./given_scripts/nrutil.c"
#include "./given_scripts/nrutil.h"

float readmatrix(size_t rows, size_t cols, float (*a)[cols], const char* filename){
    // read 2d array from text file 
    FILE *pf;
    pf = fopen (filename, "r");
    if (pf == NULL)
        return 0;
    for(size_t i = 0; i < rows; ++i)
    {
        for(size_t j = 0; j < cols; ++j)
            fscanf(pf, "%f", a[i] + j);
    }
    fclose (pf); 
    return 1; 
}

void flattened_grav_deriv(float t, float vals[], float val_derivs[] ){
    // initi is a flattened array contianing intial values
    // the first three columns are (x,y,z), followed by the velocities for each component
    // each row of val derivs is the corresponding derivatives; i.e. (vx,vy,vz,ax,ay,az)
    float G = 1.0; 
    int params = 6;
    int N_particles = 2;
    // asssuming mass vector is uniform
    float s_mass;
    float x_diff, y_diff, z_diff; 
    float mag_diff_cubed;

    for (int primary_p = 0;  primary_p < N_particles ;  primary_p++){
        // loop over the particles, finding the acceleartions by considering all others as secondaries.
        // store the velocities to the deriv array, flattened
        val_derivs[primary_p*params + 1] = vals[primary_p*params + 4];
        val_derivs[primary_p*params + 2] = vals[primary_p*params + 5];
        val_derivs[primary_p*params + 3] = vals[primary_p*params + 6];

        val_derivs[primary_p*params + 4]  = 0.0;
        val_derivs[primary_p*params + 5]  = 0.0;
        val_derivs[primary_p*params + 6]  = 0.0;
        
        for (int secondary_p = 0; secondary_p < N_particles; secondary_p++){ 
            // calculate each of the acceleration contributed by the other particles
            if (primary_p != secondary_p){
                float s_mass = 1.0;
                // calculate the difference in position between each component 
                x_diff = vals[primary_p*params + 1] - vals[secondary_p*params + 1];
                y_diff = vals[primary_p*params + 2] - vals[secondary_p*params + 2];
                z_diff = vals[primary_p*params + 3] - vals[secondary_p*params + 3];
                mag_diff_cubed = powf(x_diff*x_diff  + y_diff*y_diff + z_diff*z_diff, 1.5);
                val_derivs[primary_p*params + 4] += -(G * s_mass * x_diff) / mag_diff_cubed;
                val_derivs[primary_p*params + 5] += -(G * s_mass * y_diff) / mag_diff_cubed;
                val_derivs[primary_p*params + 6] += -(G * s_mass * z_diff) / mag_diff_cubed;
        
            }
            
        }
    } 
}


int main(int arg_count, char **argv){
    if (arg_count != 6){
        printf("> Usage: %s softening timestep end_time out_freq init_file \n", argv[0]);
         printf("out_freq means output every other N");
        printf("Output of run will be placed in ./frog_data, be sure that the directory is clean before running");
        return 1;
    }
    // float eccentricity =  0.5 ;  
   
    int Npar= 2;
    int Nparams = 6;
    
    float data[2][7];
    float part_mass[2];
    
    float *vals = vector(1 , Npar*Nparams);
    float *val_derivs = vector(1 , Npar*Nparams);
    
    int output_freq = atoi(argv[4]);
	float end_time = atof(argv[3]);
	float step = atof(argv[2]) ;
    readmatrix(2, 7, data, argv[5]);
    int Nsteps = end_time/step;

     // int output_freq = 1;
	// float end_time = 5;
	// float step = 0.05;

    // readmatrix(2, 7, data, "./e_05_init.txt");

    // init values for the first particle
    vals[1] = data[0][1];
    vals[2] = data[0][2];
    vals[3] = data[0][3];
    vals[4] = data[0][4];
    vals[5] = data[0][5];
    vals[6] = data[0][6];

    // init values for the second particle
    vals[7] = data[1][1];
    vals[8] = data[1][2];
    vals[9] = data[1][3];
    vals[10] =  data[1][4];
    vals[11] =  data[1][5];
    vals[12] =  data[1][6];

    
    // float initial_v = pow(2*(1-eccentricity), 0.5);
    // vals[1] = -0.5;
    // vals[2] = 0.0;
    // vals[3] = 0.0;
    // vals[4] = 0.0;
    // vals[5] = -initial_v/2.0;
    // vals[6] = 0.0;

    // // init values for the second particle
    // vals[7] = 0.5;
    // vals[8] = 0.0;
    // vals[9] = 0.0;
    // vals[10] =  0.0;
    // vals[11] =  initial_v/2.0;
    // vals[12] =  0.0;    
   




    // naming scheme 
    char filename[ 200];
    sprintf(filename, "./data_rk4/rk4_out_%04d.txt", 0);
    
    float time = 0.0;
    // print intial conditions to file 000
    FILE *fp;
    fp = fopen(filename,"w");
    fprintf(fp, "# \t time, \t xpos, \t ypos, \t zpos, \t xvel, \t yvel, \t zvel\n");
    for (int i=0; i<Npar; i++){
        printf(
            "%3.10e %3.10e %3.10e %3.10e %3.10e %3.10e %3.10e\n",
              time, 
              vals[i*Nparams + 1], 
              vals[i*Nparams + 2], 
              vals[i*Nparams + 3], 
              vals[i*Nparams + 4], 
              vals[i*Nparams + 5], 
              vals[i*Nparams + 6]
             );	
        fprintf(fp, "%3.10e %3.10e %3.10e %3.10e %3.10e %3.10e %3.10e\n",
                time, 
                vals[i*Nparams + 1], 
                vals[i*Nparams + 2], 
                vals[i*Nparams + 3], 
                vals[i*Nparams + 4], 
                vals[i*Nparams + 5], 
                vals[i*Nparams + 6]
             );	
    }
    fclose(fp);

    printf("----------------------- \n");
    // go through each particles and compute the position based on forces of other particles.
    
	for(int n=1; n<=Nsteps; n++){
        flattened_grav_deriv(time, vals, val_derivs);
        rk4(vals, val_derivs, Npar*Nparams, time, step, vals, *flattened_grav_deriv);

        time = n * step;
       
        // make the filename for this snapshot 
        sprintf(filename, "./data_rk4/rk4_out_%04d.txt", n);
        printf("%d", n % output_freq);

        if (n % output_freq == 0){
            printf("\t time, \t xpos, \t ypos, \t zpos, \t xvel, \t yvel, \t zvel\n");
            FILE *fp;
            fp = fopen(filename,"w");
            fprintf(fp, "# \t time, \t xpos, \t ypos, \t zpos, \t xvel, \t yvel, \t zvel\n");
            for (int i=0; i<Npar; i++){
                printf("%3.10e %3.10e %3.10e %3.10e %3.10e %3.10e %3.10e\n", 
                    time, 
                    vals[i*Nparams + 1], 
                    vals[i*Nparams + 2], 
                    vals[i*Nparams + 3], 
                    vals[i*Nparams + 4], 
                    vals[i*Nparams + 5], 
                    vals[i*Nparams + 6]
                    );	
                fprintf(fp, "%3.10e %3.10e %3.10e %3.10e %3.10e %3.10e %3.10e\n", 
                    time, 
                    vals[i*Nparams + 1], 
                    vals[i*Nparams + 2], 
                    vals[i*Nparams + 3], 
                    vals[i*Nparams + 4], 
                    vals[i*Nparams + 5], 
                    vals[i*Nparams + 6]
                    );	
            }
            fclose(fp);
            printf("----------------------- \n");
        }
	}


	return 1;
}
	

