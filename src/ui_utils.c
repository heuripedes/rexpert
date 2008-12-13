/*
 *      ui_utils.c
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

RexpertMainWidgets main_widgets;

void auto_clear_tags (GtkWidget *widget, gpointer user_data)
{
	GtkTextIter *start;
	GtkTextIter *end;

	start = g_new(GtkTextIter, 1);
	end   = g_new(GtkTextIter, 1);

	gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(widget), start);
	gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(widget), end);
	gtk_text_buffer_remove_all_tags(GTK_TEXT_BUFFER(widget), start, end);
	g_free(start);
	g_free(end);
}

void ui_init ()
{
	PangoFontDescription *font_desc1;
	GtkTextBuffer *text_buffer1;
	GtkListStore *lst_store;

	main_widgets.window = create_main_window ();

	/* Text boxes */
	main_widgets.tv_pattern = GET_MAIN_WIDGET ( "tv_pattern" );
	main_widgets.tv_subject = GET_MAIN_WIDGET ( "tv_subject" );

	/* Modifier check buttons */
	main_widgets.chk_mod_g  = GET_MAIN_WIDGET ( "chk_mod_g" );
	main_widgets.chk_mod_i  = GET_MAIN_WIDGET ( "chk_mod_i" );
	main_widgets.chk_mod_m  = GET_MAIN_WIDGET ( "chk_mod_m" );
	main_widgets.chk_mod_s  = GET_MAIN_WIDGET ( "chk_mod_s" );
	main_widgets.chk_mod_x  = GET_MAIN_WIDGET ( "chk_mod_g" );

	/* Status labels */
	main_widgets.lbl_pattern_status = GET_MAIN_WIDGET ( "lbl_pattern_status" );
	main_widgets.lbl_subject_status = GET_MAIN_WIDGET ( "lbl_subject_status" );

	/* Panel */
	main_widgets.ntbk_panel = GET_MAIN_WIDGET ( "ntbk_panel" );

	/* Setup substring combo box */
	lst_store = gtk_list_store_new(4, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_POINTER);
	gtk_combo_box_set_model(GTK_COMBO_BOX(GET_MAIN_WIDGET("cbo_substring_list")), GTK_TREE_MODEL(lst_store));

	/* Error highlighting tags */
	gtk_text_buffer_create_tag(gtk_text_view_get_buffer(GTK_TEXT_VIEW(main_widgets.tv_pattern)), "error_text", "background", "#FF3A3A", NULL);

	/* Match highlighting tags */
	gtk_text_buffer_create_tag(gtk_text_view_get_buffer(GTK_TEXT_VIEW(main_widgets.tv_subject)), "matched_text0", "background", "#FFC0CB", NULL);
	gtk_text_buffer_create_tag(gtk_text_view_get_buffer(GTK_TEXT_VIEW(main_widgets.tv_subject)), "matched_text1", "background", "#90EE90", NULL);

	/* Connect the callback that auto-cleans the text tags */
	text_buffer1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(main_widgets.tv_pattern));
	g_signal_connect ((gpointer) text_buffer1, "changed", G_CALLBACK (auto_clear_tags), NULL);
	//g_object_connect(gtk_text_view_get_buffer(GTK_TEXT_VIEW(main_widgets.tv_subject)), "changed", auto_clear_tags);

	/* Show the main window */
	gtk_widget_show (main_widgets.window);
}

gchar *get_text_view_text (GtkTextView *view)
{
	GtkTextBuffer *buffer;
	GtkTextIter   *start, *end;
	gchar *text;

	text   = NULL;
	start  = g_new(GtkTextIter, 1);
	end    = g_new(GtkTextIter, 1);

	buffer = gtk_text_view_get_buffer(view);

	gtk_text_buffer_get_start_iter(buffer, start);
	gtk_text_buffer_get_end_iter(buffer, end);

	text = gtk_text_buffer_get_text(buffer, start, end, FALSE);

	g_free(start);
	g_free(end);

	return text;
}

void set_text_view_tag_by_offset_and_name (GtkTextView* view, guint start_offset, guint end_offset, gchar *name)
{
	GtkTextBuffer *buffer;
	GtkTextIter *start;
	GtkTextIter *end;

	start = g_new(GtkTextIter, 1);
	end   = g_new(GtkTextIter, 1);

	buffer = gtk_text_view_get_buffer(view);

	gtk_text_buffer_get_iter_at_offset(buffer, start, start_offset);

	if ( end_offset < 0 )
	{
		gtk_text_buffer_get_end_iter(buffer, end);
	}
	else
	{
		gtk_text_buffer_get_iter_at_offset(buffer, end, end_offset);
	}

	gtk_text_buffer_apply_tag_by_name(buffer, name, start, end);
}

void clear_text_view_tags (GtkTextView* view)
{
	GtkTextBuffer *buffer;
	GtkTextIter *start;
	GtkTextIter *end;

	start = g_new(GtkTextIter, 1);
	end   = g_new(GtkTextIter, 1);

	buffer = gtk_text_view_get_buffer(view);

	gtk_text_buffer_get_start_iter(buffer, start);
	gtk_text_buffer_get_end_iter(buffer, end);
	gtk_text_buffer_remove_all_tags(buffer, start, end);
	g_free(start);
	g_free(end);
}
