#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <libintl.h>
#include <locale.h>
#include <pcre.h>

#define _ gettext
#define IS_CHECKED(x) (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(x)))

GtkWidget     *window;
GtkWidget     *lbl_regex,  *lbl_target;
GtkWidget     *chk_mod_i,  *chk_mod_m, *chk_mod_s, *chk_mod_x, *chk_mod_g;
GtkWidget     *btn_test,   *btn_graph, *btn_help;
GtkWidget     *view_regex, *view_target;
GtkTextBuffer *buff_regex, *buff_target;

//////// CALLBACKS
void on_window_delete_event (GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	gtk_main_quit();
}

void on_btn_help_clicked (GtkButton* btn, gpointer data)
{
}

void on_btn_test_clicked (GtkButton* btn, gpointer data)
{
}

void on_btn_graph_clicked (GtkButton* btn, gpointer data)
{
}

/////// OTHER FUNCTIONS
void create_interface ()
{
	GtkWidget *main_vbox;
	GtkWidget *mod_hbox;
	GtkWidget *hbox1,   *hbox2;
	GtkWidget *scroll1, *scroll2;
	GtkWidget *label1,  *label2;

	// main window stuff
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_window_set_title(GTK_WINDOW(window), _("Re Xpert"));
	gtk_container_set_border_width(GTK_CONTAINER(window), 2);
	gtk_widget_set_size_request(window, 400, 530);

	g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(on_window_delete_event), NULL);

	main_vbox = gtk_vbox_new(FALSE, 3);
	gtk_container_add(GTK_CONTAINER(window), main_vbox);

	// label1
	label1 = gtk_label_new(_("Regular expression:"));

	gtk_box_pack_start(GTK_BOX(main_vbox), label1, FALSE, TRUE, 0);
	gtk_misc_set_alignment(GTK_MISC(label1), 0, 0.5);

	// regex input text box
	scroll1    = gtk_scrolled_window_new(NULL, NULL);
	buff_regex = gtk_text_buffer_new(NULL);
	view_regex = gtk_text_view_new_with_buffer(buff_regex);

	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll1), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll1), view_regex);
	gtk_box_pack_start(GTK_BOX(main_vbox), scroll1, TRUE, TRUE, 0);

	// regex modifiers and regex status message
	hbox1     = gtk_hbox_new(FALSE, 0);
	mod_hbox  = gtk_hbox_new(TRUE, 0);
	lbl_regex = gtk_label_new("");
	chk_mod_i = gtk_check_button_new_with_label("i");
	chk_mod_m = gtk_check_button_new_with_label("m");
	chk_mod_s = gtk_check_button_new_with_label("s");
	chk_mod_x = gtk_check_button_new_with_label("x");
	chk_mod_g = gtk_check_button_new_with_label("g");

	gtk_box_pack_start(GTK_BOX(main_vbox), mod_hbox, FALSE, FALSE, 0);

	gtk_box_pack_start(GTK_BOX(mod_hbox), lbl_regex, TRUE, TRUE,   0);
	gtk_misc_set_alignment(GTK_MISC(lbl_regex), 0, 0.5);

	gtk_box_pack_start(GTK_BOX(mod_hbox), hbox1,     FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox1),    chk_mod_i, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox1),    chk_mod_m, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox1),    chk_mod_s, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox1),    chk_mod_x, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox1),    chk_mod_g, FALSE, FALSE, 0);

	// label2
	label2 = gtk_label_new(_("Target string:"));
	gtk_misc_set_alignment(GTK_MISC(label2), 0, 0.5);
	gtk_box_pack_start(GTK_BOX(main_vbox), label2,   FALSE, FALSE, 0);

	// target text input box
	scroll2     = gtk_scrolled_window_new(NULL, NULL);
	buff_target = gtk_text_buffer_new(NULL);
	view_target = gtk_text_view_new_with_buffer(buff_target);

	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll2), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll2), view_target);
	gtk_box_pack_start(GTK_BOX(main_vbox), scroll2, TRUE, TRUE, 0);

	// regex result status text (target)
	lbl_target = gtk_label_new("");

	gtk_misc_set_alignment(GTK_MISC(lbl_target), 0, 0.5);
	gtk_box_pack_start(GTK_BOX(main_vbox), lbl_target,   FALSE, FALSE, 0);

	// buttons
	hbox2     = gtk_hbox_new(TRUE, 0);
	btn_test  = gtk_button_new_with_label(_("Test expression"));
	btn_graph = gtk_button_new_with_label(_("Generate graphic"));
	btn_help  = gtk_button_new_with_label(_("Help"));

	gtk_box_pack_start(GTK_BOX(hbox2), btn_test,  TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox2), btn_graph, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox2), btn_help, TRUE, TRUE, 0);

	g_signal_connect(G_OBJECT(btn_test),  "clicked", G_CALLBACK(on_btn_test_clicked),  NULL);
	g_signal_connect(G_OBJECT(btn_graph), "clicked", G_CALLBACK(on_btn_graph_clicked), NULL);
	g_signal_connect(G_OBJECT(btn_help),  "clicked", G_CALLBACK(on_btn_help_clicked),  NULL);

	gtk_box_pack_start(GTK_BOX(main_vbox), hbox2,   FALSE, TRUE, 0);

	// shows the window
	gtk_widget_show_all(window);
}

int main (int argc, char** argv)
{
	gtk_init(&argc, &argv);
	create_interface();
	gtk_main();
	return 0;
}
