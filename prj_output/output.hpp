#include <Python.h>
#include <gtk/gtk.h>
#include<stdio.h>
#include<stdlib.h>

static void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer user_data);
static gboolean draw(GtkWidget *widget, cairo_t *new_cr, gpointer user_data);


int MAX_LABEL = 2000;

GtkWidget* fixed_container;
GtkWidget** label;
char * data = "youhoo";

int temp = 0;


#define DEBUG 0         //set 1 to print log on console.

class ocr_vision{
private:
    void get_append_path(char *dest);

public:
    void detect_text(char * result, int result_size, const char* filepath, const char* pythonname);
};
