all: regular optimized 

regular:
	gcc -o dynamic  hw_2_dynamic_array.c -lm 
	gcc -o static  hw_2_static_array.c -lm 
	gcc -o quad_form quad_form.c -lm 
	chmod 755 hw2_bash_script.sh 
optimized:
	gcc -O2 -o dynamic_optimized hw_2_dynamic_array.c -lm 
	gcc -o quad_form quad_form.c -lm 
	chmod 755 hw2_bash_script.sh 
clean: 
	rm -rf *.o dynamic static dynamic_optimized static_optimized
	rm -rf *.dat
	rm -rf *.png

# DO NOT DELETE