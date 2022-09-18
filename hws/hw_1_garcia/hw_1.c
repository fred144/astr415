#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

double get_cpu_time(void)
{
    return (double) clock()/CLOCKS_PER_SEC; // convert to secs
}

int int_add_five(float n_loops){
    int val = 0; // initial val
    for (int i = 1; i <= n_loops; ++i){
        val =  val + 5;
    }
    return val;
}

int int_sub_five(float n_loops){
    int val = 0; // initial val
    for (int i = 1; i <= n_loops; ++i){
        val =  val - 5;
    }
    return val;
}

int int_mul_one(float n_loops){
    int val = 0; // initial val
    for (int i = 1; i <= n_loops; ++i){
        val =  val * 1;
    }
    return val;
}

int int_div_one(float n_loops){
    int val = 0; // initial val
    for (int i = 1; i <= n_loops; ++i){
        val =  val / 1;
    }
    return val;
}

double doub_add_five(float n_loops){
    double val = 0.0; // initial val
    for (int i = 1; i <= n_loops; ++i){
        val =  val + 5;
    }
    return val;
}

double doub_sub_five(float n_loops){
    double val = 0.0; // initial val
    for (int i = 1; i <= n_loops; ++i){
        val =  val - 5;
    }
    return val;
}


double doub_mul_one(float n_loops){
    double val = 1.0; // initial val
    for (int i = 1; i <= n_loops; ++i){
        val =  val * 1.000001;
    }
    return val;
}

double doub_div_one(float n_loops){
    double val = 1.0; // initial val
    for (int i = 1; i <= n_loops; ++i){
        val =  val / 1.000001;
    }
    return val;
}

double doub_sqrt(float n_loops){
    double val = 1.1; // initial val
    for (int i = 1; i <= n_loops; ++i){
        val =  sqrt(val); 
    }
    return val;
}

double doub_pow(float n_loops){
    double val = 1.1; // initial val
    for (int i = 1; i <= n_loops; ++i){
        val =  pow(val, 0.5); 
    }
    return val;
}


int main(int arg_count, char **argv){
    // example usage 
    // hw_1 doub add 1e5
    // to compile
    // gcc -O2 -o executable_name myprog.c -lm 
    if (arg_count != 4){
        printf("> Usage: %s type operation num_iterations \n", argv[0]);
        printf(">> prints the number of iterstions, time of execution, the final value \n");
    }
    char *type =  argv[1];
    char *operation = argv[2];
    double num_iterations = atof(argv[3]);
    float final_val; 
    double t0, dt;
    int success = 1;
    t0 = get_cpu_time();         // get initial value
    // printf("%s \n",operation ); 
    // printf("%s \n", type ); 
    if (strcmp(operation, "add") == 0  ){
        if (strcmp(type, "int") == 0){
            final_val = int_add_five(num_iterations);
        } else if (strcmp(type, "double" ) == 0){
            final_val = doub_add_five(num_iterations);
        } else {
            printf("Operation not suppoerted.");
        }
    } else if (strcmp(operation, "subtract") == 0  ){
        if (strcmp(type, "int") == 0){
            final_val = int_sub_five(num_iterations);
        } else if (strcmp(type, "double" ) == 0){
            final_val = doub_sub_five(num_iterations);
        } else {
            printf("Operation not suppoerted.");
        }
    } else if (strcmp(operation,"multiply") == 0){
        if (strcmp(type, "int") == 0){
            final_val = int_mul_one(num_iterations);
        } else if (strcmp(type, "double") == 0 ){
            final_val = doub_mul_one(num_iterations);
        } else {
            printf("Operation not suppoerted.");
        }
    } else if (strcmp(operation, "divide") == 0){
        if (type == "int"){
            final_val = int_div_one(num_iterations);
        } else if (strcmp(type, "double") == 0 ){
            final_val = doub_div_one(num_iterations);
        } else {
            printf("Operation not suppoerted.");
        }
    } else if (strcmp(operation, "sqrt") == 0){
        final_val = doub_sqrt(num_iterations);
    } else if (strcmp(operation, "pow") == 0){
        final_val = doub_pow(num_iterations);
    } else  {
        printf("Available types: int, double \n");
        printf("Available operations: add, subtract, multiply, divide, sqrt, pow \n");
        success = 0;
    }

    dt = get_cpu_time() - t0;    /* difference to get execution time */
    // prints the number of iterations, time of execution, the final value
    if (success == 1){
        printf("%2.12e  %2.12e  %2.12e \n", num_iterations, dt, final_val);
    }
   

    return 0;
}