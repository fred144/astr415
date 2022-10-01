#include <stdio.h> 
#include <math.h> 


int main() {
    // using single floating point precision 
    // compute x^2 - 4999x + 1 = 0
    float b = -4999;
    float a = 1;
    float c = 1;
    float x_1 = (- (b) + sqrt(pow(b,2) - 4*a*c)) / 2*a;
    float x_2 = (- (b) - sqrt(pow(b,2) - 4*a*c)) / 2*a;
    float x_2_indirect = 1 /  x_1;

    printf("Single floating point precision\n");
    printf("\t Using direct computation of both roots\n");
    printf("\t first root: %4.12e  \n", x_1);
    printf("\t second root: %4.12e  \n", x_2);
   
  
    printf("\t Using larger root \n");
    printf("\t second_root: %4.12e  \n", x_2_indirect);
 

    double doub_b = -4999;
    double doub_a = 1;
    double doub_c = 1;
    double doub_x_1 = (- (doub_b) + sqrt(pow(doub_b,2) - 4*doub_a*doub_c)) / 2*doub_a;
    double doub_x_2 = (- (doub_b) - sqrt(pow(doub_b,2) - 4*doub_a*doub_c)) / 2*doub_a;
    double doub_x_2_indirect = 1 /  doub_x_1;

    printf("Double floating point precision\n");
    printf("\t Using direct computation of both roots\n");
    printf("\t first root: %4.12e  \n", doub_x_1);
    printf("\t second root: %4.12e  \n", doub_x_2);
   
  
    printf("\t Using larger root \n");
    printf("\t second_root: %4.12e  \n", doub_x_2_indirect);
 
}