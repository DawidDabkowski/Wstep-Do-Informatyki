#include "utils.h"
#include <math.h>
#include <unistd.h>
#include <cairo.h>

void sierpinski(int level, double x1, double y1, double x2, 
double y2, double x3, double y3){
	triangle(x1,y1,x2,y2,x3,y3);
	if (level>0){
		double x12=(x1+x2)/2;
		double y12=(y1+y2)/2;
		double x13=(x1+x3)/2;
		double y13=(y1+y3)/2;
		double x23=(x2+x3)/2;
		double y23=(y2+y3)/2;
		sierpinski(level-1,x1,y1,x12,y12,x13,y13);
		sierpinski(level-1,x12,y12,x2,y2,x23,y23);
		sierpinski(level-1,x13,y13,x23,y23,x3,y3);		
	}
}
void draw(){
	set_color(0.7, 0.7, 0.7); 
	sierpinski(5, 400, 10, 100, 500, 700, 500);
}

/*	{
		/*set_color(0.5, 0.6+1.0/20*i, 0.8);
		triangle_fill(300, 400, 
				300+100*cos(M_PI/4 - M_PI/6*i), 400-100*sin(M_PI/4 - M_PI/6*i),
				300+100*cos(M_PI/4 - M_PI/6*(i+1)), 400-100*sin(M_PI/4 - M_PI/6*(i+1))
				);
	}
*/



