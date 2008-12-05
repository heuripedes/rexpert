
// main.c

#include <stdlib.h>
#include "rexpert.h"
#include "ui.h"

#define IS_CHECKED(x) (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(x)))

//////// main ui callbacks
void on_window_delete_event (GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	gtk_main_quit();
}

void on_btn_help_clicked (GtkButton* btn, gpointer data)
{
}

void on_btn_testre_clicked (GtkButton* btn, gpointer data)
{
}

void on_btn_graph_clicked (GtkButton* btn, gpointer data)
{
}

///// Helper functions

void connect_main_ui_callbacks ()
{
	g_signal_connect(G_OBJECT(main_ui.window),    "delete-event", G_CALLBACK(gtk_main_quit),        NULL);

	// button callbacks
	g_signal_connect(G_OBJECT(main_ui.btn_testre),  "clicked",      G_CALLBACK(on_btn_testre_clicked),  NULL);
	g_signal_connect(G_OBJECT(main_ui.btn_graph), "clicked",      G_CALLBACK(on_btn_graph_clicked), NULL);
	g_signal_connect(G_OBJECT(main_ui.btn_help),  "clicked",      G_CALLBACK(on_btn_help_clicked),  NULL);
}

int main (int argc, char** argv)
{
	gtk_init(&argc, &argv);
	create_main_ui();
	connect_main_ui_callbacks();

	gtk_widget_show_all(main_ui.window);
	gtk_main();
	return 0;
}
