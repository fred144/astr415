# Fred Angelo Garcia | P. Set #6 | ASTR415 | Fall 2022
Visit [https://github.com/fred144/astr415/tree/main/hws/hw_5_garcia](https://github.com/fred144/astr415/tree/main/hws/hw_5_garcia) for a full rendered version of this file. 

## Compilation 
#### Pre-requisites
```console
GNU bash, version 5.0.17(1)-release (x86_64-pc-linux-gnu)
python 3.8.10 
matplotlib
numpy
PIL
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
total 19M
-rwxr-xr-x 1   27K Nov 22 18:46 a.out        [test]
drwxr-xr-x 2  1.1M Nov 22 21:44 data_frog    [data gets temporarily stored here]
drwxr-xr-x 2  1.1M Nov 22 21:44 data_rk4     [data gets temporarily stored here]
-rw-r--r-- 1   239 Nov 22 14:08 e_05_init.txt [starting conditions]
-rw-r--r-- 1   239 Nov 22 14:08 e_09_init.txt [starting conditions]
-rwxr-xr-x 1   27K Nov 22 21:06 frog            [executable]
-rw-r--r-- 1   15M Nov 22 21:00 frog_0.5.gif    [good gif]
-rw-r--r-- 1   26K Nov 22 21:36 frog_0.9.gif    [too short gif]
drwxr-xr-x 3  4.0K Nov 22 18:48 given_scripts   [num rec scripts]
-rwxr-xr-x 1   706 Nov 22 21:41 hw6_bash.sh     [run me]
-rw-r--r-- 1   256 Nov 22 18:38 makefile        [don't delete]
-rw-r--r-- 1  8.1K Nov 22 16:33 matrix_frog.c   [trial script]
-rw-r--r-- 1  4.3K Nov 22 21:43 plot.py         [plotting func]
-rw-r--r-- 1  7.4K Nov 22 20:07 pset6_frog.c    [main frog script]
-rw-r--r-- 1  7.0K Nov 22 19:11 pset6_rk4.c     [main rk4 script]
-rw-r--r-- 1  6.0K Nov 22 21:43 readme.md       [this file]
-rwxr-xr-x 1   27K Nov 22 21:06 rk4             [executable]
-rw-r--r-- 1   26K Nov 22 21:36 rk4_0.5.gif     [bad gif]
-rw-r--r-- 1  1.8M Nov 22 17:10 rk4_0.9.gif     [bad gif]
drwxr-xr-x 2  4.0K Nov 22 21:43 saved_frames    [images/ results]
drwxr-xr-x 2  128K Nov 22 21:40 sequence_frog   [temp directory]
drwxr-xr-x 2  4.0K Nov 22 21:40 sequence_rk4    [temp directory]
```
## Commentary and Answers 

We have a system of two particles, $1$ and $2$ with a given mass, position, and velocities in 3D space
[$m1$ , $x_1$, $y_1$, $z_1$, $\dot{x_1}$, $\dot{x_1}$, $\dot{x_1}$ ] 
[$m2$ , $x_2$, $y_2$, $z_2$, $\dot{x_2}$, $\dot{x_2}$, $\dot{x_2}$ ]

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

Note, I have chose my program to run using the parameters stored in

```./rk4 0 0.05 10 1 e_05_init.txt```

Where the first index is the softening implemented as ```0 ```for now. ```0.05``` is the step size, ```10``` is the *end time* and `e_05_init.tx` is the input file with the header format:

```
# paticle_mass, x, y, z, v_x, v_y, v_z
```

Notice that eccentricity is not part of this. This is a strict 2 body problem and, in the spirit of generalizing our nbody code, will not be taking in the eccentricity. Hence, given the intial velocities, we have calculated the corresponding initial velocities. 

For the $e = 0.5$ case, it is stored in `e_05_init.txt` and accordingly for `e_09_init.txt`. 

We are told to analyze it for 100 orbits. This is dependent on the eccentricity. 
Given that $a = \frac{1}{1+e}$

$ p^2 = \frac{4\pi^2}{GM}a^3 \rightarrow p = \frac{2\pi}{\sqrt{GM}} \frac{1}{(1+e)^{3/2}}$

for equal mass particles $M=2$ and if we take $G=1$. 

$$
p = \frac{2\pi}{\sqrt{2}} \frac{1}{(1+e)^{3/2}}
$$

Finally, we get p(0.5) = 2.41 and p(0.9) = 1.69. Which means our end time parameters should be adjust accordingly to 241 and 169. To make smooth visualizations, the output time step should be as small as possible while having enough time for dynamical evolution. Hence, we sometimes have to use lower times. This is strictly a computational resource issue. My laptop takes too long to render these gifs. Also, the time steps in the gifs are not consistent. some are sped up some are not. this is just a choice due to rendering times.

>smooth gifs take time to render. Unless you want to wait a long time, don't run the bash scripts. It also auotmates deletion inside the sequence_ and data_ directories, so last frame of each rendering run is saved in saved_frames. Or at least comment out the lines calling the plotting scripts.
___

Here is a rendered gif for the 0.5 eccentricity. If reading on the pdf, click on the link. it should redirect to github. these take way too long to render so I only made one full one. The other gif are unfinished. 
<p align="center">
<img src=./frog_0.5.gif alt="drawing" width="800"/> 
</p>


Here are the final frames for each.  

</p>
<p align="center">
<img src=./saved_frames/frame_4800_frog_0.5.png alt="drawing" width="800"/> 

</p>

</p>
<p align="center">
<img src=./saved_frames/frame_9999_frog_0.9.png alt="drawing" width="800"/> 

</p>

</p>
<p align="center">
<img src=./saved_frames/frame_4800_rk4_0.5.png alt="drawing" width="800"/> 

</p>

</p>
<p align="center">
<img src=./saved_frames/frame_9999_rk4_0.9.png alt="drawing" width="800"/> 

</p>


Per usual leapfrog is conservative while rk4 is not. this is especially true when looking at the total energy plots. Whereby there is a noticable sag for the rk4, while the leapfrog reaches a steady state. The volume is conserved in phases space for leapfrog which hints at conservation. For rk4 this is not the case, it is loosing energy so it seems to be shrinking. The energy when comparing, is lower in te rk4. 
