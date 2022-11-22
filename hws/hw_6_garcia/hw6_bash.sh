#!/bin/bash 
echo "RUNNING THIS WILL TAKE SOME TIME; PYTHON PLOTTING IS SLOW"
echo "RUNNING FROG"
rm  frog_data/*
rm  frog_sequence/*
# no softening
./frog 0 0.05 10 1 e_05_init.txt 
python3 ./plot.py frog_data/ frog_sequence/ frog 0.5

# rm  frog_data/*
# rm  frog_sequence/*
# # no softening output every other 3 
# ./frog 0 0.003 18 10 e_09_init.txt 
# python3 ./plot.py frog_data/ frog_sequence/ frog 0.9
# rm  frog_data/*
# rm  frog_sequence/*s