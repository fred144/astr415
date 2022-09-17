#include <stdio.h>

/* print Fahrenheit-Celsius table
   for fahr = 0, 20, ..., 300 */
int main()
{
  int fahr, celsius;
  int lower, upper, step;

  lower = 0;     /* lower limit of temperature table */
  upper = 300;   /* upper limit */
  step = 20;     /* step size */

  fahr = lower;
  while (fahr <= upper) {
    celsius = 5*(fahr - 32)/9;
    //  format the output
    // %d says that the fahrenheit is into %d
    // \t is for line
    // %d is integer
    
    printf("%d\t%d\n", fahr, celsius);
     // increase the value of the fahrenhite by step
    fahr = fahr + step;
  }
}