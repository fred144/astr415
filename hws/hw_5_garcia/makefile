all: regular 

regular:
	gcc -o p1_pset5  p1_pset5.c  -lm
	gcc -o p2_pset5_frog  p2_pset5_frog.c -lm 
	gcc -o p2_pset5_rk4  p2_pset5_rk4.c -lm 
	chmod 755 hw5_bash.sh
clean: 
	rm -rf *.o p1_pset5  p2_pset5_frog p2_pset5_rk4
	rm -rf *.png
	rm -rf *.txt
	rm -rf problem_1_data/*
	rm -rf problem_2_data/frog/*
	rm -rf problem_2_data/rk4/*

# DO NOT DELETE