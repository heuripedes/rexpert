
// main.c

#include "rexpert.h"
#include "ui.h"
#include "ui_utils.h"
#include <string.h>

#define IS_CHECKED(x) (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(x)))
#define OVECOUNTER 30


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
	pcre *re;
	gchar *msg;
	gchar *regex;
	gchar *target;
	const char *error;
	int erroffset;
	int options = 0;
	int rc;
	int ovector[OVECOUNTER];
	int i;

	regex  = get_gtk_text_view_text(GTK_TEXT_VIEW(main_ui.view_regex));
	target = get_gtk_text_view_text(GTK_TEXT_VIEW(main_ui.view_target));

	options += (IS_CHECKED(main_ui.chk_mod_i) ? PCRE_CASELESS  : 0);
	options += (IS_CHECKED(main_ui.chk_mod_m) ? PCRE_MULTILINE : 0);
	options += (IS_CHECKED(main_ui.chk_mod_s) ? PCRE_DOTALL    : 0);
	options += (IS_CHECKED(main_ui.chk_mod_x) ? PCRE_EXTENDED  : 0);
// i dont know what pcre const represents 'g' modifier. "global" maybe ?
//	options += (IS_CHECKED(main_ui.chk_mod_g)?PCRE_*:0);

	re = pcre_compile (regex, options, &error, &erroffset, NULL );

	if ( re == NULL )
	{
		msg = (gchar*)g_malloc(sizeof(gchar*) * (strlen(_("Error: %s")) + strlen(_(error))));
		g_sprintf(msg, _("Error: %s"), error);
		gtk_label_set_text(GTK_LABEL(main_ui.lbl_regex), msg);
		//set_gtk_text_view_cursor_position(GTK_TEXT_VIEW(main_ui.view_regex), erroffset);
		g_free(msg);
		return;
	}

	rc = pcre_exec (re, NULL, target, (int)strlen(target), 0, 0, ovector, OVECOUNTER);

	if ( rc < 0 )
	{
		switch ( rc )
		{
			case PCRE_ERROR_NOMATCH:
				gtk_label_set_text(GTK_LABEL(main_ui.lbl_target), _("No match found"));
				break;
			case PCRE_ERROR_NOMEMORY:
				gtk_label_set_text(GTK_LABEL(main_ui.lbl_target), _("No enought memory avaliable"));
				break;
			default:
				gtk_label_set_text(GTK_LABEL(main_ui.lbl_target), _("Unknown error"));
				break;
		}
		return;
	}

	msg = (gchar*)g_malloc(sizeof(gchar*) * (strlen(_("%i matches found")) + 4 ));
	g_sprintf(msg, _("%i matches found"), (rc-1));
	gtk_label_set_text(GTK_LABEL(main_ui.lbl_target), msg);
	g_free(msg);
	
	
	clear_all_tags(GTK_TEXT_VIEW(main_ui.view_target));
	
	for ( i = 1; i < rc; i++ )
	{
		set_gtk_text_view_tag_by_offset_and_name(GTK_TEXT_VIEW(main_ui.view_target), ovector[i*2], ovector[i*2+1], (i % 2 ? "matched_text0" : "matched_text1"));
	}

}

void on_btn_graph_clicked (GtkButton* btn, gpointer data)
{
}

///// Helper functions

void connect_main_ui_callbacks ()
{
	g_signal_connect(G_OBJECT(main_ui.window), "delete-event", G_CALLBACK(gtk_main_quit), NULL);

	// button callbacks
	g_signal_connect(G_OBJECT(main_ui.btn_testre), "clicked", G_CALLBACK(on_btn_testre_clicked), NULL);
	g_signal_connect(G_OBJECT(main_ui.btn_graph),  "clicked", G_CALLBACK(on_btn_graph_clicked),  NULL);
	g_signal_connect(G_OBJECT(main_ui.btn_help),   "clicked", G_CALLBACK(on_btn_help_clicked),   NULL);
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
