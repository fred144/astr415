# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
#include <string.h>

int main (int arg_count, char **argv){
    char *type =  argv[1];
   
    int maxN = 21;
    if (strcmp(type , "float") == 0){
        float phi = (sqrt(5) - 1) / 2; 
        for (int n=1; n < maxN; n++){
            float phi_n_minus = 1;
            for(int i=1; i<n; i++){
                phi_n_minus =  phi_n_minus * phi;
            }

            float phi_n_plus = 1;
            for(int i=1; i<=n + 1; i++){
                phi_n_plus =  phi_n_plus * phi;
            }

             float phi_n_recursion = phi_n_minus - phi_n_plus;
            
             float phi_n = 1;
            for(int i=1; i<=n; i++){
                phi_n = phi_n * phi;
            }

            printf("%2i %4.32e %4.32e \n", n, phi_n_recursion, phi_n);
        }  
    } else if (strcmp(type, "double") == 0) {
        double phi = (sqrt(5) - 1) / 2; 
        for (int n=1; n < maxN; n++){
            double phi_n_minus = 1;
            for(int i=1; i<n; i++){
                phi_n_minus =  phi_n_minus * phi;
            }

            double phi_n_plus = 1;
            for(int i=1; i<=n + 1; i++){
                phi_n_plus =  phi_n_plus * phi;
            }

            double phi_n_recursion = phi_n_minus - phi_n_plus;
            
            double phi_n = 1;
            for(int i=1; i<=n; i++){
                phi_n = phi_n * phi;
            }
            
            printf("%2i %4.32e %4.32e \n", n, phi_n_recursion, phi_n);
        } 
    } else {
        printf("> Usage: %s type, double or float \n", argv[0]);

    }

   

    

}
