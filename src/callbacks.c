/*
 *      callbacks.c
 *
 *      Copyright 2008 Higor Eurípedes <heuripedes@gmail.com>
 *      Copyright 2008 Felipe Pena     <@gmail.com>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#include "rexpert.h"
#include <string.h>
#include <pcre.h>

#define MAX_RESULTS 30

//////////////////////////// Helper funcs

void populate_substring_highlight_list (int rc, int result_vector[])
{
	gchar *subject;
	gchar *str;
	GtkTreeModel *model;
	GtkTreeIter  *iter;
	GtkWidget  *cbo;
	GValue *gvalue;
	PcreResult *pr;

	const char  **strlist;
	int   list_length;
	int   status;
	int   i = 0;

	subject = get_text_view_text(GTK_TEXT_VIEW(main_widgets.tv_subject));
	cbo     = GET_MAIN_WIDGET("cbo_substring_list");
	model   = gtk_combo_box_get_model(GTK_COMBO_BOX(cbo));

	status  = pcre_get_substring_list (subject, result_vector, rc, &strlist);

	switch ( status )
	{
		case PCRE_ERROR_NOMEMORY:
			gtk_label_set_text(GTK_LABEL(main_widgets.lbl_subject_status), _("No enought memory avaliable."));
			return;
	}

	gtk_list_store_clear(GTK_LIST_STORE(model));

	str = g_new (gchar, strlen(_("[%i - %i]: All substrings")) + 8);
	g_sprintf(str, _("[%i - %i]: All substrings"), result_vector[0], result_vector[1]);

	iter = g_new(GtkTreeIter, 1);
	gtk_list_store_append(GTK_LIST_STORE(model), iter);

	G_VALUE_NEW_STRING(gvalue, str);
	gtk_list_store_set_value(GTK_LIST_STORE(model), iter, 0, gvalue);
	G_VALUE_FREE(gvalue);

	G_VALUE_NEW_INT(gvalue, result_vector[0]);
	gtk_list_store_set_value(GTK_LIST_STORE(model), iter, 1, gvalue);
	G_VALUE_FREE(gvalue);

	G_VALUE_NEW_INT(gvalue, result_vector[1]);
	gtk_list_store_set_value(GTK_LIST_STORE(model), iter, 2, gvalue);
	G_VALUE_FREE(gvalue);

	g_free(iter);
	g_free(str);

	for ( i = 1; i < rc; i++ )
	{
		str = g_new (gchar, strlen("[%i - %i]: %s") + strlen(strlist[i]) + 8);
		g_sprintf(str, _("[%i - %i]: %s"), result_vector[i*2], result_vector[i*2+1], strlist[i]);

		iter = g_new(GtkTreeIter, 1);
		gtk_list_store_append(GTK_LIST_STORE(model), iter);

		G_VALUE_NEW_STRING(gvalue, str);
		gtk_list_store_set_value(GTK_LIST_STORE(model), iter, 0, gvalue);
		G_VALUE_FREE(gvalue);

		G_VALUE_NEW_INT(gvalue, result_vector[i*2]);
		gtk_list_store_set_value(GTK_LIST_STORE(model), iter, 1, gvalue);
		G_VALUE_FREE(gvalue);

		G_VALUE_NEW_INT(gvalue, result_vector[i*2+1]);
		gtk_list_store_set_value(GTK_LIST_STORE(model), iter, 2, gvalue);
		G_VALUE_FREE(gvalue);

		g_free(iter);
		g_free(str);
	}
}

void highlight_substring ( int start, int end )
{
	set_text_view_tag_by_offset_and_name(GTK_TEXT_VIEW(main_widgets.tv_subject), start, end, "matched_text0");
}
//////////////////////////// Callbacks

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
		set_text_view_tag_by_offset_and_name(GTK_TEXT_VIEW(main_widgets.tv_pattern), erroffset-1, -1, "error_text");
		g_printf("%i\n", erroffset);
		//set_gtk_text_view_cursor_position(GTK_TEXT_VIEW(main_ui.view_regex), erroffset);
		g_free(message);
		return;
	}
	gtk_label_set_text(GTK_LABEL(main_widgets.lbl_pattern_status), _("No errors found."));

	result_count = pcre_exec (regex, NULL, subject, (int)strlen(subject), 0, 0, result_vector, MAX_RESULTS);

	if ( result_count < 0 )
	{
		switch ( result_count )
		{
			case PCRE_ERROR_NOMATCH:
				gtk_label_set_text(GTK_LABEL(main_widgets.lbl_subject_status), _("No match found."));
				break;
			case PCRE_ERROR_NOMEMORY:
				gtk_label_set_text(GTK_LABEL(main_widgets.lbl_subject_status), _("No enought memory avaliable."));
				break;
			default:
				gtk_label_set_text(GTK_LABEL(main_widgets.lbl_subject_status), _("Unknown error."));
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
		//set_text_view_tag_by_offset_and_name(GTK_TEXT_VIEW(main_widgets.tv_subject), \
//			result_vector[i*2], result_vector[i*2+1], (i % 2 ? "matched_text0" : "matched_text1"));
		highlight_substring(result_vector[i*2], result_vector[i*2+1]);
	}

	populate_substring_highlight_list (result_count, result_vector);
}

void on_btn_show_panel_clicked (GtkButton *button, gpointer user_data)
{
	if ( GTK_WIDGET_VISIBLE(main_widgets.ntbk_panel) )
	{
		gtk_widget_hide(main_widgets.ntbk_panel);
	}
	else
	{
		gtk_widget_show(main_widgets.ntbk_panel);
	}
}


void on_cbo_substring_list_changed (GtkComboBox *combobox, gpointer user_data)
{
	GtkTreeIter *iter;
	GtkTreeModel *model;
	GValue gvalue = {0,};
	int start, end;


	iter  = g_new(GtkTreeIter, 1);
	model = gtk_combo_box_get_model(combobox);

	if ( !gtk_combo_box_get_active_iter(combobox, iter) )
	{
		return;
	}

	gtk_tree_model_get_value(model, iter, 1, &gvalue);
	start = g_value_get_int(&gvalue);
	g_value_unset(&gvalue);

	gtk_tree_model_get_value(model, iter, 2, &gvalue);
	end = g_value_get_int(&gvalue);
	g_value_unset(&gvalue);

	clear_text_view_tags(GTK_TEXT_VIEW(main_widgets.tv_subject));
	highlight_substring (start, end);

	g_printf("%i - %i\n", start, end);


}

