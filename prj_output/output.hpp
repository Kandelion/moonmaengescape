#ifndef __OUTPUT__
#define __OUTPUT__

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

//////////// struct and static funct /////////////////////////////////
typedef struct _str_and_vertex{
	char str[200];
	int x1, y1, x2, y2;
}SV;

static void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer user_data);
static gboolean draw(GtkWidget *widget, cairo_t *new_cr, gpointer user_data);
//////////////////////////////////////////////////////////////////////

//////////////////// global variables //////////////////////////////////
int MAX_LABEL;
int temp;
gboolean supports_alpha; //false null null
SV* s_ptr;
int* num_ptr;

GtkWidget* fixed_container;
GtkWidget** label;
////////////////////////////////////////////////////////////////////////

/////////////////// output class ////////////////////////////

class output{
public:
    GtkWidget *window;

    void output_init(SV* struct_ptr, int* int_ptr);
    // void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer user_data);
    // gboolean draw(GtkWidget *window, cairo_t *cr, gpointer userdata);
};

//////////////////////////////////////////////////////////////

#endif