#include <gtk/gtk.h>
void cw_new(GtkWidget *newMi, gpointer data) {
	printf("new clicked\n");
}
void cw_open(GtkWidget *openMi, gpointer data) {
	printf("open clicked\n");
}
void cw_save(GtkWidget *saveMi, gpointer data) {
	printf("save clicked\n");
}
void cw_saveas(GtkWidget *saveasMi, gpointer data) {
	printf("saveas clicked\n");
}
static gboolean cw_delete(GtkWidget *window, gpointer data) {
	gtk_main_quit();
	return FALSE;
}
GdkPixbuf *create_pixbuf(const gchar * filename) {
	GdkPixbuf *pixbuf;
	GError *error = NULL;
    	pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    	if(!pixbuf) {
      		fprintf(stderr, "%s\n", error->message);
       		g_error_free(error);
    	}
  	return pixbuf;
}

int main( int argc, char *argv[]) {
   	GtkWidget *window;

	GtkWidget *box;
	GtkWidget *menubar;
	GtkWidget *fileMenu;
	GtkWidget *fileMi;
	GtkWidget *openMi;
	GtkWidget *saveMi;
	GtkWidget *saveasMi;
	GtkWidget *quitMi;
	GtkWidget *newMi;

	GtkWidget *table;
	GtkWidget *wins;
	
	GtkWidget *drawingarea;
	GtkWidget *event_box;
	
	GtkWidget *toolbar;
	GtkWidget *frame;
	GtkWidget *label;
	GtkToolItem *newTb;
	GtkToolItem *openTb;
	GtkToolItem *saveTb;
	
	gtk_init(&argc, &argv);
	
	/***************************window and icon****************************/
   	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   	gtk_window_set_title(GTK_WINDOW(window), "Logic Gate Simulator");
   	gtk_window_set_default_size(GTK_WINDOW(window), 1500, 1500);
   	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
   	gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("icon.png"));
   	
	/***************************box and menubar***************************/
	box = gtk_box_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), box);
	menubar = gtk_menu_bar_new();
	fileMenu = gtk_menu_new();

	fileMi = gtk_menu_item_new_with_label("File");
	openMi = gtk_menu_item_new_with_label("Open");
	saveMi = gtk_menu_item_new_with_label("Save");
	saveasMi = gtk_menu_item_new_with_label("Save as");
	quitMi = gtk_menu_item_new_with_label("Quit");
	newMi = gtk_menu_item_new_with_label("New");

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), newMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), openMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), saveMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), saveasMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);
	gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 0);
	
	/**************************call back functions**************************/
	g_signal_connect(G_OBJECT(newMi), "activate", G_CALLBACK(cw_new), NULL);
	g_signal_connect(G_OBJECT(openMi), "activate", G_CALLBACK(cw_open), NULL);
	g_signal_connect(G_OBJECT(saveMi), "activate", G_CALLBACK(cw_save), NULL);
	g_signal_connect(G_OBJECT(saveasMi), "activate", G_CALLBACK(cw_saveas), NULL);
	g_signal_connect(G_OBJECT(quitMi), "activate", G_CALLBACK(cw_delete), NULL);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(cw_delete), NULL);
	
	/************************event box*************************************/
	event_box = gtk_event_box_new ();
	gtk_container_add (GTK_CONTAINER(box), event_box);
    	gtk_widget_show (event_box);
    	
    	/*************************drawing area*********************************/
	drawingarea = gtk_drawing_area_new();
	//gtk_container_set_border_width(GTK_CONTAINER(window), 150);
	gtk_container_add(GTK_CONTAINER(event_box), drawingarea);
	
	/**************************toolbar*************************************/
	toolbar = gtk_toolbar_new();
	gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
	gtk_box_pack_start(GTK_BOX(drawingarea), toolbar, FALSE, FALSE, 10);
	
	frame = gtk_frame_new ("Toolbar");
  	gtk_container_add (GTK_CONTAINER (frame), toolbar);
  	gtk_box_pack_start (GTK_BOX (box), frame, FALSE, FALSE, 10);
  	newTb = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), newTb, -1);
	openTb = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), openTb, -1);
	saveTb = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), saveTb, -1);

  		
	gtk_widget_show_all(window);
	gtk_widget_show(box);
	gtk_widget_show(event_box);
	gtk_widget_show(drawingarea);
	gtk_widget_show(toolbar);
  	gtk_main();
	return 0;
}
