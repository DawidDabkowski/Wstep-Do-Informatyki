#include "utils.h"
#include <math.h>
#include <unistd.h>
#include <cairo.h>

void fraktal(int lev1, int lev2, double konts, double kont, double a1, double h1, double x1, 
double y1, double x2, double y2, double x3, double y3){
	set_color(0.3+0.3*lev1, 0.2*lev2, 0.1);
	triangle(x1,y1,x2,y2,x3,y3);
	if (lev1>0){
		double h2=sin(konts)*a1;
		double a2=cos(konts)*a1;
		double x22=x2;
		double y22=y2;
		double x32=x1;
		double y32=y1;
		double x12=x1+(sin(kont)*h2);
		double y12=y1+(cos(kont)*h2);
		fraktal(lev1-1,lev2,konts,konts+kont,a2,h2,x12,y12,x22,y22,x32,y32);
	}	
	if (lev2>0){
		double h3=sin(konts)*h1;
		double a3=cos(konts)*h1;
		double x23=x1;
		double y23=y1;
		double x33=x3;
		double y33=y3;
		double x13=x3+(sin(kont-M_PI/2)*h3);	/* ?? */
		double y13=y3+(cos(kont-M_PI/2)*h3);
		fraktal(lev1,lev2-1,konts,kont-konts*2,a3,h3,x13,y13,x23,y23,x33,y33);	
	}
}
void draw(int lev1, int lev2, double konts, double kont, double a1, double h1, double x1, 
double y1, double x2, double y2, double x3, double y3){
	lev1=9;      /* np. 11-6 lub 9-9 lub 11-11*/
	lev2=9;
	konts=M_PI/6;	/* z zakresu [0,M_PI/2] */
	kont=konts;
	x1=400;	
	x2=800;
	y1=320;
	y2=320;
	a1=x2-x1;	
	h1=tan(kont)*a1;
	x3=x1;
	y3=y1-h1;
	fraktal(lev1, lev2, konts, kont, a1, h1, x1, y1, x2, y2, x3, y3);
}

/*	{
		/*set_color(0.5, 0.6+1.0/20*i, 0.8);
		triangle_fill(300, 400, 
				300+100*cos(M_PI/4 - M_PI/6*i), 400-100*sin(M_PI/4 - M_PI/6*i),
				300+100*cos(M_PI/4 - M_PI/6*(i+1)), 400-100*sin(M_PI/4 - M_PI/6*(i+1))
				);
	}
*/



