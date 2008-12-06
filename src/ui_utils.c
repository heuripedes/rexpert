
// ui_utils.c

#include "rexpert.h"
#include "ui_utils.h"
#include <string.h>

gchar * get_gtk_text_view_text (GtkTextView* view)
{
	GtkTextBuffer *buffer;
	GtkTextIter *start;
	GtkTextIter *end;
	gchar * text;

	start = g_new(GtkTextIter, 1);
	end   = g_new(GtkTextIter, 1);
	text = g_malloc0(0);

	buffer = gtk_text_view_get_buffer(view);

	gtk_text_buffer_get_start_iter(buffer, start);
	gtk_text_buffer_get_end_iter(buffer, end);

	text = gtk_text_buffer_get_text(buffer, start, end, FALSE);

	g_free(start);
	g_free(end);

	return text;
}

void set_gtk_text_view_text (GtkTextView* view, gchar* text)
{
	GtkTextBuffer *buffer;
	buffer = gtk_text_view_get_buffer(view);
	gtk_text_buffer_set_text(buffer, text, strlen(text));
}

void set_gtk_text_view_cursor_position (GtkTextView* view, int offset)
{
	GtkTextBuffer *buffer;
	GtkTextIter* iter;
	buffer = gtk_text_view_get_buffer(view);
	gtk_text_buffer_get_iter_at_offset(buffer, iter, offset);
	gtk_widget_grab_focus(GTK_WIDGET(view));
	gtk_text_buffer_place_cursor(buffer, iter);

}


