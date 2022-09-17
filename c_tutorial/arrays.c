#include <stdio.h>

/* count digits, white space, others */
int main()
{
  int c, i, nwhite, nother;
  int ndigit[10]; // initialize a len() = 10 arrays

  nwhite = nother = 0;
  for (i = 0; i < 10; ++i) // index goes from 0 - 9 
    ndigit[i] = 0;
  // malloc can do this too: 
  // https://www.tutorialspoint.com/c_standard_library/c_function_malloc.htm
  // the arrays are stored in the memory
  
  while ((c = getchar()) != EOF)
    if (c >= '0' && c <= '9')
      ++ndigit[c-'0'];
    else if (c == ' ' || c == '\n' || c == '\t')
      ++nwhite;
    else
      ++nother;

  printf("digits =");
  for (i = 0; i < 10; ++i)
    printf(" %d", ndigit[i]);
  printf(", white space = %d, other = %d\n",
	 nwhite, nother);

  //variable size arrays
  double *myArray;
  myArray = (double *) malloc(n*sizeof(double));
  assert(myArray != NULL);
  DoSomethingWith(myArray);
  free((void *) myArray);

  // static 
  array[10][12]
  

  //multidimensions dynamically
  double **myArray;
  int i;
  // ** means pointer of pointer
  // 
  myArray = (double **) malloc(m*sizeof(double *));
  assert(myArray);
  // for each array element, point to a vector
  // 
  for (i=0;i<m;i++) {
    myArray[i] = (double *) malloc(n*sizeof(double));
    assert(myArray[i]);
  }
  DoSomethingWith(myArray);
  for (i=0;i<m;i++)
    free( (void *) myArray[i]);
  free((void *) myArray);

}