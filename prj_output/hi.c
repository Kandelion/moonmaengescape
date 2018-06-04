#include <gtk/gtk.h>

  // Window의 'destroy' Signal 발생시 호출될 Callback 함수
  void
  cb_window_destroy (GtkWidget *widget, gpointer data)
  {
    // Main Event Loop 종료 (프로그램의 종료)
    gtk_main_quit ();
  }
  // Button의 'button_press_event' Signal 발생시 호출될 Callback함수
  gboolean
  cb_button_press_event (GtkWidget *widget, GdkEventButton *event, gpointer data)
  {
    gtk_button_set_label (GTK_BUTTON (widget), "Button을 마우스로 눌렀습니다.");
    return FALSE;
    /*
     * 반환값은 FALSE가 기본이다. 이걸 TRUE로 반환한다면 default handler는 호출되지 않는다.
     * 강좌를 순서대로 쭉 봐왔다면 이것이 어떤 의미가 있는것인지 알것이다.
     * 만약 잘 모르겠다면 바로 전 장인 'Signal &amp; Callback &amp; Handler'를 다시 보라.
     * 잘차려진 밥상은 아니더라도 밥상 차린 사람의 성의를 생각해 천천히 꼭꼭 씹어먹기 바란다.
     */
  }
  int
  main (int argc, char *argv[])
  {
    // 대부분 Widget의 생성후 반환값 형식은 GtkWidget이므로 GtkWidget의 포인터로 변수 선언
    GtkWidget *window = NULL;
    GtkWidget *button = NULL;
    gtk_init (&argc, &argv);
    // 기본 Window(GtkWindow) 생성
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    /*
    * Button(GtkButton) 생성 및 Label 변경
    * 생성과 label변경을 한번에 처리할 수도 있겠으나 이해를 돕기위해 나누었다.
    * 아래의 두가지는 'button = gtk_button_new_with_label ("Hi 똘츄~");' 로 합쳐도 된다.
    */
    button = gtk_button_new ();
    gtk_button_set_label (GTK_BUTTON (button), "Hi 똘츄~");
    // 기본 Window에 Button을 넣어준다.(GtkContainer에 대해서는 이미 설명하였으므로 생략한다)
    gtk_container_add (GTK_CONTAINER (window), button);
    // Signal 연결에 대해서는 전장인 "Signal &amp; Callback &amp; Handler"에서 설명하였다
    // 기본 Window의 X 버튼 클릭시 실행할 Callback 함수 연결
    g_signal_connect (G_OBJECT (window), "destroy",
                    G_CALLBACK (cb_window_destroy), NULL);
    // Button을 마우스 버튼으로 눌렀을때 실행할 Callback 함수 연결
    g_signal_connect (G_OBJECT (button), "button_press_event",
                    G_CALLBACK (cb_button_press_event), NULL);
    // Button과 Window를 화면에 표시한다.
    gtk_widget_show (button);
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