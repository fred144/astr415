#include <stdio.h>
#include <math.h>
#include <string.h>
#include "./nr.h"
#include "./nrutil.h"

void lf2(float *y, float *dydx, int n, float x, float h, float *yout,
        void (*derivs)(float, float *, float *));

void eul1(float *y, float *dydx, int n, float x, float h, float *yout,
        void (*derivs)(float, float *, float *));

void deriv(float t, float y[], float f[]){

	f[1]=y[2];
	f[2]=-y[1];
}

int main(int argc,char *argv[]){
  if (argc != 2) {
    printf("Usage: %s rk4|eu|lf \n",argv[0]);
    return 1;
  }

  printf("%s received method=%s\n",argv[0],argv[1]);

	int N=2;
	float *y=vector(1,N);
	float *d=vector(1,N);

	float time=15.0;
	float h=0.1;
	int Nsteps=time/h;

	float t=0.0;
	y[1]=1.;
	y[2]=0.;

	printf("%f %f %f\n",t,y[1],y[2]);	
	for(int i=1; i<=Nsteps;i++){
		deriv(t,y,d);
		if (strcmp(argv[1],"rk4") == 0) rk4(y,d,N,t,h,y,*deriv);
		if (strcmp(argv[1],"lf") == 0) lf2(y,d,N,t,h,y,*deriv);
		if (strcmp(argv[1],"eu") == 0) eul1(y,d,N,t,h,y,*deriv);
		t=i*h;
		printf("%f %f %f\n",t,y[1],y[2]);	
	}
	return 1;
	}
	

