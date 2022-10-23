#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "./given_scripts/random_1.c"


int main(){
    long i = 218941289; // seed
    // loop through for 10 to 1e7
    FILE *fp = fopen("./p2_data.txt", "w");
    for (float sample_size=1; sample_size <=7; sample_size++){
        float N = pow(10, sample_size); // number of throws
        float mass_sum = 0.0;
        float density_squared = 0.0;
        // let's take the sample box region 
        // -3 to 3 in z
        // -1 to 3 in y 
        //  0 to 3 in x
        float sample_volume = 6.0 * 4.0 * 3; 
        for (int throw=0; throw<N; throw++){
            // start throwing in each dimension
            // take into account that random_1 is [0,1]
            float random_x = 3.0*random_1(&i); // [0,3]
            float random_y = (-1.0)+4*random_1(&i); //[-1,3]
            float random_z = (-3.0)+6*random_1(&i);  //[-3,3]
            // after generating these numbers which dictate the bound,
            // we need to still make sure that it is within the object 
            float distance_from_center = random_x*random_x + random_y*random_y + random_z*random_z;
            if (distance_from_center < 9){
                float density = 1 + (random_x*random_x) + 3*(random_y+random_z)*(random_y+random_z); 
                mass_sum += density; 
                density_squared += density*density; 
                // printf("%4.12e\n",mass_sum);


            } 

        } 
        float total_mass = sample_volume * (mass_sum/N);
        float mass_err = sample_volume * sqrt( ( (density_squared/N) - (mass_sum/N)*(mass_sum/N) ) / N); 
        fprintf(fp, "%.12e \t %4.12e \t %4.12e\n", N, total_mass, mass_err);
        
    }

    fclose(fp);
    printf("See p2_data.txt\n ");
    return 0;

}