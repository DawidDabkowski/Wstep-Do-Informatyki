#include <gtk/gtk.h>
#include "drawing.h"

#define UI_FILE "project.glade"


cairo_surface_t *surface = NULL;
unsigned int width;
unsigned int height;
double bg_color_r = 1;
double bg_color_g = 1;
double bg_color_b = 1;

static int running = 1;



G_MODULE_EXPORT void on_start_button_clicked(GtkButton *button, gpointer user_data) {
	running = 1;
}

G_MODULE_EXPORT void on_pause_button_clicked(GtkButton *button, gpointer user_data) {
	running = 0;
}

G_MODULE_EXPORT void on_window1_destroy(GtkButton *button, gpointer user_data) {
	gtk_main_quit();
}

G_MODULE_EXPORT gboolean on_darea_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
	cairo_t *cr2;
	cr2 = cairo_create(surface);
	cairo_set_source_rgb(cr2, bg_color_r, bg_color_g, bg_color_b);
	cairo_paint(cr2);
	prog_draw();	
	cairo_destroy(cr2);
	cairo_set_source_surface(cr, surface, 0, 0);
	cairo_paint(cr);
	return FALSE;
}	

G_MODULE_EXPORT gboolean on_darea_configure_event(GtkWidget *widget, GdkEventConfigure *event, gpointer user_data) {
	if (surface)
		cairo_surface_destroy (surface);
	width = gtk_widget_get_allocated_width(widget);
	height = gtk_widget_get_allocated_height(widget);
	surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
					CAIRO_CONTENT_COLOR,
					width,
					height);

	return TRUE;
}

GtkWidget * create_window(void) {
	GtkWidget * window1;
	GtkBuilder * builder;
	GError * error = NULL;
	builder = gtk_builder_new();
	if(!gtk_builder_add_from_file( builder, UI_FILE, &error)) {
		g_error_free(error);
	}
	gtk_builder_connect_signals(builder, NULL);
	window1 = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
	g_object_unref(builder);
	return window1;
}

gboolean drawing_timer_exe(GtkWidget *window){
	gtk_widget_queue_draw_area(window, 0, 0, width, height);
	return TRUE;
}

gboolean updating_timer_exe(GtkWidget *window){
	if (running) {
	    prog_update();
	}
	return TRUE;
}

int main(int argc, char * argv[]) {
	GtkWidget * window1;
	gtk_init(& argc, & argv);
	window1 = create_window();
	gtk_widget_show(window1);
	gtk_widget_set_app_paintable(window1, TRUE);
	gtk_widget_set_double_buffered(window1, TRUE);
	prog_init();
	g_timeout_add(33, (GSourceFunc)drawing_timer_exe, window1);
	g_timeout_add(33, (GSourceFunc)updating_timer_exe, window1);
	gtk_main();
	return 0;
}

