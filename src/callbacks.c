#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"


void on_btn_test_pattern_clicked (GtkButton *button, gpointer user_data)
{
	/*pcre *re;
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
// i dont know what pcre const represents 'g' modifier.
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
	}*/
}

