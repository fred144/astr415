all: regular 

regular:
	gcc -o problem1  problem1.c -lm 
	gcc -o problem2  problem2.c ./given_scripts/nrutil.c ./given_scripts/gaussj.c -lm 
	chmod 755 hw3_bash.sh
clean: 
	rm -rf *.o problem1 problem2
	rm -rf *.png

# DO NOT DELETE