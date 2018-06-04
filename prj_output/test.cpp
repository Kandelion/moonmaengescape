 #include <gtk/gtk.h>

    int main(int argc, char *argv[])
    {
        GtkWidget *window;

        gtk_init (&argc, &argv);

        window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        gtk_window_resize(GTK_WINDOW(window), 100, 100);
        gtk_widget_show (window);

        gtk_main ();
    }