- r (run code)
- q (quit) 
- break
>https://www.astro.umd.edu/~ricotti/NEWWEB/teaching/ASTR415/GDB.pdf 
- debugger
    - change code at run time
    - floating point exception 
    ```c
    #include <xmmintrin.h>
    _MM_setcsr(_MM....)
    for (i=0; i<100 ; i++){
        y = 1000000000 * i;
        x = -1.0 / (50 - i); 
    }
    ``` 
    - floating point exception at `x = 50`. 

## Parallelization
- add line for a for loop, basically, some can't be broken into multiple processes though
- 
```c
#pragma omp parallel for default(none) shared(xd1) private(i,g)
```

```terminal 
gcc -o timer_omp timer_omp.c -fopenmp -lm
setenv OMP_NUM_THREAD 1 
```
## GPU Computing
- nvcc compiler
```
__global__ void Mat
```