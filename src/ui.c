
// ui.c

#include "rexpert.h"
#include "ui.h"

RXMainUi main_ui;

void create_main_ui ()
{
	GtkWidget *vbox1;
	GtkWidget *hbox1,   *hbox2,   *hbox3;
	GtkWidget *scroll1, *scroll2;
	GtkWidget *label1,  *label2;
	GtkWidget *align1;
	PangoFontDescription *fdesk1;

	// main window stuff
	main_ui.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_window_set_title(GTK_WINDOW(main_ui.window), _("Re Xpert"));
	gtk_container_set_border_width(GTK_CONTAINER(main_ui.window), 2);
	gtk_widget_set_size_request(main_ui.window, 400, 530);

	vbox1 = gtk_vbox_new(FALSE, 3);
	gtk_container_add(GTK_CONTAINER(main_ui.window), vbox1);

	// label1
	label1 = gtk_label_new(_("Regular expression:"));

	gtk_box_pack_start(GTK_BOX(vbox1), label1, FALSE, TRUE, 0);
	gtk_misc_set_alignment(GTK_MISC(label1), 0, 0.5);

	// regex input text box
	scroll1 = gtk_scrolled_window_new(NULL, NULL);
	fdesk1   = pango_font_description_from_string("monospace 9");
	main_ui.view_regex = gtk_text_view_new();


	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll1), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll1), main_ui.view_regex);
	gtk_box_pack_start(GTK_BOX(vbox1), scroll1, TRUE, TRUE, 0);

	gtk_widget_modify_font(main_ui.view_regex, fdesk1);
	pango_font_description_free(fdesk1);

	// regex modifiers and regex status message
	hbox2 = gtk_hbox_new(TRUE, 0);
	hbox1 = gtk_hbox_new(FALSE, 0);
	align1 = gtk_alignment_new(1,0.5,0,1);
	main_ui.lbl_regex = gtk_label_new("");
	main_ui.chk_mod_i = gtk_check_button_new_with_label("i");
	main_ui.chk_mod_m = gtk_check_button_new_with_label("m");
	main_ui.chk_mod_s = gtk_check_button_new_with_label("s");
	main_ui.chk_mod_x = gtk_check_button_new_with_label("x");
	main_ui.chk_mod_g = gtk_check_button_new_with_label("g");

	gtk_box_pack_start(GTK_BOX(vbox1), hbox1, FALSE, FALSE, 0);

	gtk_box_pack_start(GTK_BOX(hbox1), main_ui.lbl_regex, TRUE, TRUE,   0);
	gtk_misc_set_alignment(GTK_MISC(main_ui.lbl_regex), 0, 0.5);

	gtk_box_pack_start(GTK_BOX(hbox1), align1,            FALSE, FALSE, 0);
	gtk_container_add(GTK_CONTAINER(align1), hbox2);
	gtk_box_pack_start(GTK_BOX(hbox2), main_ui.chk_mod_i, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox2), main_ui.chk_mod_m, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox2), main_ui.chk_mod_s, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox2), main_ui.chk_mod_x, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox2), main_ui.chk_mod_g, FALSE, FALSE, 0);

	// label2
	label2 = gtk_label_new(_("Target string:"));
	gtk_misc_set_alignment(GTK_MISC(label2), 0, 0.5);
	gtk_box_pack_start(GTK_BOX(vbox1), label2,   FALSE, FALSE, 0);

	// target text input box
	scroll2 = gtk_scrolled_window_new(NULL, NULL);
	fdesk1   = pango_font_description_from_string("monospace 9");
	main_ui.view_target = gtk_text_view_new();


	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll2), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll2), main_ui.view_target);
	gtk_box_pack_start(GTK_BOX(vbox1), scroll2, TRUE, TRUE, 0);

	gtk_widget_modify_font(main_ui.view_target, fdesk1);
	pango_font_description_free(fdesk1);

	// regex result status text (target)
	main_ui.lbl_target = gtk_label_new("");

	gtk_misc_set_alignment(GTK_MISC(main_ui.lbl_target), 0, 0.5);
	gtk_box_pack_start(GTK_BOX(vbox1), main_ui.lbl_target,   FALSE, FALSE, 0);

	// buttons
	hbox3 = gtk_hbox_new(TRUE, 0);
	main_ui.btn_testre  = gtk_button_new_with_label(_("Test expression"));
	main_ui.btn_graph = gtk_button_new_with_label(_("Generate graphic"));
	main_ui.btn_help  = gtk_button_new_with_label(_("Help"));

	gtk_box_pack_start(GTK_BOX(hbox3), main_ui.btn_testre,  TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox3), main_ui.btn_graph, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox3), main_ui.btn_help, TRUE, TRUE, 0);



	gtk_box_pack_start(GTK_BOX(vbox1), hbox3,   FALSE, TRUE, 0);

	// shows the window

}
