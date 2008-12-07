
// ui.h

#ifndef UI_H
#define UI_H

typedef struct RXMainUi
{
	GtkWidget *window;
	GtkWidget *lbl_regex,  *lbl_target;
	GtkWidget *chk_mod_i,  *chk_mod_m, *chk_mod_s, *chk_mod_x, *chk_mod_g;
	GtkWidget *btn_testre, *btn_graph, *btn_help;
	GtkWidget *view_regex, *view_target;
	//GtkTextBuffer   *buffer_regex, *buffer_target;
	//GtkTextTagTable *tag_table;
}
RXMainUi;

extern RXMainUi main_ui;

void create_main_ui ();

#endif
