#ifndef __OUTPUT__
#define __OUTPUT__

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//////////// struct and static funct /////////////////////////////////
typedef struct _str_and_vertex{
	char str[200];
	int x1, y1, x2, y2;
}SV;

static void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer user_data);
static gboolean draw(GtkWidget *widget, cairo_t *new_cr, gpointer user_data);
//////////////////////////////////////////////////////////////////////



/////////////////// output class ////////////////////////////

class output{
public:
    void output_init(SV* struct_ptr, int* int_ptr);
    // void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer user_data);
    // gboolean draw(GtkWidget *window, cairo_t *cr, gpointer userdata);
};

//////////////////////////////////////////////////////////////

#endif