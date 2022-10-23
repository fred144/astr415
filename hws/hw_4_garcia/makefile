all: regular 

regular:
	gcc  -c  ./given_scripts/random_1.c  -lm 
	gcc -o p1_pset4  p1_pset4.c -lm 
	gcc -o p2_pset4  p2_pset4.c -lm 
	chmod 755 hw4_bash.sh
clean: 
	rm -rf *.o p1_pset4  p2_pset4 
	rm -rf *.png
	rm -rf *.txt

# DO NOT DELETE