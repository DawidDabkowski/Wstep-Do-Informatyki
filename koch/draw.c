#include "utils.h"
#include <math.h>
#include <unistd.h>
#include <cairo.h>

void koch(int lev, double h, double x1, double y1, double x2, 
double y2, double x3, double y3){
	double h1=h/3;
	set_color(1.0, 1.0, 1.2);
	triangle_fill(x1,y1,x2,y2,x3,y3);
	triangle_fill(x1,y1-h1*2,x2,y1-h1*2,x3,y1+h1);
	if (lev>0){
		double x12a=x1+(x2-x1)/3;
		double y12a=y1;
		double x12b=x2-(x2-x1)/3;
		double y12b=y1;
		double x12c=(x1+x2)/2;
		double y12c=y1+h;
		double x13a=x1+(x3-x1)/3;
		double y13a=y1-h1;
		double x13b=x3-(x3-x1)/3;
		double y13b=y3+h1;
		double x13c=x1;
		double y13c=y13b;
		double x23a=x3+(x2-x3)/3;
		double y23a=y3+h1;
		double x23b=x2-(x2-x3)/3;
		double y23b=y2-h1;
		double x23c=x2;
		double y23c=y23a;
		koch(lev-1,h1,x1,y1,x12a,y12a,x13a,y13a);
		koch(lev-1,h1,x1,y1-h1*4/3,x12a,y12a-h1*4/3,x13a,y13a-h1*4/3);
		koch(lev-1,h1,x12b,y12b,x2,y2,x23b,y23b);
		koch(lev-1,h1,x12b,y12b-h1*4/3,x2,y2-h1*4/3,x23b,y23b-h1*4/3);
		koch(lev-1,h1,x13b,y13b,x23a,y23a,x3,y3);
		koch(lev-1,h1,x13b,y13b+h1*8/3,x23a,y23a+h1*8/3,x3,y3+h1*8/3);
	}
}
void draw(int lev, double h, double x1, double y1, double x2, double y2, double x3, double y3){
	lev=5;				/*Optymalnie [0;6]*/
	x1=300;
	y1=530;
	x2=900;
	y2=530;
	h=tan(M_PI/3)*(x2-x1)/2;	/*Optymalnie [0;M_PI/2]*/
	x3=(x1+x2)/2;
	y3=y1-h;
	koch(lev, h, x1, y1, x2, y2, x3, y3);
}



