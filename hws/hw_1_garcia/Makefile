all: regular optimized 

regular:
	gcc -o gcc_no_optimize hw_1.c -lm
	chmod 755 hw1_bash.sh 
optimized:
	gcc -O3 -o gcc_optimized hw_1.c -lm
	cc -O3 -o cc_optimized hw_1.c -lm
	chmod 755 hw1_bash.sh 
clean: 
	rm -rf *.o gcc_no_optimize gcc_optimized cc_optimized
	rm -rf *.dat
	rm -rf *.png

# DO NOT DELETE