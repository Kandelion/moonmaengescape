#include "output.hpp"

//////////////////// global variables //////////////////////////////////
int MAX_LABEL;
int temp;
gboolean supports_alpha; //false null null
SV* s_ptr;
int* num_ptr;
int pre_num;

GtkWidget* window;
GtkWidget* fixed_container;
GtkWidget** label;
////////////////////////////////////////////////////////////////////////

static void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer userdata)
{
    // To check if the display supports alpha channels, get the visual 
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

    printf("screen changed ! \n");
    gtk_widget_set_visual(widget, visual);
}

static gboolean draw(GtkWidget *window, cairo_t *cr, gpointer userdata)
{
   cairo_t *new_cr = gdk_cairo_create(gtk_widget_get_window(window));
   char str_tmp[300] = { '0', };
   char font_color[20] = "RED";
   char bg_color[20] = "#00FF007F";
   char font_size[20] = "10";

    if (supports_alpha)
    {
        // r g b 투명도
        cairo_set_source_rgba (new_cr, 0.0, 0.0, 0.0, 0.0); // transparent 
    }
    else
    {
        cairo_set_source_rgb (new_cr, 1.0, 1.0, 1.0); // opaque white 
    }

    
    // draw the background //
    cairo_set_operator (new_cr, CAIRO_OPERATOR_SOURCE);
    cairo_paint (new_cr);
    cairo_destroy(new_cr);

    ///////////////////////////////////////////////////////////////////////////

    printf("drawing Start ! \n");
            // for testing.
            strcpy(str_tmp, "<span foreground=\"");
            strcat(str_tmp, font_color);
            strcat(str_tmp, "\" background=\"");
            strcat(str_tmp, bg_color);
            strcat(str_tmp, "\" font=\"");
            strcat(str_tmp, font_size);
            strcat(str_tmp, "\"><b>");
            strcat(str_tmp, "test");
            strcat(str_tmp, "</b></span>");
    
            //printf("%s\n", str_tmp);
    
    
    /*
    //  merge all 사용시 이 부분 사용.
    if(!num_ptr) {
        int check_length = (*num_ptr) > pre_num ? *num_ptr : pre_num;
        for(int i = 0; i < check_length; i++) {
                // 새로 변경된 텍스트 갱신
            if(i < *num_ptr) {
                //gtk_label_set_markup(GTK_LABEL(label[i]), data);
                strcpy(str_tmp, "<span foreground=\"");
                strcat(str_tmp, font_color);
                strcat(str_tmp, "\" background=\"");
                strcat(str_tmp, bg_color);
                strcat(str_tmp, "\" font=\"");
                strcat(str_tmp, font_size);
                strcat(str_tmp, "\"><b>");
                strcat(str_tmp, s_ptr[i].str);
                strcat(str_tmp, "</b></span>");

                //gtk_label_set_markup(GTK_LABEL(label[i]), "<span foreground=\"red\" background=\"#00FF007F\" font=\"30.5\"><b>Test Text 1</b></span>");
                gtk_label_set_markup(GTK_LABEL(label[i]), str_tmp);
                gtk_fixed_move (GTK_FIXED(fixed_container), label[i], s_ptr[i].x1, s_ptr[i].y1);
            }
                // 갱신됨으로써 지워져야 할 텍스트들 초기화.
            else {
                gtk_fixed_move (GTK_FIXED(fixed_container), label[i], 5000, 5000);
            }
        }
        pre_num = *num_ptr;
    }
    */
    
        
    gtk_label_set_markup(GTK_LABEL(label[0]), str_tmp);
    gtk_fixed_move (GTK_FIXED(fixed_container), label[0], temp, 500);

    temp += 100;
    if( temp > 1000 ) temp = 0;

    //printf("drawing End.\n");

    sleep(1);

    return FALSE;
}

void output::output_init(SV* struct_ptr, int* int_ptr) { // class에 구현할 아웃푸웃
    temp = 0;
    MAX_LABEL = 2000;
    s_ptr = NULL;
    num_ptr = NULL;
    supports_alpha = false;
    pre_num = 0;

        // pointer fetching.
    s_ptr = struct_ptr;
    num_ptr = int_ptr;
    
    gtk_init(NULL, NULL);

        // window init setting.
    printf("start initializing the gtk. \n");
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    printf("error check 1\n");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    printf("error check 2\n");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);
    printf("error check 3\n");
    gtk_window_set_title(GTK_WINDOW(window), "MoonMaengEscape !");
    g_signal_connect(G_OBJECT(window), "delete-event", gtk_main_quit, NULL);

    gtk_widget_set_app_paintable(window, TRUE);

    g_signal_connect(G_OBJECT(window), "draw", G_CALLBACK(draw), NULL);
    g_signal_connect(G_OBJECT(window), "screen_changed", G_CALLBACK(screen_changed), NULL);
    
    fixed_container = gtk_fixed_new();
    
    label = (GtkWidget **)malloc(sizeof(GtkWidget*) * MAX_LABEL);
    for(int i=0; i< MAX_LABEL; i++) {
        label[i] = gtk_label_new(NULL);
        gtk_fixed_put (GTK_FIXED (fixed_container), label[i], 0, 0); 
    }
    gtk_container_add(GTK_CONTAINER(window), fixed_container);
    
    screen_changed(window, NULL, NULL);
    gtk_window_fullscreen((GtkWindow*)window);

    gtk_widget_show_all(window);
    gtk_main();
}