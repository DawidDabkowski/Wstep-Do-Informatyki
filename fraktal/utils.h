#ifndef __UTILS_H_INCLUDED__
#define __UTILS_H_INCLUDED__

#include <gtk/gtk.h>

void set_color(double red, double green, double blue);
void line(double x1, double y1, double x2, double y2);
void circle(double x, double y, double r);
void circle_fill(double x, double y, double r);
void rectangle(double x, double y, double width, double height);
void rectangle_fill(double x, double y, double width, double height);
void triangle(double x1, double y1, double x2, double y2, double x3, double y3);
void triangle_fill(double x1, double y1, double x2, double y2, double x3, double y3);
void point(double x, double y);
void text(double x, double y, const char * utf8, double size);

#endif

