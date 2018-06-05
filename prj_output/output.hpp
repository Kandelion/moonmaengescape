#include <gtk/gtk.h>
#include<stdio.h>
#include<stdlib.h>

static void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer user_data);
static gboolean draw(GtkWidget *widget, cairo_t *new_cr, gpointer user_data);


int MAX_LABEL = 2000;

GtkWidget* fixed_container;
GtkWidget** label;
char data[10] = "TEST BOY";
int temp = 0;
gboolean supports_alpha = FALSE;