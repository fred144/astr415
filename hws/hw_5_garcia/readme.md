# Fred Angelo Garcia | P. Set #5 | ASTR415 | Fall 2022
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

### Problem 1

We have the system

$$ \frac{d^2 x}{dt^2} = -x$$

Which we can turn into two coupled diff equations 

$$\begin{cases}
\frac{dx}{dt} = v 
\\ 
\frac{dv}{dt} = -x 
\\
\end{cases}$$ 

We can solve this using euler method

$$\begin{cases}
v_{n+1} (t) = v_n(t) - x_n (t)\Delta t 
\\
x_{n+1} (t) = x_n(t) + v_n(t) \Delta t 
\end{cases}$$ 

Where $n=0, 1, 2,...$ and $v_0 = 1$ and $x_0 = 0$ and $\Delta t$ is the step size.  

>(a) and (b) Here we show the comparison between analytical and numerical solutions for various step sizes (see legend) and different methods (see each column title). The leap frog and euler's are quite similar, which makes sense given that one could argue that leap frog is a simple modificaiton of euler's. Note, as expected we get convergence as a function of increasing samples, or decreasing sample interval (what we have been calling as $h$). 
<p align="center">
<img src=./p1_b.png alt="drawing" width="800"/> 
</p>

>(c) Here we plot the difference in the final values as a function of step size. The absolute differences approach a smaller number as functio of decreasing step size (note, flipped axis). As expected, the euler and leapfrog is smillar, with the best performance being for Runge Kutta, which is a more sophisticated routine. Yes, the error decreases as a function of step size, given some noise. It is roughyl linear in log-log space which must mean it is a power-law of sort. I would not be surprised if it has an $N^{-1/2}$ dependance, or some other power. Maybe actually $N^{-2}$ by eye. 
<p align="center">
<img src=./p1_c.png alt="drawing" width="400"/> 
</p>

___

### Problem 2

We have the potential 

$$
\Phi = \frac{-1}{\sqrt{1+2x^2 + 2y^2}}
$$

Knowing that $F= ma = -\nabla\Phi$, we can look at the acceleration in each component. We can neglect the mass and set it to 1.  

$$
\begin{cases}
a_x = \frac{d^2x}{dt^2}= - \frac{\partial }{\partial x} \left(\frac{-1}{\sqrt{1+2x^2 + 2y^2}}\right) = -  \dfrac{2x}{\left(2x^2+2y^2+1\right)^\frac{3}{2}} 
\\
\\
a_y = \frac{d^2y}{dt^2}= - \frac{\partial }{\partial y} \left(\frac{-1}{\sqrt{1+2x^2 + 2y^2}}\right) = -  \dfrac{2y}{\left(2x^2+2y^2+1\right)^\frac{3}{2}}
\end{cases}
$$ 

We then get the coupled equations

$$
\begin{cases}
 \frac{d^2x}{dt^2}=  -  \dfrac{2x}{\left(2x^2+2y^2+1\right)^\frac{3}{2}} 
 \\
 \\
 \frac{d^2y}{dt^2}= -  \dfrac{2y}{\left(2x^2+2y^2+1\right)^\frac{3}{2}}
\end{cases}
$$ 

Reduce it to first order by integrating, note the negative sign, so it is now the potential, but positive. 

We get our coupled first order equations for the x componenet. 

$$
\begin{cases}
 \dot{x} = v_x = \dfrac{dx}{dt} = \dfrac{1}{\sqrt{2x^2 + 2y^2 + 1}} 
 \\ 
 \\
 a_x = \dfrac{dv_x}{dt} = \dfrac{d^2x}{dt^2} =  -  \dfrac{2x}{\left(2x^2+2y^2+1\right)^\frac{3}{2}}
\end{cases}
$$ 

Similarly for the y

$$
\begin{cases}
 \dot{y} = v_y = \dfrac{dy}{dt} = \dfrac{1}{\sqrt{2x^2 + 2y^2 + 1}} 
 \\ 
 \\
 a_y = \dfrac{dv_y}{dt} = \dfrac{d^2y}{dt^2} =  -  \dfrac{2y}{\left(2x^2+2y^2+1\right)^{\frac{3}{2}}}
\end{cases}
$$ 

Note, we can jus reduce these to, knowing the initial conditions for the velocities themselves, to be 

$$
\begin{cases}
 \dfrac{dx}{dt} = v_x 
 \\
 \\
 \dfrac{d^2x}{dt^2} = \dot{v_x}  =-  \dfrac{2x}{\left(2x^2+2y^2+1\right)^\frac{3}{2}}
 \\
 \\
 \dfrac{dy}{dt} = v_y 
 \\
 \\
 \dfrac{d^2y}{dt^2} = \dot{v_y } = -  \dfrac{2y}{\left(2x^2+2y^2+1\right)^\frac{3}{2}}
\end{cases}
$$ 

 
>(a) Carrying through out calculations, we get the following plots. 

<p align="center">
<img src=./p2_ab.png alt="drawing" width="800"/> 
</p>

>(b) The total energy as a function of time is on the right most column. The first column depicts the Leap frog method for various step sizes (indicated on the middle column legend). The second column from the left depicts RK4. From top to bottom, we decrease the step size leading to more numerically stable orbits with notable precession. Note, there is something that happens quite strange in the total energy when comparing the runge kutta and leap frog at very coarse step sizes (look first row). Leap frog appears that the total energy gets more and more positive, actually making the object escape the gravitational potential well. On the other hand, the rk4 method shows a more and more negative total energy as a function of time, suggesting that it is spiralling inward. This is the result of numerical error, nothing rather physical. 

>Note, an important result of the leapfrog is the way its total energy oscillates. If you were to track orbits for an extended amount of time, rk4 shows a notable sag in the total energy and it does not appear to be going the other way or restorative. For the leapfrog method, though it oscillates both in the small scales and the larger envelope, it appears to stable in a sense that it conserves energy about some small number deviation. 
