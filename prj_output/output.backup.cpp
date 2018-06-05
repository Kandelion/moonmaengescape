#include <gtk/gtk.h>

static void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer user_data);
static gboolean draw(GtkWidget *widget, cairo_t *new_cr, gpointer user_data);
void init_output(void) {

}

int main(int argc, char **argv)
{
    printf("argc : %d\n", argc);
    gtk_init(NULL, NULL);


        // window init setting.
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);
    gtk_window_set_title(GTK_WINDOW(window), "MoonMaengEscape !");
    g_signal_connect(G_OBJECT(window), "delete-event", gtk_main_quit, NULL);

    gtk_widget_set_app_paintable(window, TRUE);

    g_signal_connect(G_OBJECT(window), "draw", G_CALLBACK(draw), NULL);
    g_signal_connect(G_OBJECT(window), "screen-changed", G_CALLBACK(screen_changed), NULL);

        // for freely expressing, use fixed.

    GtkWidget* fixed_container = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed_container);

        // button test.

    GtkWidget* button = gtk_button_new_with_label("Button Test");
    gtk_widget_set_size_request(button, 100, 100);   
    gtk_fixed_put (GTK_FIXED (fixed_container), button, 1080, 720); 
    //gtk_container_add(GTK_CONTAINER(fixed_container), button);


        // label test. pango markup language use. color, fontsize setting.

    GtkWidget* label;
    label = gtk_label_new (NULL);
    //gtk_label_set_text (GTK_LABEL (label), "Label Input String");
    gtk_label_set_markup(GTK_LABEL(label), "<span foreground=\"red\" background=\"#00FF007F\" font=\"30.5\"><b>Test Text 1</b></span>");
    //gtk_widget_set_size_request(label, 1, -1);
    //gtk_container_add(GTK_CONTAINER(fixed_container), label);
    gtk_fixed_put (GTK_FIXED (fixed_container), label, 30, 320); 


        // label test. pango markup language use. color, fontsize setting.

    GtkWidget* label2;
    label2 = gtk_label_new (NULL);
    //gtk_label_set_text (GTK_LABEL (label2), "YELLOW Input String");
    gtk_label_set_markup(GTK_LABEL(label2), "<span foreground=\"blue\" font=\"20.5\">Input Text</span> is <i><span font=\"50\">cool</span></i>!");
    gtk_fixed_put (GTK_FIXED (fixed_container), label2, 430, 120); 

        // entry widget test.
  
    GtkWidget* entry = gtk_entry_new ();
  
    gtk_widget_set_size_request(entry, 100, -1);
    gtk_entry_set_text (GTK_ENTRY (entry), "Entry Input Test");
    gtk_fixed_put (GTK_FIXED (fixed_container), entry, 580, 120); 
    //gtk_container_add(GTK_CONTAINER(fixed_container), entry);

    printf("Output End1.\n");

    screen_changed(window, NULL, NULL);
    gtk_window_fullscreen((GtkWindow*)window);

    printf("Output End2.\n");

    gtk_widget_show_all(window);
    printf("Output End3.\n");
    gtk_entry_set_text (GTK_ENTRY (entry), "Entry Input Test tttttttttttttt");

    gtk_main();

    printf("Output End4.\n");
    return 0;
}

gboolean supports_alpha = FALSE;
static void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer userdata)
{
    /* To check if the display supports alpha channels, get the visual */
    GdkScreen *screen = gtk_widget_get_screen(widget);
    GdkVisual *visual = gdk_screen_get_rgba_visual(screen);

    if (!visual)
    {
        printf("Your screen does not support alpha channels!\n");
        visual = gdk_screen_get_system_visual(screen);
        supports_alpha = FALSE;
    }
    else
    {
        printf("Your screen supports alpha channels!\n");
        supports_alpha = TRUE;
    }

    gtk_widget_set_visual(widget, visual);
}

static gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer userdata)
{
   cairo_t *new_cr = gdk_cairo_create(gtk_widget_get_window(widget));
   
    if (supports_alpha)
    {
        // r g b 투명도
        cairo_set_source_rgba (new_cr, 0.0, 0.0, 0.0, 0.0); /* transparent */
    }
    else
    {
        cairo_set_source_rgb (new_cr, 1.0, 1.0, 1.0); /* opaque white */
    }
    printf("drawing\n");
    
    /* draw the background */
    cairo_set_operator (new_cr, CAIRO_OPERATOR_SOURCE);
    cairo_paint (new_cr);

    cairo_destroy(new_cr);

    return FALSE;
}

