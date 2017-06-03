#include <gtk/gtk.h>
#include <cairo.h>
#include "utils.h"

extern cairo_t *draw_cr;


void set_color(double red, double green, double blue) {
	cairo_set_source_rgb(draw_cr, red, green, blue); 
}


void line(double x1, double y1, double x2, double y2) {
	cairo_move_to(draw_cr, x1, y1);
	cairo_line_to(draw_cr, x2, y2);
	cairo_set_line_width(draw_cr, 1);
	cairo_stroke(draw_cr);
}


static void circle_base(double x, double y, double r, int fill) {
	cairo_arc(draw_cr, x, y, r, 0, 2 * G_PI);
	cairo_set_line_width(draw_cr, 2);
	if (fill) {
		cairo_stroke_preserve(draw_cr);
		cairo_fill(draw_cr);
	} else {
		cairo_stroke(draw_cr);
	}
}


void circle(double x, double y, double r) {
	circle_base(x, y, r, 0);
}


void circle_fill(double x, double y, double r) {
	circle_base(x, y, r, 1);
}


static void rectangle_base(double x, double y, double width, double height, int fill) {
	cairo_rectangle(draw_cr, x, y, width, height);
	cairo_set_line_width(draw_cr, 2);
	if (fill) {
		cairo_stroke_preserve(draw_cr);
		cairo_fill(draw_cr);
	} else {
		cairo_stroke(draw_cr);
	}
}


void rectangle(double x, double y, double width, double height) {
	rectangle_base(x, y, width, height, 0);
}


void rectangle_fill(double x, double y, double width, double height) {
	rectangle_base(x, y, width, height, 1);
}


void triangle_base(double x1, double y1, double x2, double y2, double x3, double y3, int fill) {
	cairo_set_line_width(draw_cr, 1);
	cairo_move_to(draw_cr, x1, y1);
	cairo_line_to(draw_cr, x2, y2);
	cairo_line_to(draw_cr, x3, y3);
	cairo_close_path(draw_cr);
	if (fill) {
		cairo_stroke_preserve(draw_cr);
		cairo_fill(draw_cr);
	} else {
		cairo_stroke(draw_cr);
	}
}


void triangle(double x1, double y1, double x2, double y2, double x3, double y3) {
	triangle_base(x1, y1, x2, y2, x3, y3, 0);
}


void triangle_fill(double x1, double y1, double x2, double y2, double x3, double y3) {
	triangle_base(x1, y1, x2, y2, x3, y3, 1);
}


void point(double x, double y) {
	cairo_rectangle(draw_cr, x, y, 1, 1);
	cairo_fill(draw_cr);
}


void text(double x, double y, const char *utf8, double size) {
	cairo_select_font_face(draw_cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(draw_cr, size);
	cairo_move_to(draw_cr, x, y);
	cairo_show_text(draw_cr, utf8);
	cairo_new_path(draw_cr);
}








