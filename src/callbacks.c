/*
 *      callbacks.c
 *
 *      Copyright 2008 Higor Eurípedes <heuripedes@gmail.com>
 *      Copyright 2008 Felipe Pena     <felipensp@gmail.com>
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

struct _PcreData
{
	gchar      *pattern;
	gchar      *subject;
	const char *error;
	int         erroffset;
	int         options;
	int         result_count;
	int         result_arr[MAX_RESULTS];
};

static struct _PcreData re_data;

//////////////////////////// Helper funcs

void populate_substring_highlight_list ()
{
	gchar *str;
	GtkTreeModel *model;
	GtkTreeIter  *iter;
	GtkWidget  *cbo;
	GValue *gvalue;

	const char  **strlist;
	int   list_length;
	int   status;
	int   i = 0;

	cbo     = GET_MAIN_WIDGET("cbo_substring_list");
	model   = gtk_combo_box_get_model(GTK_COMBO_BOX(cbo));

	status  = pcre_get_substring_list (re_data.subject, re_data.result_arr, re_data.result_count, &strlist);

	switch ( status )
	{
		case PCRE_ERROR_NOMEMORY:
			gtk_label_set_text(GTK_LABEL(main_widgets.lbl_subject_status), _("No enought memory avaliable."));
			return;
	}

	gtk_list_store_clear(GTK_LIST_STORE(model));

	str = g_new (gchar, strlen(_("[%i - %i]: All substrings")) + 8);
	g_sprintf(str, _("[%i - %i]: All substrings"), re_data.result_arr[0], re_data.result_arr[1]);

	iter = g_new(GtkTreeIter, 1);
	gtk_list_store_append(GTK_LIST_STORE(model), iter);

	G_VALUE_NEW_STRING(gvalue, str);
	gtk_list_store_set_value(GTK_LIST_STORE(model), iter, 0, gvalue);
	G_VALUE_FREE(gvalue);

	G_VALUE_NEW_INT(gvalue, re_data.result_arr[0]);
	gtk_list_store_set_value(GTK_LIST_STORE(model), iter, 1, gvalue);
	G_VALUE_FREE(gvalue);

	G_VALUE_NEW_INT(gvalue, re_data.result_arr[1]);
	gtk_list_store_set_value(GTK_LIST_STORE(model), iter, 2, gvalue);
	G_VALUE_FREE(gvalue);

	g_free(iter);
	g_free(str);

	for ( i = 1; i < re_data.result_count; i++ )
	{
		str = g_new (gchar, strlen("[%i - %i]: %s") + strlen(strlist[i]) + 8);
		g_sprintf(str, _("[%i - %i]: %s"), re_data.result_arr[i*2], re_data.result_arr[i*2+1], strlist[i]);

		iter = g_new(GtkTreeIter, 1);
		gtk_list_store_append(GTK_LIST_STORE(model), iter);

		G_VALUE_NEW_STRING(gvalue, str);
		gtk_list_store_set_value(GTK_LIST_STORE(model), iter, 0, gvalue);
		G_VALUE_FREE(gvalue);

		G_VALUE_NEW_INT(gvalue, re_data.result_arr[i*2]);
		gtk_list_store_set_value(GTK_LIST_STORE(model), iter, 1, gvalue);
		G_VALUE_FREE(gvalue);

		G_VALUE_NEW_INT(gvalue, re_data.result_arr[i*2+1]);
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
	int i, str_offset = 0, matches = 0, is_global = 0;

	re_data.subject = get_text_view_text(GTK_TEXT_VIEW(main_widgets.tv_subject));
	re_data.pattern = get_text_view_text(GTK_TEXT_VIEW(main_widgets.tv_pattern));

	re_data.options += (IS_CHECKED(main_widgets.chk_mod_i) ? PCRE_CASELESS  : 0);
	re_data.options += (IS_CHECKED(main_widgets.chk_mod_m) ? PCRE_MULTILINE : 0);
	re_data.options += (IS_CHECKED(main_widgets.chk_mod_s) ? PCRE_DOTALL    : 0);
	re_data.options += (IS_CHECKED(main_widgets.chk_mod_x) ? PCRE_EXTENDED  : 0);
	is_global = IS_CHECKED(main_widgets.chk_mod_g);

	regex = pcre_compile (re_data.pattern, re_data.options, &re_data.error, &re_data.erroffset, NULL);

	if ( regex == NULL )
	{
		message = g_new(gchar, (strlen(_("Error: %s")) + strlen(_(re_data.error))));
		g_sprintf(message, _("Error: %s"), re_data.error);
		gtk_label_set_text(GTK_LABEL(main_widgets.lbl_pattern_status), message);
		set_text_view_tag_by_offset_and_name(GTK_TEXT_VIEW(main_widgets.tv_pattern), re_data.erroffset-1, -1, "error_text");
		g_printf("%i\n", re_data.erroffset);
		g_free(message);

		return;
	}

	gtk_label_set_text(GTK_LABEL(main_widgets.lbl_pattern_status), _("No errors found."));
	
	clear_text_view_tags(GTK_TEXT_VIEW(main_widgets.tv_subject));
	
	do {
		re_data.result_count = pcre_exec (regex, NULL, re_data.subject, strlen(re_data.subject), str_offset, 0, re_data.result_arr, MAX_RESULTS);

		if ( re_data.result_count < 0 )
		{
			switch ( re_data.result_count )
			{
				case PCRE_ERROR_NOMATCH:
					if (!matches) {
						gtk_label_set_text(GTK_LABEL(main_widgets.lbl_subject_status), _("No match found."));
					}
					break;
				case PCRE_ERROR_NOMEMORY:
					gtk_label_set_text(GTK_LABEL(main_widgets.lbl_subject_status), _("No enought memory avaliable."));
					break;
				default:
					gtk_label_set_text(GTK_LABEL(main_widgets.lbl_subject_status), _("Unknown error."));
					break;
			}
			break;
		}
		matches++;
		
		for ( i = 0; i < re_data.result_count; i++ )
		{
			if (i == 0 && re_data.result_count > 1) {
				/* Nao possui subpatterns */
				continue;
			}
			highlight_substring(re_data.result_arr[i<<1], re_data.result_arr[(i<<1)+1]);
		}
		
		str_offset = re_data.result_arr[1];

		/* 
		 * message = g_new(gchar, (strlen(_("%i matches found between offsets %i and %i")) + 16));
		 * g_sprintf(message, _("%i matches found between offsets %i and %i."), (re_data.result_count-1), re_data.result_arr[0], re_data.result_arr[1]);
		 * gtk_label_set_text(GTK_LABEL(main_widgets.lbl_subject_status), message); 
		 * g_free(message);
		 */
	} while (is_global);
	
	if (matches) {
		gtk_label_set_text(GTK_LABEL(main_widgets.lbl_subject_status), _("Matched!"));
		populate_substring_highlight_list ();
	}
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
	GtkTreeIter *first;
	GtkTreeModel *model;
	GValue gvalue = {0,};
	int start, end;
	int i;


	iter  = g_new(GtkTreeIter, 1);
	first = g_new(GtkTreeIter, 1);

	model = gtk_combo_box_get_model(combobox);

	if ( !gtk_combo_box_get_active_iter(combobox, iter) )
	{
		return;
	}

	clear_text_view_tags(GTK_TEXT_VIEW(main_widgets.tv_subject));

	/* Fetches the first iter, so we can compare to the selected one to see if is the "all substrings" option */
	if ( gtk_tree_model_get_iter_first(model, first) )
	{
		gchar *str1, *str2;

		gtk_tree_model_get_value(model, first, 0, &gvalue);
		str1 = (gchar*) g_value_get_string(&gvalue);
		g_value_unset(&gvalue);

		gtk_tree_model_get_value(model, iter, 0, &gvalue);
		str2 = (gchar*) g_value_get_string(&gvalue);
		g_value_unset(&gvalue);

		if ( g_strcmp0(str1, str2) == 0 )
		{
			for ( i = 1; i < re_data.result_count; i++ )
			{
				highlight_substring(re_data.result_arr[i*2], re_data.result_arr[i*2+1]);
			}

			return;
		}
	}

	gtk_tree_model_get_value(model, iter, 1, &gvalue);
	start = g_value_get_int(&gvalue);
	g_value_unset(&gvalue);

	gtk_tree_model_get_value(model, iter, 2, &gvalue);
	end = g_value_get_int(&gvalue);
	g_value_unset(&gvalue);

	highlight_substring(start, end);
}

