#include <stdio.h>
//https://www.astro.umd.edu/~ricotti/NEWWEB/teaching/ASTR415/intro_C_examples/node3.html
/* print Fahrenheit-Celsius table */
main()
{
  int fahr;

  for (fahr = 0; fahr <= 300; fahr = fahr + 20)
    printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
    // adding decimal point causes a float.
    // %f is float
    // pads the front with spaces. 
    // 6.1f means six characters (including pads) with one decimal points
}