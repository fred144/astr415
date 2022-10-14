#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <nrutil.h>
// read file and 

void read_data(char *filename, float *d, int *n, int n_max){
    // n_max is the size of file 
    // file name in string
    // float * d is the vector name
    
    FILE *fp;
    fp = fopen(filename, "r") ;
    for (*n = 0; *n <= n_max && fscanf (fp, "%f", &d[*n]) != EOF; (*n)++); 
    (void) fclose(fp);

}

int main(){
    int n = 100;
    float array[n]; 
    int N[n];
    float array1[n];

    read_data("./data9_1.txt", array, N, n);
    
    read_data("./data9_2.txt", array, N, n);

    printf("> %f ", array[0]);



}

// Driver code
// int main()
// {
//     FILE* ptr;
//     char ch;
 
//     // Opening file in reading mode
//     ptr = fopen("./data9_1.txt", "r");
//     if (NULL == ptr) {
//         printf("file can't be opened \n");
//     }
//     printf("content of this file are \n");
 
//     // Printing what is written in file
//     // character by character using loop.
//     do {
//         ch = fgetc(ptr);
//         printf("%c", ch);
 
//         // Checking if character is not EOF.
//         // If it is EOF stop eading.
//     } while (ch != EOF);
 
//     // Closing the file
//     fclose(ptr);
//     return 0;
// }