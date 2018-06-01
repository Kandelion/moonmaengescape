#include <gtk/gtk.h>

static void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer user_data);
static gboolean draw(GtkWidget *widget, cairo_t *new_cr, gpointer user_data);
static void clicked(GtkWindow *win, GdkEventButton *event, gpointer user_data);

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *text;

    /*
    GtkWidget *entry;

    gtk_window_set_title(GTK_WINDOW (window), "GTK Entry");
    gtk_signal_connect(G_OBJECT (window), "delete_event",
                       (GtkSignalFunc) gtk_exit, NULL);
    /////////////////////////////////////////////////////////////////////////

    entry = gtk_entry_new_with_max_length (50);
    gtk_signal_connect(G_OBJECT(entry), "activate",
                       GTK_SIGNAL_FUNC(enter_callback),
                       entry);
    gtk_entry_set_text (GTK_ENTRY (entry), "hello");
    gtk_entry_append_text (GTK_ENTRY (entry), " world");
    gtk_entry_select_region (GTK_ENTRY (entry),
                             0, GTK_ENTRY(entry)->text_length);
    gtk_widget_show (entry);
    */

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);
    gtk_window_set_title(GTK_WINDOW(window), "Alpha Demo");
    g_signal_connect(G_OBJECT(window), "delete-event", gtk_main_quit, NULL);

    gtk_widget_set_app_paintable(window, TRUE);

    g_signal_connect(G_OBJECT(window), "draw", G_CALLBACK(draw), NULL);
    g_signal_connect(G_OBJECT(window), "screen-changed", G_CALLBACK(screen_changed), NULL);

    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
    gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);
    g_signal_connect(G_OBJECT(window), "button-press-event", G_CALLBACK(clicked), NULL);

    GtkWidget* fixed_container = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed_container);
    GtkWidget* button = gtk_button_new_with_label("button1");
    gtk_widget_set_size_request(button, 100, 100);

    /* Create the GtkText widget */
    /*
    text = gtk_text_new (NULL, NULL);
    gtk_text_set_editable (GTK_TEXT (text), TRUE);
    gtk_table_attach (GTK_TABLE (table), text, 0, 1, 0, 1,
                    GTK_EXPAND | GTK_SHRINK | GTK_FILL,
                    GTK_EXPAND | GTK_SHRINK | GTK_FILL, 0, 0);
    gtk_widget_show (text);
    */
    
    gtk_container_add(GTK_CONTAINER(fixed_container), button);

    screen_changed(window, NULL, NULL);
    gtk_window_fullscreen((GtkWindow*)window);

    gtk_widget_show_all(window);
    gtk_main();

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
        cairo_set_source_rgba (new_cr, 0.0, 0.0, 0.0, 0.5); /* transparent */
    }
    else
    {
        cairo_set_source_rgb (new_cr, 1.0, 1.0, 1.0); /* opaque white */
    }

    /* draw the background */
    cairo_set_operator (new_cr, CAIRO_OPERATOR_SOURCE);
    cairo_paint (new_cr);

    cairo_destroy(new_cr);

    return FALSE;
}

static void clicked(GtkWindow *win, GdkEventButton *event, gpointer user_data)
{
    /* toggle window manager frames */
    gtk_window_set_decorated(win, !gtk_window_get_decorated(win));
} 