#!/bin/bash 

echo "--solving problem 1"
stepsizes="1 0.3 0.1 0.03 0.01" 

for stepsize in $stepsizes
do  
    ./p1_pset5 $stepsize &> problem_1_data/step_$stepsize.dat
    
done 

echo "--solving problem 2"

echo "---doing leapfrog"
stepsizes="1 0.5 0.25 0.01" 
for stepsize in $stepsizes
do  
    ./p2_pset5_frog $stepsize &> problem_2_data/frog/step_$stepsize.dat
done 

echo "---doing rk4"
stepsizes="1 0.5 0.25 0.01" 
for stepsize in $stepsizes
do  
    ./p2_pset5_rk4 $stepsize &> problem_2_data/rk4/step_$stepsize.dat
done 

echo "--making plots"
python3 ./plot.py