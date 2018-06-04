#include <gtk/gtk.h>
  /*
   * GtkFixed를 Global로 선언한다.
   * Callback 함수에서 여러개의 Widget을 사용할 일이 있어서이다.
   * 이는 단순한 예제를 위하여 사용하는것이니 Global은 가급적 삼가토록 한다.
   * Callback에서 여러개의 Widget을 가져오는 방법은 후에 여러가지를 알려주겠다.
   */
  GtkWidget *fixed = NULL;
  // Window의 'destroy' Signal 발생시 호출될 Callback 함수
  void
  cb_window_destroy (GtkWidget *widget, gpointer data)
  {
    // Main Event Loop 종료 (프로그램의 종료)
    gtk_main_quit ();
  }
  // Button1의 'clicked' Signal 발생시 호출될 Callback함수
  gboolean
  cb_button1_clicked (GtkWidget *widget, gpointer data)
  {
    // g_signal_connect에서 넘어온 사용자 데이터(Button2)를 GtkWidget의 포인터로 타입 캐스팅
    GtkWidget *button = (GtkWidget *) data;
    /*
     * GtkWidget의 크기를 변경하는 함수
     * 넓이는 50으로 변경하고 높이는 변경하지 않는다.
     * 넓이와 높이의 값이 -1이면 변경하지 않는다
     */
    gtk_widget_set_size_request (button, 50, -1);
    /*
     * 반환값이 없다. default handler는 무조건 호출된다.
     */
  }
  // Button2의 'clicked' Signal 발생시 호출될 Callback함수
  gboolean
  cb_button2_clicked (GtkWidget *widget, gpointer data)
  {
    // g_signal_connect에서 넘어온 사용자 데이터(entry)를 GtkWidget의 포인터로 타입 캐스팅
    GtkWidget *entry = (GtkWidget *) data;
    /*
     * GtkFixed내에 포함된 Widget의 위치를 이동시키는 함수
     * fixed는 위에서 선언한 글로벌 변수이다.
     */
    gtk_fixed_move (GTK_FIXED (fixed), entry, 10, 50);
    // GtkEntry의 Text를 변경하는 함수
    gtk_entry_set_text (GTK_ENTRY (entry), "오!! Entry의 텍스트가 바꼈습니다.");
    /*
     * 반환값이 없다. default handler는 무조건 호출된다.
     */
  }
  // entry의 'activate' Signal 발생시 호출될 Callback함수
  void
  cb_entry_activate (GtkWidget *widget, gpointer data)
  {
    // g_signal_connect에서 넘어온 사용자 데이터(label)를 GtkWidget의 포인터로 타입 캐스팅
    GtkWidget *label = (GtkWidget *) data;
    // 자기 자신(entry)의 Text를 가져온다.
    const gchar *entry_text = gtk_entry_get_text (GTK_ENTRY (widget));
    // label의 Text를 entry의 Text롤 변경한다.
    gtk_label_set_text (GTK_LABEL (label), entry_text);
    /*
     * 반환값이 없다. default handler는 무조건 호출된다.
     */
  }
  int
  main (int argc, char *argv[])
  {
    // 대부분 Widget의 생성후 반환값 형식은 GtkWidget이므로 GtkWidget의 포인터로 변수 선언
    GtkWidget *window = NULL;
    GtkWidget *label = NULL;
    GtkWidget *entry = NULL;
    GtkWidget *button1 = NULL;
    GtkWidget *button2 = NULL;
    gtk_init (&argc, &argv);
    // 기본 Window(GtkWindow) 생성
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    /*
     * Label(GtkLabel) 생성
     */
    label = gtk_label_new ("Hi 똘츄~");
    /*
     * label의 최소 크기를 변경한다.
     * GtkFixed내에 포함되는 Widget들은 왠만하면 지정해주는것이 좋다.
     * 높이는 기본크기 사용
     */
    gtk_widget_set_size_request(label, 100, -1);
    gtk_widget_show (label);
    /*
     * Entry(GtkEntry) 생성
     */
    entry = gtk_entry_new ();
    /*
     * entry의 최소 크기를 변경한다.
     * GtkFixed내에 포함되는 Widget들은 왠만하면 지정해주는것이 좋다.
     * 높이는 기본크기 사용
     */
    gtk_widget_set_size_request(entry, 150, -1);
    gtk_widget_show (entry);
    /*
     * Button1(GtkButton) 생성
     * 생성과 label변경을 한번에 처리할 수 있는 gtk_button_new_with_label 함수를 썼다.
     */
    button1 = gtk_button_new_with_label ("Button1");
    /*
     * Button1의 최소 크기를 변경한다.
     * GtkFixed내에 포함되는 Widget들은 왠만하면 지정해주는것이 좋다.
     * 높이는 기본크기 사용
     */
    gtk_widget_set_size_request(button1, 70, -1);
    gtk_widget_show (button1);
    /*
     * Button2(GtkButton) 생성
     * 생성과 label변경을 한번에 처리할 수 있는 gtk_button_new_with_label 함수를 썼다.
     */
    button2 = gtk_button_new_with_label ("Button2");
    /*
     * Button2의 최소 크기를 변경한다.
     * GtkFixed내에 포함되는 Widget들은 왠만하면 지정해주는것이 좋다.
     */
    gtk_widget_set_size_request(button2, 100, 100);
    gtk_widget_show (button2);
    /*
     * Fixed(GtkFixed) 생성
     * fixed변수는 최상단에 Global로 선언
     */
    fixed = gtk_fixed_new ();
    gtk_widget_show (fixed);
    /*
     * fixed의 최소 크기를 변경한다.
     * gtk_widget_set_size_request는 GtkFixed내에 포함된 Widget에만 국한된것이 아니다.
         어느 Widget이든 원하면 지정할 수 있다.
     */
    gtk_widget_set_size_request (fixed, 300, 300);
    // 기본 Window에 Fixed를 넣어준다.(GtkContainer에 대해서는 이미 설명하였으므로 생략한다)
    gtk_container_add (GTK_CONTAINER (window), fixed);
    /*
     * GtkFixed에 label을 child widget으로 포함시킨다.
     * 가로 위치 10 pixel, 세로 위치 10 pixel이다.
     */
    gtk_fixed_put (GTK_FIXED (fixed), label, 10, 10); 
    /*
     * GtkFixed에 entry를 child widget으로 포함시킨다.
     * 가로 위치 120 pixel, 세로 위치 50 pixel이다.
     */
    gtk_fixed_put (GTK_FIXED (fixed), entry, 120, 50); 
    /*
     * GtkFixed에 Button1을 child widget으로 포함시킨다.
     * 가로 위치 20 pixel, 세로 위치 150 pixel이다.
     */
    gtk_fixed_put (GTK_FIXED (fixed), button1, 20, 150);
    
    /*
     * GtkFixed에 Button2을 child widget으로 포함시킨다.
     * 가로 위치 70 pixel, 세로 위치 160 pixel이다.
     */
    gtk_fixed_put (GTK_FIXED (fixed), button2, 70, 160);
    // Signal 연결에 대해서는 전장인 "Signal & Callback & Handler"에서 설명하였다
    // 기본 Window의 X 버튼 클릭시 실행할 Callback 함수 연결
    g_signal_connect (G_OBJECT (window), "destroy",
                    G_CALLBACK (cb_window_destroy), NULL);
    /*
     * entry에서 Enter를 입력하였을때 실행할 Callback 함수 연결
     * 사용자 데이터로 마지막 파라미터에 label(포인터)를 넘긴다.
     */
    g_signal_connect (G_OBJECT (entry), "activate",
                    G_CALLBACK (cb_entry_activate), label);
    /*
     * Button1을 마우스 버튼으로 클릭했을때 실행할 Callback 함수 연결
     * 사용자 데이터로 마지막 파라미터에 button2(포인터)를 넘긴다.
     */
    g_signal_connect (G_OBJECT (button1), "clicked",
                    G_CALLBACK (cb_button1_clicked), (gpointer) button2);
    /*
     * Button2를 마우스 버튼으로 클릭했을때 실행할 Callback 함수 연결
     * 사용자 데이터로 마지막 파라미터에 entry(포인터)를 넘긴다.
     */
    g_signal_connect (G_OBJECT (button2), "clicked",
                    G_CALLBACK (cb_button2_clicked), (gpointer) entry);
    // Window를 화면에 표시한다.
    gtk_widget_show (window);
    /*
    * Main Event Loop 생성 및 실행
    * gtk_main_quit 함수가 호출될때까지 다음 문장으로 진입할 수 없다.
    * 실질적으로 이때 화면상에 UI가 표시된다.
    */
    gtk_main ();
    // gtk_main_quit 함수가 호출되면 여기로 진입하게 된다.
    return 0;
  }