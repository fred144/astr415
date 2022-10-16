#!/bin/bash 




# here do the part 1 
echo "using single precision float"
./problem1 float &> float.dat
echo "using double precision float"
./problem1 double  &> double.dat
echo "Doing Problem 2"
./problem2 
    


echo "making plots"
python3 ./plot.py