all: struct timer argv

struct:
	cc -o struct struct.c
timer:
	cc -o timer timer.c -lm
argv:
	cc -o argv argv.cc
clean: 
	rm -rf *.o struct timer argv
	rm -rf *.png results

# DO NOT DELETE