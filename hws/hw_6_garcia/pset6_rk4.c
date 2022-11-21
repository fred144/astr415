#include <stdio.h>
#include <math.h>
#include <string.h>
#include "./given_scripts/nr.h"
#include "./given_scripts/rk4.c"
#include "./given_scripts/nrutil.c"
#include "./given_scripts/nrutil.h"

int readmatrix(size_t rows, size_t cols, float (*a)[cols], const char* filename)
{

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

void flattened_grav_deriv(float t, float init[], float val_derivs[], int N_particles ){
    // initi is a flattened array
    // the first three columns are (x,y,z), followed by the velocities for each component
    // each row of val derivs is the corresponding derivatives; i.e. (vx,vy,vz,ax,ay,az)
    float G = 1.0; 
    int params = 6;
    // asssuming mass vector is uniform
     
    for (int primary_p = 0;  primary_p < params*N_particles;  primary_p = primary_p*6){
        // loop over the particles, finding the acceleartions by considering all others as secondaries.
        // p_ si for primary
        float p_pos_x = init[primary_p + 1];
        float p_pos_y = init[primary_p + 2];
        float p_pos_z = init[primary_p + 3];

        float p_vel_x = init[primary_p + 4];
        float p_vel_y = init[primary_p + 5];
        float p_vel_z = init[primary_p + 6];
        // store the velocities to the deriv array
        val_derivs[primary_p + 1] = p_vel_x;
        val_derivs[primary_p + 2] = p_vel_y;
        val_derivs[primary_p + 3]= p_vel_z;

        float p_acc_x = 0;
        float p_acc_y = 0;
        float p_acc_z = 0;
        
        for (int secondary_p = 0; secondary_p < params*N_particles; primary_p = primary_p*6){ 
            // calculate each of the acceleration contributed by the other particles
            if (primary_p != secondary_p){
                // printf("primary particle %d \n", primary_p);
                // printf("primary particle %d \n", primary_p);
                // get pertinent info about the secondary particle
                // float s_mass = mass_vec[secondary_p];
                float s_mass = 1.0;

                float s_pos_x = init[secondary_p + 1];
                float s_pos_y = init[secondary_p + 2];
                float s_pos_z = init[secondary_p + 3];
                
                // calculate the difference in position between each component 
                float x_diff = p_pos_x-s_pos_x;
                float y_diff = p_pos_y-s_pos_y;
                float z_diff = p_pos_z-s_pos_z;

                float mag_diff = pow(pow(x_diff, 2) + pow(y_diff, 2) + pow(z_diff, 2) , 0.5);

                p_acc_x = (G * s_mass * x_diff) / pow(mag_diff,3);
                p_acc_y = (G * s_mass * y_diff) / pow(mag_diff,3);
                p_acc_z = (G * s_mass * z_diff) / pow(mag_diff,3);

                p_acc_x += p_acc_x;
                p_acc_y += p_acc_y;
                p_acc_z += p_acc_z;
            }

        }
        val_derivs[primary_p] = - p_acc_x;
        val_derivs[primary_p] = - p_acc_y;
        val_derivs[primary_p] = - p_acc_z;

    } 
}




int main(int arg_count, char **argv){
    if (arg_count != 6){
        printf("> Usage: %s softening timestep end_time out_freq init_file \n", argv[0]);
         printf("out_freq means output every other N");
        printf("Output of run will be placed in ./frog_data, be sure that the directory is clean before running");
        return 1;
    }
    // float eccentricity =  atof(argv[1]) ;  
    // float initial_v = pow(2*(1-eccentricity), 0.5);
    int Npar= 2;
    int params = 6;
    // values take the form
    //  $x_N$, $y_N$, $z_N$, $\dot{x_N}$, $\dot{x_N}$, $\dot{x_N}$ 
    //argv[6]
    float *y=vector(1,N);
    
    float data[2][7];
    float part_mass[2];
    
    float *vals = vector(1 , Npar*params);
    float *val_derivs = vector(1 , Npar*params);
    
    readmatrix(2, 7, data, argv[5]);


    vals[1] = data[0][1];
    vals[2] = data[0][2];
    vals[3] = data[0][3];
    vals[4] = data[0][4];
    vals[5] = data[0][5];
    vals[6] = data[0][6];
    vals[7] = data[1][1];
    vals[8] = data[1][2];
    vals[9] = data[1][3];
    vals[10] =  data[1][4];
    vals[11] =  data[1][5];
    vals[12] =  data[1][6];
    // for(int i = 0; i < 2; ++i){
    //     for(int j = 0; j < 7; ++j)
    //         printf(" %3.10e ",  data[i][j]);
    //     puts("");
    // }


   

    // for(int i = 0; i < 2; ++i){
    //         printf(" %3.10e ",  part_mass[i]);
    // }

    for (int row =0; row< Npar; row++){
        for (int col =0; col < 6; col++)
            vals[row][col] = data[row][col + 1];
    }

    // for (int col=0; col<6; col++){
    //     read_data(argv[5], vals[][col], vec_buffer,  Npar, col);
    // }

    // float vals[][6]={
    //     mass,
    // };

    // float vals[][6]={
    //     -0.5, 0.0, 0.0, 0.0, -initial_v/2.0, 0.0, 
    //     0.5, 0.0, 0.0, 0.0, initial_v/2.0, 0.0
    //     };
    
   
    // float part_mass[] = {1., 1.}; 
    int output_freq = atoi(argv[4]);
	float end_time = atof(argv[3]);
	float step = atof(argv[2]) ;
	int Nsteps = end_time/step;

	float time = 0.0;
	// y[1]=1.;
	// y[2]=0.; 

    // naming scheme 
    char filename[200];
    sprintf(filename, "./rk4_data/out_%04d.txt", 0);
    
    // print the intial conditions
    printf("# \t time, \t xpos, \t ypos, \t zpos, \t xvel, \t yvel, \t zvel\n");
    for (int i=0; i<Npar; i++){
        printf(
            "%3.10e %3.10e %3.10e %3.10e %3.10e %3.10e %3.10e\n",
              time, vals[i][0], vals[i][1], vals[i][2], vals[i][3], vals[i][4], vals[i][5]
             );	
    }
    // print intial conditions to file 000
    FILE *fp;
    fp = fopen(filename,"w");
    printf("# \t time, \t xpos, \t ypos, \t zpos, \t xvel, \t yvel, \t zvel\n");
    fprintf(fp, "# \t time, \t xpos, \t ypos, \t zpos, \t xvel, \t yvel, \t zvel\n");
    for (int i=0; i<Npar; i++){
        fprintf(fp, "%3.10e %3.10e %3.10e %3.10e %3.10e %3.10e %3.10e\n",
              time, vals[i][0], vals[i][1], vals[i][2], vals[i][3], vals[i][4], vals[i][5]
             );	
    }
    fclose(fp );

    printf("----------------------- \n");
    // go through each particles and compute the position based on forces of other particles.
    
	for(int n=1; n<=Nsteps; n++){
        grav_deriv(time, vals, val_derivs, part_mass, Npar);
        
        // for (int i=0; i<Npar; i++){
        //     printf("derivs: %3.10e %3.10e %3.10e %3.10e %3.10e %3.10e %3.10e\n", 
        //     time, val_derivs[i][0], val_derivs[i][1], val_derivs[i][2], val_derivs[i][3], val_derivs[i][4], val_derivs[i][5]
        //         );	}
        
        //  val has x, y, z, vx, vy, vz
        //  val derivs has vx, vy, vz, ax, ay, az
        
      

        time = n * step;
       
        
        sprintf(filename, "./frog_data/out_%04d.txt", n);
        printf("%d",n %  output_freq);
        if (n %  output_freq == 0){
            printf("\t time, \t xpos, \t ypos, \t zpos, \t xvel, \t yvel, \t zvel\n");
            FILE *fp;
            fp = fopen(filename,"w");
            fprintf(fp, "# \t time, \t xpos, \t ypos, \t zpos, \t xvel, \t yvel, \t zvel\n");
            for (int i=0; i<Npar; i++){
                printf("%3.10e %3.10e %3.10e %3.10e %3.10e %3.10e %3.10e\n", 
                time, vals[i][0], vals[i][1], vals[i][2], vals[i][3], vals[i][4], vals[i][5]
                    );	
                fprintf(fp, "%3.10e %3.10e %3.10e %3.10e %3.10e %3.10e %3.10e\n", 
                time,  vals[i][0], vals[i][1], vals[i][2], vals[i][3], vals[i][4], vals[i][5]
                    );	
            }
            fclose(fp);
            printf("----------------------- \n");
        }
	}
	return 1;
	}
	

