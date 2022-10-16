# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "./given_scripts/nr.h"
# include "./given_scripts/nrutil.h"



void read_data(char *filename, float *d, int *n,  int vec_size, int read_col){
    // n_max is the size of file 
    // file name in string
    // float * d is the vector 
    // read col dictates which column to read.
    // idx starts from 0 
    // this is a really crappy way of hardcoding this
    // asterisk means skipping a specific column
    char s[100];
    if (read_col==0){
        char s[] = "%f %*f %*f %*f %*f %*f";
    } else if(read_col==1){ 
         char s[] = "%*f %f %*f %*f %*f %*f";
    }else if(read_col==2){ 
         char s[] = "%*f %*f %f %*f %*f %*f";
    }else if(read_col==3){ 
         char s[] = "%*f %*f %*f %f %*f %*f";
    }else if(read_col==4){ 
         char s[] = "%*f %*f %*f %*f %f %*f";
    }else if(read_col==5){ 
         char s[] = "%*f %*f %*f %*f %*f %f";
    }else {
        printf("column not valid");
    }
    
    FILE *fp;
    fp = fopen(filename, "r") ;
    for (*n = 0; *n < vec_size && fscanf (fp, s, &d[*n]) != EOF; (*n)++); 
    (void) fclose(fp);

}


float *squaredVector(float rowVector[], int array_size) {
    static float* output;
    output = (float*) malloc(array_size *sizeof(float));
    for(int i = 0; i < array_size; i++){
        output[i] = (rowVector[i]) * (rowVector[i]);
    }
    return output;
}

float sumVector(float rowVector[], int array_size) {
    float sum = 0;
    for(int i = 0; i < array_size; i++){
        sum = sum + (rowVector[i]);
    }
    return sum;
}

float *multiplyVectors(float firsVec[], float secondVec[], int array_size){
    static float* output; 
    output = (float*) malloc(array_size *sizeof(float));
     for(int i = 0; i < array_size; i++){
        output[i] = (firsVec[i]) * (secondVec[i]);
    }
    return output;
}

float *addVectors(float firsVec[], float secondVec[], int array_size){
    static float* output; 
    output = (float*) malloc(array_size *sizeof(float));
     for(int i = 0; i < array_size; i++){
        output[i] = (firsVec[i]) + (secondVec[i]);
    }
    return output;
}

float *negateVector(float rowVector[], int array_size) {
    static float* output;
    output = (float*) malloc(array_size *sizeof(float));
    for(int i = 0; i < array_size; i++){
        output[i] = -1 * (rowVector[i]);
    }
    return output;
}

int main(){
    int n = 1908;
    float x_pos[n];
    float y_pos[n];
    float z_pos[n];
    float x_vel[n];
    float y_vel[n];
    float z_vel[n];  
    
    int vec_buffer[n];
    // read in data and store them, last number is the column number
    read_data("./ps2.dat", x_pos, vec_buffer, n, 0);
    read_data("./ps2.dat", y_pos, vec_buffer, n, 1);
    read_data("./ps2.dat", z_pos, vec_buffer, n, 2);
    read_data("./ps2.dat", x_vel, vec_buffer, n, 3);
    read_data("./ps2.dat", y_vel, vec_buffer, n, 4);
    read_data("./ps2.dat", z_vel, vec_buffer, n, 5);
    
    // calculate the angular momentum of each particle and store them
    float x_ang_mom[n]; 
    float y_ang_mom[n]; 
    float z_ang_mom[n];  
    for (int row = 0; row < n; row++){
        // Vector pos_vec = {x_pos[row], y_pos[row], z_pos[row]}; 
        // Vector vel_vec = {x_vel[row], y_vel[row], z_vel[row]};
        // Vector momentum = crossProduct(pos_vec, vel_vec);
        x_ang_mom[row] = (y_pos[row] * z_vel[row]) - ( y_vel[row] *  z_pos[row]); 
        y_ang_mom[row] = - (x_pos[row] * z_vel[row]) + (x_vel[row]*  z_pos[row]) ; 
        z_ang_mom[row] = (x_pos[row]*y_vel[row]) - (x_vel[row]*y_pos[row]);
        // x_ang_mom[row] = momentum.i;
        // y_ang_mom[row] = momentum.j;
        // z_ang_mom[row] = momentum.k;
    } 
    float tot_x_mom = sumVector(x_ang_mom, n);
    float tot_y_mom = sumVector(y_ang_mom, n);
    float tot_z_mom = sumVector(z_ang_mom, n);

    printf("Total Angular Momentum Vector\n");
    printf("%f %f %f \n", tot_x_mom  ,tot_y_mom , tot_z_mom );
    printf("\n");
    // we now have the L vector

    /* 
    We are now using numerical recipes scripts, which stupidly treats the
    first index as 1. 

    */

    float **L_vec  = matrix(1,3,1,1); 
    L_vec[1][1] = tot_x_mom;
    L_vec[2][1] = tot_y_mom;
    L_vec[3][1] = tot_z_mom;
    // float **L_vec =   matrix(1,3,1,1); 
    
    // we can sequare the position vectors
    float *x_2 = squaredVector(x_pos, n);
    float *y_2 = squaredVector(y_pos, n);
    float *z_2 = squaredVector(z_pos, n);
    
    // moment of inerita tensor 
    // first row
    float I11 = sumVector(addVectors(y_2, z_2, n), n); 
    float I12 = sumVector(multiplyVectors(negateVector(x_pos,n), y_pos, n), n);
    float I13 = sumVector(multiplyVectors(negateVector(x_pos,n), z_pos, n), n);
    // second row 
    float I21 = sumVector(multiplyVectors(negateVector(y_pos,n), x_pos, n), n);
    float I22 = sumVector(addVectors(x_2, z_2, n), n); 
    float I23 = sumVector(multiplyVectors(negateVector(y_pos,n), z_pos, n), n);
    // third row
    float I31 = sumVector(multiplyVectors(negateVector(x_pos,n), z_pos, n), n);
    float I32 = sumVector(multiplyVectors(negateVector(y_pos,n), z_pos, n), n);
    float I33 = sumVector(addVectors(x_2, y_2, n), n); 
   
    // make the tensor
    float **moment_of_inertia = matrix(1,3,1,3); 
    moment_of_inertia [1][1] = I11; 
    moment_of_inertia [1][2] = I12;
    moment_of_inertia [1][3] = I13;
    moment_of_inertia [2][1] = I21; 
    moment_of_inertia [2][2] = I22;
    moment_of_inertia [2][3] = I23;
    moment_of_inertia [3][1] = I31;
    moment_of_inertia [3][2] = I32; 
    moment_of_inertia [3][3] = I33; 

    // gauss jordan, L_vec will contain the vector solution
    gaussj(moment_of_inertia, 3, L_vec, 1);
    printf("The values of the associated reduced vector is \n");
    printf("%g %g %g \n", L_vec[1][1] , L_vec[1][2], L_vec[1][3]);
   
    printf("\n");
    printf("Here is the tensor\n");
    printf("%g %g %g \n",  I11 ,  I12,  I13);
    printf("%g %g %g \n",  I21 ,  I22,  I23);
    printf("%g %g %g \n",  I31 ,  I32,  I33);
     printf("\n");
     
    float first_element_squared = pow(L_vec[1][1], 2); 
    float second_element_squared = pow(L_vec[2][1], 2); 
    float third_element_squared = pow(L_vec[3][1], 2); 
    // calculate omega
    double omega = sqrt(first_element_squared + second_element_squared + third_element_squared);
    // calculate period
    float period = (2*M_PI) / omega;
    printf("With the corresponding omega = %f s^-1 \n", omega);
    printf("We calculate a period of = %f s \n", period );
    printf("Or %f hrs \n", period/3600 );

}