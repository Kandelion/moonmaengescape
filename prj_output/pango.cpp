#include <gtk/gtk.h>


/*
        gtk_widget_modify_font
        This's the simpliest way to change the label's font :)
*/
static void font_set_way0(GtkEntry *entry, gpointer data)
{
GtkLabel                *label;
PangoFontDescription    *pfd;

        g_return_if_fail(GTK_IS_ENTRY(entry));
        g_return_if_fail(GTK_IS_LABEL(data));

        label = GTK_LABEL(data);

        /* creating PangoFontDescription from string, specified in entry */
        pfd = pango_font_description_from_string(gtk_entry_get_text(entry));
        /* setting label's font */
        gtk_widget_modify_font(GTK_WIDGET(label), pfd);
        /* freeing PangoFontDescription, cause it has been copied by prev. call */
        pango_font_description_free(pfd);
}
/*
        Setting up widgets: setup_way[01234]
*/
static void setup_way0(GtkBox *box)
{
char      *font;
GtkWidget *hbox;
GtkWidget *entry;
GtkWidget *label;

        hbox = gtk_hbox_new(FALSE, 4);
        gtk_box_pack_start(box, hbox, TRUE,TRUE, 0);

        label = gtk_label_new("Font name");
        gtk_box_pack_start(GTK_BOX(hbox), label, FALSE,FALSE, 0);

        entry = gtk_entry_new();
        gtk_entry_set_width_chars(GTK_ENTRY(entry), 10);
        gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE,FALSE, 0);

        label = gtk_label_new(" 0. The font of this label is changing via gtk_widget_modify_font ");
        gtk_box_pack_start(GTK_BOX(hbox), label, TRUE,TRUE, 0);

        font = pango_font_description_to_string(
                pango_context_get_font_description(
                        gtk_widget_get_pango_context(label)
                )
        );
        gtk_entry_set_text(GTK_ENTRY(entry), font);
        g_free(font);
        g_signal_connect(G_OBJECT(entry), "activate", G_CALLBACK(font_set_way0), (gpointer)label);
}

int main(int argc, char **argv)
{
        GtkWidget *window;
        GtkWidget *vbox;
        GtkWidget *label;
        GtkWidget *button;
        GtkWidget *sep;

        gtk_init(&argc, &argv);

        /* process rc file, contains the font description */
        gtk_rc_parse("fonts.rc");

        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_container_set_border_width(GTK_CONTAINER(window), 8);
        g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(gtk_main_quit), NULL);

        vbox = gtk_vbox_new(FALSE, 2);
        gtk_container_add(GTK_CONTAINER(window), vbox);

        label = gtk_label_new("Type font description in entry and press <Enter>");
        gtk_box_pack_start(GTK_BOX(vbox), label, TRUE,TRUE, 4);

        sep = gtk_hseparator_new();
        gtk_box_pack_start(GTK_BOX(vbox), sep, TRUE,TRUE, 4);

        setup_way0(GTK_BOX(vbox));

        sep = gtk_hseparator_new();
        gtk_box_pack_start(GTK_BOX(vbox), sep, TRUE,TRUE, 4);

        button = gtk_button_new_with_label(" QuIt ");
        gtk_box_pack_start(GTK_BOX(vbox), button, TRUE,TRUE, 0);
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(gtk_main_quit), NULL);

        gtk_widget_show_all(window);
        
        gtk_main();

        return 0;
}
