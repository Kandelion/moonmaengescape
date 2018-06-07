#include "output.hpp"

#define SV_SIZE 50

void init_Msg();
void receiveMsg(SV *receive_data, int *numsv_);

//////////////////// global variables //////////////////////////////////
int MAX_LABEL;
int temp;
gboolean supports_alpha; //false null null
SV s_ptr[SV_SIZE];
int numsv;
int pre_num;

GtkWidget* window;
GtkWidget* fixed_container;
GtkWidget** label;

///// by khw /////
struct my_msgbuf
{
    long msgtype;
    SV data[SV_SIZE];
    int numsv;
    int dummy[2];
};
key_t key_id;
struct my_msgbuf mybuf;
/////////////////
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
   char font_color[20] = "WHITE";
   char bg_color[20] = "#00000090";
   char font_size[20] = "20";
   int y_tmp;

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
    
    //printf("drawing!\n");
    numsv = 0;
    receiveMsg(s_ptr, &numsv);
    //printf("data receive!\n");
    
    //  merge all 사용시 이 부분 사용.
    if(numsv > 0) {
        //printf("numsv : %d\n", numsv);
        printf("y1 : %d , y2 : %d\n", s_ptr[0].y1, s_ptr[0].y2);
        printf("font size : %d\n", (s_ptr[0].y2 - s_ptr[0].y1));
        int check_length = numsv > pre_num ? numsv : pre_num;
        for(int i = 0; i < check_length; i++) {
                // 새로 변경된 텍스트 갱신
            if(i < numsv) {
                //gtk_label_set_markup(GTK_LABEL(label[i]), data);
                strcpy(str_tmp, "<span foreground=\"");
                strcat(str_tmp, font_color);
                strcat(str_tmp, "\" background=\"");
                strcat(str_tmp, bg_color);
                strcat(str_tmp, "\" font=\"");

                sprintf(font_size, "%d", (int)((double)((s_ptr[i].y2 - s_ptr[i].y1)) * 0.9));
                printf("%s\n", font_size);
                strcat(str_tmp, font_size);
                strcat(str_tmp, "\"><b>");
                strcat(str_tmp, s_ptr[i].str);
                strcat(str_tmp, "</b></span>");

                //gtk_label_set_markup(GTK_LABEL(label[i]), "<span foreground=\"red\" background=\"#00FF007F\" font=\"30.5\"><b>Test Text 1</b></span>");
                gtk_label_set_markup(GTK_LABEL(label[i]), str_tmp);
                y_tmp = s_ptr[i].y1;
                if(s_ptr[i].y1 > 10) y_tmp -= 10; 
                gtk_fixed_move (GTK_FIXED(fixed_container), label[i], s_ptr[i].x1, s_ptr[i].y1 - 10);
            }
                // 갱신됨으로써 지워져야 할 텍스트들 초기화.t
            else {
                gtk_label_set_markup(GTK_LABEL(label[i]), "");
                //gtk_fixed_move (GTK_FIXED(fixed_container), label[i], 5000, 5000);
            }
        }
        pre_num = numsv;
    }

    //printf("drawing End.\n");
    gtk_fixed_move (GTK_FIXED(fixed_container), label[1500], 5000, 5000); // 호출이 없을 시에 draw 지속 호출을 위한 더미.

    //sleep(1);
    
    return FALSE;
}

void output::output_init(SV* struct_ptr, int* int_ptr) { // class에 구현할 아웃푸웃
    temp = 0;
    MAX_LABEL = 2000;
    supports_alpha = false;
    pre_num = 0;

    numsv = 0;
    
    init_Msg();
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
    printf("almost done.\n");
    gtk_main();
}


//////////////// Init MSG queue /////////////////
void init_Msg(){
    key_id = msgget((key_t)1234, IPC_CREAT|0666);
    if (key_id == -1)
    {
        perror("msgget error : ");
        exit(0);
    }
}
//////////////// Init MSG queue /////////////////



//////////////// Receive MSG queue /////////////////
void receiveMsg(SV *receive_data, int *numsv_){
    struct my_msgbuf temp_buf;
    int flag=0, rcv_result=0;

    //get data from queue.
    rcv_result = msgrcv( key_id, (void *)&temp_buf, sizeof(temp_buf) - 8, 1, IPC_NOWAIT | MSG_NOERROR);

    if(rcv_result != -1){
        //printf("Copy to local\n");
        memcpy(receive_data, temp_buf.data, sizeof(SV) * (SV_SIZE));
        *numsv_ = temp_buf.numsv;
        //printf("rcv_done : %s, %d\n", temp_buf.data[0].str, temp_buf.numsv);
    }
    else{
        //printf("Nothing to rcv\n");
    }
}
//////////////// Receive MSG queue /////////////////
