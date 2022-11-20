#!/bin/csh

make clean
make
rm -f test.*

ode-template eu > test.eu
ode-template lf > test.lf
ode-template rk4 > test.rk4
python3 plot.py
