# Fred Angelo Garcia | P. Set #4 | ASTR415 | Fall 2022
Visit [https://github.com/fred144/astr415/tree/main/hws/hw_3_garcia](https://github.com/fred144/astr415/tree/main/hws/hw_4_garcia) for a full rendered version of this file. 

## Compilation 
#### Pre-requisites
```console
GNU bash, version 5.0.17(1)-release (x86_64-pc-linux-gnu)
python 3.8.10 
matplotlib
numpy
gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
```
The compressed folder should contain the precompiled code. 

However, you can rebuild it by doing the following.
```console
user~$ make clean
user~$ make all
user~$ ./hw4_bash.sh
```

After that, the directory should contain 
```
drwxr-xr-x 2 fabg fabg    4096 Oct 22 18:54 given_scripts   [misc scripts]
-rwxr-xr-x 1 fabg fabg     145 Oct 23 01:45 hw4_bash.sh     [run me]
-rw-r--r-- 1 fabg fabg     242 Oct 23 01:23 makefile        [make file]
-rw-r--r-- 1 fabg fabg 4200000 Oct 23 01:49 p1_data.txt     [data set]
-rwxr-xr-x 1 fabg fabg   17152 Oct 23 02:03 p1_pset4        [executable]
-rw-r--r-- 1 fabg fabg     711 Oct 23 01:45 p1_pset4.c      [script for 1stproblem]
-rw-r--r-- 1 fabg fabg   54302 Oct 23 01:49 p1_results.png  [plot]
-rw-r--r-- 1 fabg fabg     427 Oct 23 01:49 p2_data.txt     [data set]
-rwxr-xr-x 1 fabg fabg   17048 Oct 23 02:03 p2_pset4        [executable]
-rw-r--r-- 1 fabg fabg    1779 Oct 23 01:45 p2_pset4.c      [script for 2nd problem]
-rw-r--r-- 1 fabg fabg   33187 Oct 23 01:49 p2_results.png  [plot]
-rw-r--r-- 1 fabg fabg    2058 Oct 23 01:49 plot.py         [plotting scipt]
-rw-r--r-- 1 fabg fabg    2472 Oct 23 02:03 random_1.o      [rand1]
-rw-r--r-- 1 fabg fabg    2282 Oct 23 01:51 readme.md       [this file]
```
## Commentary and Answers 

### Problem 1

>We aproach the question by first computing the CDF, P(x). Then solving for the $P^{-1}(U)$, which is the transormed distribution.
>$$\int p(y) dy = \int y\exp({\frac{-y^2}{2}}) dy \rightarrow P(x) = \int_{- \infty}^x y \exp({\frac{-y^2}{2}}) = 1 - \exp(\frac{-x^2}{2})dy$$
>$$ P (P^{-1}(U)) = U = 1 - \exp(\frac{-P^{-1}(U)^2}{2})$$
>$$ P^{-1}(U) = \sqrt{-\ln\left(\left(-U+1\right)^{2}\right)}  \rightarrow  \sqrt{-2\ln\left(-U+1\right)} $$
> We end up with the following. 

<p align="center">
<img src=./p1_results.png alt="drawing" width="500"/> 
</p>

### Problem 2
>Here we just make sure that our random points have the right possible range of values. 
```C
...
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
            ...
```
> We get. 
<p align="center">
<img src=./p2_results.png alt="drawing" width="500"/> 
</p>

> Note, one way to check is to see if making the sample volume bigger. We should get convergence from the top
<p align="center">
<img src=./test.png alt="drawing" width="500"/> 
</p>
> It checks out. 
