
#include "rexpert.h"
#include <string.h>
#include <pcre.h>

#define MAX_RESULTS 30

void on_btn_test_pattern_clicked (GtkButton *button, gpointer user_data)
{
	pcre       *regex;
	gchar      *message;
	gchar      *pattern;
	gchar      *subject;
	const char *error;
	int erroffset;
	int options = 0;
	int result_count;
	int result_vector[MAX_RESULTS];
	int i;

	subject = get_text_view_text(GTK_TEXT_VIEW(main_widgets.tv_subject));
	pattern = get_text_view_text(GTK_TEXT_VIEW(main_widgets.tv_pattern));
	
	options += (IS_CHECKED(main_widgets.chk_mod_i) ? PCRE_CASELESS  : 0);
	options += (IS_CHECKED(main_widgets.chk_mod_m) ? PCRE_MULTILINE : 0);
	options += (IS_CHECKED(main_widgets.chk_mod_s) ? PCRE_DOTALL    : 0);
	options += (IS_CHECKED(main_widgets.chk_mod_x) ? PCRE_EXTENDED  : 0);
//	options += (IS_CHECKED(main_widgets.chk_mod_g) ? PCRE_          : 0);

	regex = pcre_compile (pattern, options, &error, &erroffset, NULL);
	
	if ( regex == NULL )
	{
		message = g_new(gchar, (strlen(_("Error: %s")) + strlen(_(error))));
		g_sprintf(message, _("Error: %s"), error);
		gtk_label_set_text(GTK_LABEL(main_widgets.lbl_pattern_status), message);
		//set_gtk_text_view_cursor_position(GTK_TEXT_VIEW(main_ui.view_regex), erroffset);
		g_free(message);
		return;
	}
	
	result_count = pcre_exec (regex, NULL, subject, (int)strlen(subject), 0, 0, result_vector, MAX_RESULTS);
	
	if ( result_count < 0 )
	{
		switch ( result_count )
		{
			case PCRE_ERROR_NOMATCH:
				gtk_label_set_text(GTK_LABEL(main_widgets.lbl_subject_status), _("No match found"));
				break;
			case PCRE_ERROR_NOMEMORY:
				gtk_label_set_text(GTK_LABEL(main_widgets.lbl_subject_status), _("No enought memory avaliable"));
				break;
			default:
				gtk_label_set_text(GTK_LABEL(main_widgets.lbl_subject_status), _("Unknown error"));
				break;
		}
		return;
	}
	
	if ( !(result_count - 1) )
	{
		message = g_new(gchar, (strlen(_("No matches found.")) ));
		g_sprintf(message, _("No matches found."));
		gtk_label_set_text(GTK_LABEL(main_widgets.lbl_subject_status), message);
		g_free(message);
	}
	else
	{
		message = g_new(gchar, (strlen(_("%i matches found between offsets %i and %i")) + 16)); /* 16 = 4 for each integer */
		g_sprintf(message, _("%i matches found between offsets %i and %i."), (result_count-1), result_vector[0], result_vector[1]);
		gtk_label_set_text(GTK_LABEL(main_widgets.lbl_subject_status), message);
		g_free(message);
	}
	
	clear_text_view_tags(GTK_TEXT_VIEW(main_widgets.tv_subject));

	for ( i = 1; i < result_count; i++ )
	{
		set_text_view_tag_by_offset_and_name(GTK_TEXT_VIEW(main_widgets.tv_subject), \
			result_vector[i*2], result_vector[i*2+1], (i % 2 ? "matched_text0" : "matched_text1"));
	}
}

