#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#include <string.h>

double get_cpu_time(void)
{
    return (double) clock()/CLOCKS_PER_SEC; // convert to secs
}

void row_major (int n){
    // the fast changing index is for the columns
    double array[n][n]; 
    for (int row_idx = 0; row_idx < n; ++row_idx) {

        for (int col_idx = 0; col_idx < n; ++col_idx){
           
            array[row_idx][col_idx] = 2;
            // printf("%e ", array[row_idx][col_idx]);
        }
        // printf("\n");
    }
}

void column_major (int n){
    // the fast changing index is for the rows
    double array[n][n]; 
    for (int col_idx = 0; col_idx < n; ++col_idx) {

        for (int row_idx = 0; row_idx < n; ++row_idx){
           
            array[row_idx][col_idx] = 2;
            // printf("%e ", array[row_idx][col_idx]);
        }
        // printf("\n");
    }
}

int main(int arg_count, char **argv){
    if (arg_count != 3){
        printf("> Usage: %s fast_idx size_of_matrix \n", argv[0]);
        printf("# N by N Matrix \t Runtime (secs)");
    }

    char *fast_index =  argv[1];
    double matrix_size = atof(argv[2]);
    double t0, dt;
   
    int success = 1;
    if (strcmp(fast_index, "columns") == 0){
        t0 = get_cpu_time();
        row_major(matrix_size);
        dt = get_cpu_time() - t0; 
    } else if (strcmp(fast_index, "rows") == 0) {
        t0 = get_cpu_time();
        column_major(matrix_size);
        dt = get_cpu_time() - t0; 
    } else {
        success = 0;
        printf("> Usage: %s fast_idx size_of_matrix \n", argv[0]);

    }
    
    if (success == 1){
        printf("%4.12e  %4.12e  \n", matrix_size, dt);
    }

    return 0;
}