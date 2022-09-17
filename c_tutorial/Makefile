all: struct timer argv

struct:
	cc -o struct struct.c
timer:
	cc -o timer timer.c -lm
argv:
	cc -o argv argv.cc
clean: 
	rm -rf *.o struct timer argv

# DO NOT DELETE