#define NRANSI

void eul1(float y[], float dydx[], int n, float x, float h, float yout[],
	void (*derivs)(float, float [], float []))
{
	for (int i=1;i<=n;i=i+1) yout[i]=y[i]+h*dydx[i];
}
#undef NRANSI
/* (C) Copr. 1986-92 Numerical Recipes Software ?421.1-9. */
