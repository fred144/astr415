#!/bin/bash

find . -name '*.dat' -exec rm -f {} \;

echo ">> doing static arrays runs, can seg fault, but error redirected to text file."
for i in {0..5000..10}
do  
	{ ./static rows "$i" >> static_row_major.dat; } 2>segfault_error.dat
done

for i in {0..5000..10}
do  
	{ ./static columns "$i" >> static_col_major.dat; } 2>segfault_error.dat
done

echo ">> doing malloc arrays, less likely to seg fault"
for i in {0..5000..10}
do  
	{ ./dynamic rows "$i" >> dynamic_row_major.dat; } 2>segfault_error.dat
done

for i in {0..5000..10}
do  
	{ ./dynamic columns "$i" >> dynamic_col_major.dat; } 2>segfault_error.dat
done

echo ">> doing -O2 optimized runs"
for i in {0..5000..10}
do  
	{ ./dynamic_optimized rows "$i" >> dynamic_row_major_optimized.dat; } 2>segfault_error.dat
done

for i in {0..5000..10}
do  
	{ ./dynamic_optimized columns "$i" >> dynamic_col_major_optimized.dat; } 2>segfault_error.dat
done

python3 plot_hw2.py 
