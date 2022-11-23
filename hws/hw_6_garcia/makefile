all: regular 

regular:
	gcc -o frog pset6_frog.c  -lm
	gcc -o rk4 pset6_rk4.c  -lm
	chmod 755 hw6_bash.sh
clean: 
	rm  -rf *.o frog rk4
	rm -rf data_frog/*.txt
	rm -rf sequence_frog/*.png
	rm -rf data_rk4/*.txt
	rm -rf sequence_rk4/*.png


# DO NOT DELETE