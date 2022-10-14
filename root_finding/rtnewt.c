#include <math.h>
#define JMAX 20
#define Doub double

Doub rtnewt(void (*funcd)(Doub, Doub *, Doub *), Doub x1, Doub x2,
	Doub xacc)
{
	void nrerror(char error_text[]);
	int j;
	Doub df,dx,f,rtn;

	rtn=0.5*(x1+x2);
	for (j=1;j<=JMAX;j++) {
		(*funcd)(rtn,&f,&df);
		dx=f/df;
		rtn -= dx;
		if ((x1-rtn)*(rtn-x2) < 0.0)
			nrerror("Jumped out of brackets in rtnewt");
		if (fabs(dx) < xacc) return rtn;
	}
	nrerror("Maximum number of iterations exceeded in rtnewt");
	return 0.0;
}
#undef JMAX
/* (C) Copr. 1986-92 Numerical Recipes Software ?421.1-9. */
