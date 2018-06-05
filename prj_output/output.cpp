#include "output.hpp"

int main(int argc, char **argv)
{
    
    gtk_init(&argc, &argv);
    fixed_container = gtk_fixed_new();

    label = (GtkWidget **)malloc(sizeof(GtkWidget*) * MAX_LABEL);
    for(int i=0; i< MAX_LABEL; i++) {
        label[i] = gtk_label_new(NULL);
        gtk_fixed_put (GTK_FIXED (fixed_container), label[i], 0, 0); 
    }
    
        // window init setting.
    printf("start initializing the gtk. \n");
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);
    gtk_window_set_title(GTK_WINDOW(window), "MoonMaengEscape !");
    g_signal_connect(G_OBJECT(window), "delete-event", gtk_main_quit, NULL);

    gtk_widget_set_app_paintable(window, TRUE);

    gtk_container_add(GTK_CONTAINER(window), fixed_container);

    g_signal_connect(G_OBJECT(window), "draw", G_CALLBACK(draw), NULL);
    g_signal_connect(G_OBJECT(window), "screen-changed", G_CALLBACK(screen_changed), NULL);


    screen_changed(window, NULL, NULL);
    gtk_window_fullscreen((GtkWindow*)window);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}


static void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer userdata)
{
    /* To check if the display supports alpha channels, get the visual */
    GdkScreen *screen = gtk_widget_get_screen(widget);
    GdkVisual *visual = gdk_screen_get_rgba_visual(screen);

    if (!visual)
    {
        //printf("Your screen does not support alpha channels!\n");
        visual = gdk_screen_get_system_visual(screen);
        supports_alpha = FALSE;
    }
    else
    {
        //printf("Your screen supports alpha channels!\n");
        supports_alpha = TRUE;
    }

    gtk_widget_set_visual(widget, visual);
}

static gboolean draw(GtkWidget *window, cairo_t *cr, gpointer userdata)
{
   cairo_t *new_cr = gdk_cairo_create(gtk_widget_get_window(window));

    if (supports_alpha)
    {
        // r g b 투명도
        cairo_set_source_rgba (new_cr, 0.0, 0.0, 0.0, 0.0); /* transparent */
    }
    else
    {
        cairo_set_source_rgb (new_cr, 1.0, 1.0, 1.0); /* opaque white */
    }

    
    /* draw the background */
    cairo_set_operator (new_cr, CAIRO_OPERATOR_SOURCE);
    cairo_paint (new_cr);

    cairo_destroy(new_cr);

    ///////////////////////////////////////////////////////////////////////////

    printf("drawing Start ! \n");

    for(int i=0; i<MAX_LABEL; i++) {
        //gtk_label_set_markup(GTK_LABEL(label[i]), data);
        gtk_label_set_markup(GTK_LABEL(label[i]), "<span foreground=\"red\" background=\"#00FF007F\" font=\"30.5\"><b>Test Text 1</b></span>");
        gtk_fixed_move (GTK_FIXED(fixed_container), label[i], 10+temp, i/2);
    }
    
    if( temp++ > 1000 ) temp = 0;

    printf("drawing End.\n");

    sleep(1);

    return FALSE;
}

