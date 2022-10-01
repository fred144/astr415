#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#include <string.h>
#include <assert.h>

double get_cpu_time(void)
{
    return (double) clock()/CLOCKS_PER_SEC; // convert to secs
}

void row_major (int n){

    // allocating array 
    double **array;
    array = (double**)malloc((n * sizeof(double*)));
    assert(array);
    for (int i=0; i<n ;i++) {
        // for a given element in a row, fill that element with a column vector
        array[i] = (double *) malloc(n*sizeof(double));
        assert(array[i]);
    }
    // the fast changing index is for the columns
    for (int row_idx = 0; row_idx < n; ++row_idx) {
        for (int col_idx = 0; col_idx < n; ++col_idx){
            // fill a zero matrix
            array[row_idx][col_idx] = 2;
            // printf("%e ", array[row_idx][col_idx]);
        }
        // printf("\n");
    }

    // free memory 
    for (int i = 0;i < n; i++)
        free((void *) array[i]);
    free((void *) array);
}

void column_major (int n){
    
    // allocating array 
    double **array;
    array = (double**)malloc((n * sizeof(double*)));
    assert(array);
    for (int i=0; i<n ;i++) {
        // for a given element in a row, fill that element with a column vector
        array[i] = (double *) malloc(n*sizeof(double));
        assert(array[i]);
    }
    // the fast changing index is for the rows
    for (int col_idx = 0; col_idx < n; ++col_idx) {

        for (int row_idx = 0; row_idx < n; ++row_idx){
            // fill a zero matrix
            array[row_idx][col_idx] = 2;
            // printf("%e ", array[row_idx][col_idx]);
        }
        // printf("\n");
    }

    // free memory 
    for (int i = 0;i < n; i++)
        free((void *) array[i]);
    free((void *) array);
}

int main(int arg_count, char **argv){
    if (arg_count != 3){
        printf("> Usage: %s major size_of_matrix \n", argv[0]);
        printf("# N by N Matrix \t Runtime (secs)");
    }

    char *major=  argv[1];
    double matrix_size = atof(argv[2]);
    double t0, dt;
   
    int success = 1;
    if (strcmp(major, "rows") == 0){
        t0 = get_cpu_time();
        row_major(matrix_size);
        dt = get_cpu_time() - t0; 
    } else if (strcmp(major, "columns") == 0) {
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