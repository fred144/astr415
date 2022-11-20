# Fred Angelo Garcia | P. Set #6 | ASTR415 | Fall 2022
Visit [https://github.com/fred144/astr415/tree/main/hws/hw_5_garcia](https://github.com/fred144/astr415/tree/main/hws/hw_5_garcia) for a full rendered version of this file. 

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
user~$ ./hw5_bash.sh
```

After that, the directory should contain 
```
    4096 Nov  4 20:31 given_scripts   [numerical recipes]
     571 Nov  6 01:57 hw5_bash.sh     [handles different stepsizes and executing]
     352 Nov  6 01:47 makefile        [compiles stuff, all or clean]
  951489 Nov  6 02:22 p1_b.png        [plot showing the sines]
  133321 Nov  6 02:22 p1_c.png        [plot err vs step size]
   22624 Nov  6 01:57 p1_pset5        [executable for first problem]
    3272 Nov  5 19:15 p1_pset5.c      [script for first problem]
 1010653 Nov  6 02:22 p2_ab.png       [plot showing orbits and energy]    
    3949 Nov  5 23:26 p2_pset5.c      [script for first problem]
   22608 Nov  6 01:57 p2_pset5_frog   [executable for 2nd problem]
    3939 Nov  5 23:45 p2_pset5_frog.c [script for 2nd problem]
   22520 Nov  6 01:57 p2_pset5_rk4    [executable for 2nd problem]
    3077 Nov  6 00:40 p2_pset5_rk4.c  [script for 2nd problem]
    4492 Nov  6 02:22 plot.py         [main plotting scripts]
    4096 Nov  6 01:59 problem_1_data  [directory contianing tables for p1]
    4096 Nov  6 01:30 problem_2_data  [directory contianing tables for p2]
    6501 Nov  6 02:33 readme.md       [this file]
```
## Commentary and Answers 

We have a system of two particles, $1$ and $2$ with a given mass, position, and velocities in 3D space
>[$m_1$, $x_1$, $y_1$, $z_1$, $\dot{x_1}$, $\dot{x_1}$, $\dot{x_1}$ ] <br /> 
>[$m_2$, $x_2$, $y_2$, $z_2$, $\dot{x_2}$, $\dot{x_2}$, $\dot{x_2}$ ]

Particle 1 experiences an acceleration $\ddot{\vec{r_1}} = (\ddot{x_1}, \ddot{y_1}, \ddot{z_1})$ due to force of gravity from Particle 2. This can be stated as

$$
(\ddot{x_1}, \ddot{y_1}, \ddot{z_1}) = -G m_{2}\frac{ [(x_1, y_1, z_1) - (x_2, y_2, z_2)]}{|(x_1, y_1, z_1) - (x_2, y_2, z_2)|^3}
$$

Note, in general, we can apply softening $\epsilon$

$$
(\ddot{x_1}, \ddot{y_1}, \ddot{z_1}) = -G m_{2}\frac{ [(x_1, y_1, z_1) - (x_2, y_2, z_2)]}{(|(x_1, y_1, z_1) - (x_2, y_2, z_2)|^2 + \epsilon^2) ^{3/2}}
$$

Fir thus problem, we set $\epsilon$ = 0. So we just recover the first one.

For N particles, we can of course generalize this to the individual 2-body interactions and sum them. 

$$
(\ddot{x_1}, \ddot{y_1}, \ddot{z_1}) = -G \left( m_{2}\frac{ (x_1, y_1, z_1) - (x_2, y_2, z_2)}{|(x_1, y_1, z_1) - (x_2, y_2, z_2)|^3} + ... + m_{N}\frac{ (x_1, y_1, z_1) - (x_N, y_N, z_N)}{|(x_1, y_1, z_1) - (x_N, y_N, z_N)|^3} \right)
$$

For a given time, this particle 1 at $(x_1, y_1, z_1)$ experiences this $(\ddot{x_1}, \ddot{y_1}, \ddot{z_1})$. 

This generalized force produces $3N$ coupled ODEs of the second order. Which we can reduce to the first order, giving $6N$ coupled first order equations. For our case of the 2 body problem. We have 12 couples equations. This is from the fact that we are calculating the velocity and acceleration all in 3 dimensions (6 parameters). But not only on 1 caused by 2, but also on 2 caused by 1, giving us 12. 

We are given the initial conditions $m_1$ =  $m_2$ = 1
$$
[ x_1, y_1, z_1, \dot{x_1}, \dot{x_1}, \dot{x_1} ] = [ -\frac{1}{2}, 0, 0, 0, -\frac{v}{2}, 0 ] 
$$
$$
[ x_2, y_2, z_2, \dot{x_2}, \dot{x_2}, \dot{x_2} ] = [ \frac{1}{2}, 0, 0, 0, \frac{v}{2}, 0] 
$$

where $v$ is dictated by the eccentricity $e$ and $r_a$.

Given that and $\frac{1}{a} =\frac{2}{r}-\frac{v^2}{GM}$ 

We can say that $v= \sqrt{GM(\frac{2}{r} - \frac{1+e}{r_a})}$, and taking $G=1$, $M =2$, starting at $r = r_a = 1$.

$$
v = \sqrt{2(1-e)}
$$

We are then told to test  $e = 0.5$ and $e = 0.9$, so we just adjust our initial conditions accordingly. 