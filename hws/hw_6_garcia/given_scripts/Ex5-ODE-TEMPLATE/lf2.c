#define NRANSI

void lf2(float y[], float dydx[], int n, float x, float h, float yout[],
	void (*derivs)(float, float [], float []))
{
	int i;
	float xh,hh;

	hh=h*0.5;
	xh=x+hh;
	for (i=1;i<=n;i=i+2) yout[i+1]=y[i+1]+hh*dydx[i+1];
	for (i=1;i<=n;i=i+2) yout[i]=y[i]+h*yout[i+1];
	(*derivs)(xh,yout,dydx);
	for (i=1;i<=n;i=i+2) yout[i+1]=yout[i+1]+hh*dydx[i+1];
}
#undef NRANSI
/* (C) Copr. 1986-92 Numerical Recipes Software ?421.1-9. */
