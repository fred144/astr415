#!/bin/bash 
echo "*********************************************************"
echo "RUNNING THIS WILL TAKE SOME TIME; PYTHON IS SLOW"
echo "*********************************************************"

echo "RUNNING FROG"

# no softening'

rm  data_frog/*.txt
rm  sequence_frog/*.png
./frog 0 0.05 240 1 e_05_init.txt 
python3 ./plot.py data_frog/ saved_frames/ frog 0.5

rm  data_frog/*.txt
rm  sequence_frog/*.png

./frog 0 0.003 169 1 e_09_init.txt 
python3 ./plot.py data_frog/ saved_frames/ frog 0.9

rm  data_frog/*.txt
rm  sequence_frog/*.png

echo "RUNNING RK4"

rm  data_rk4/*.txt
rm  sequence_rk4/*.png

./rk4 0 0.05  240 1 e_05_init.txt 
python3 ./plot.py data_rk4/ saved_frames/ rk4 0.5

rm  data_rk4/*.txt
rm  sequence_rk4/*.png

./rk4 0 0.003 169 1 e_09_init.txt 
python3 ./plot.py data_rk4/ saved_frames/ rk4 0.9

rm  data_rk4/*.txt
rm  sequence_rk4/*.png
