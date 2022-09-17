#include <stdio.h>
#include <time.h>
// starting point for HW 1
// write a bash script to run this and log the outputs into a text file. 

double getCPU(void)
{
    return (double) clock()/CLOCKS_PER_SEC; /* convert to seconds */
}

int main(void)
{
    double t0,dt;
    t0 = getCPU();         /* get initial value */
    MyExpensiveFunction();
    dt = getCPU() - t0;    /* difference to get execution time */
    (void) printf("Execution time: %g sec\n",dt);
    return 0;
}