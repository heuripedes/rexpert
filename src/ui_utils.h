
// ui_utils.h

#ifndef UI_UTILS_H
#define UI_UTILS_H

gchar * get_gtk_text_view_text (GtkTextView* view);
gchar * get_gtk_text_view_text_by_offset (GtkTextView* view, guint offset, guint length);
void set_gtk_text_view_tag_by_offset_and_name (GtkTextView* view, guint start_offset, guint end_offset, gchar *name);
void clear_all_tags (GtkTextView* view);
void set_gtk_text_view_text (GtkTextView* view, gchar* text);
void set_gtk_text_view_cursor_position (GtkTextView* view, int offset);

#endif
