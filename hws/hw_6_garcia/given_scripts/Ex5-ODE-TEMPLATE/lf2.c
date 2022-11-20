#define NRANSI

void lf2(float y[], float dydt[], int n, float t, float h, float yout[],
	void (*derivs)(float, float [], float []))
{
	int i;
	float th,hh;

	hh=h*0.5; // half kick
	th=t+hh;
	for (i=1;i<=n;i=i+2) // adjusted velocity
		yout[i+1]=y[i+1]+hh*dydt[i+1];
	for (i=1;i<=n;i=i+2) 
		yout[i]=y[i]+h*yout[i+1]; // new position
	(*derivs)(th,yout,dydt); // 
	for (i=1;i<=n;i=i+2) 
		yout[i+1]=yout[i+1]+hh*dydt[i+1];
}
#undef NRANSI
/* (C) Copr. 1986-92 Numerical Recipes Software ?421.1-9. */
