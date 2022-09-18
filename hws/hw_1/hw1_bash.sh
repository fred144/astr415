#!/bin/bash 

rm *.dat

iterations="1e6 3e6 1e7 3e7 1e8 1e9" 

# here do the part 1 
echo "double precission addition"
echo "# number of iterations, time of execution, the final value" >>  gcc_double_add_results.dat
for iter_num in $iterations
do  

    ./gcc_no_optimize double add $iter_num >> gcc_double_add_results.dat
    
done 
echo "double precission multiplication"
echo "# number of iterations, time of execution, the final value" >>  gcc_double_multiply_results.dat
for iter_num in $iterations
do  
    ./gcc_no_optimize double multiply $iter_num >> gcc_double_multiply_results.dat
    
done 
echo "double precission power"
echo "# number of iterations, time of execution, the final value" >>  gcc_pow_results.dat
for iter_num in $iterations
do  
    ./gcc_no_optimize double pow $iter_num >> gcc_pow_results.dat
    
done 
echo "double precission sqrt"
echo "# number of iterations, time of execution, the final value" >>  gcc_sqrt_results.dat
for iter_num in $iterations
do  
    ./gcc_no_optimize double sqrt $iter_num >> gcc_sqrt_results.dat
    
done 


# here do the optimizations using gcc
echo "gcc optimized"

echo "double precission add"
echo "# number of iterations, time of execution, the final value" >> gcc_O2_double_add_results.dat
for iter_num in $iterations
do  
    ./gcc_O2_optimized double add $iter_num >> gcc_O2_double_add_results.dat
    
done 

echo "double precission multiply"
echo "# number of iterations, time of execution, the final value" >> gcc_O2_double_multiply_results.dat
for iter_num in $iterations
do  
    ./gcc_O2_optimized double multiply $iter_num >> gcc_O2_double_multiply_results.dat
    
done 