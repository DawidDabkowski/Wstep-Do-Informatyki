/*  wzorowane na przykłądach z kursu http://cpp0x.pl/kursy/Kurs-Glade-GTK+/Podstawy-obslugi-programu-Glade/453 */
/* oraz https://developer.gnome.org/gtk3/3.0/gtk-getting-started.html */

#include <gtk/gtk.h>

#define UI_FILE "project.glade"

static cairo_surface_t *surface = NULL;
cairo_t *draw_cr = NULL;

#define BG_COLOR_R 0.0
#define BG_COLOR_G 0.0
#define BG_COLOR_B 0.0


G_MODULE_EXPORT void on_window1_destroy(GtkButton *button, gpointer user_data)
{
	gtk_main_quit();
}


static void clear_surface(void) {
	cairo_t *cr;
	cr = cairo_create(surface);
	cairo_set_source_rgb(cr, BG_COLOR_R, BG_COLOR_G, BG_COLOR_B);
	cairo_paint(cr);
	cairo_destroy(cr);
}


G_MODULE_EXPORT gboolean on_darea_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
	g_print( "on_darea_draw function call\n" );

	cairo_set_source_surface(cr, surface, 0, 0);
	cairo_paint(cr);

	return FALSE;
}	



G_MODULE_EXPORT gboolean on_darea_configure_event(GtkWidget *widget, GdkEventConfigure *event, gpointer user_data) {
	g_print( "on_darea_configure_event function call\n" );
	if (surface)
		cairo_surface_destroy(surface);
	guint width = gtk_widget_get_allocated_width(widget);
	guint height = gtk_widget_get_allocated_height(widget);
	surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget),
					CAIRO_CONTENT_COLOR,
					width,
					height);

	clear_surface();

	draw_cr = cairo_create(surface);
	draw();
	cairo_destroy(draw_cr);
	draw_cr = NULL;

	return TRUE;
}


GtkWidget * create_window(void) {
	GtkWidget * window1;
	GtkBuilder * builder;
	GError * error = NULL;

	/* Create builder object */
	builder = gtk_builder_new();

	/* Read interface content from file and check for errors */
	if(!gtk_builder_add_from_file( builder, UI_FILE, &error)) {
		g_warning("Cannot read builder file content: %s", error->message);
		g_error_free(error);
	}

	/* Connect signals with proper functions */
	gtk_builder_connect_signals(builder, NULL);
	
	/* Get "window1" object */
	window1 = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));

	/* Dispose builder object */
	g_object_unref(builder);
	
	return window1;
}


int main(int argc, char * argv[]) {
	GtkWidget * window1;

	gtk_init(& argc, & argv);
   	
	window1 = create_window();
	gtk_widget_show(window1);

	gtk_widget_set_size_request(window1, 1200, 1000);
	gtk_window_set_resizable(GTK_WINDOW(window1), FALSE);



	/*
	cairo_move_to(cr, 100, 100);
	cairo_line_to(cr, 500, 500);
	cairo_set_line_width(cr, 1);
	cairo_stroke(cr);
	*/

	gtk_main();
	return 0;
}

