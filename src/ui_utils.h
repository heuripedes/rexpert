/*
 *      ui_utils.h
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

#ifndef HAVE_UI_UTILS_H
#define HAVE_UI_UTILS_H

typedef struct
{
	GtkWidget *window;
	GtkWidget *tv_pattern, *tv_subject;
	GtkWidget *chk_mod_i, *chk_mod_m, *chk_mod_s, *chk_mod_x, *chk_mod_g;
	GtkWidget *lbl_pattern_status, *lbl_subject_status;
}
RexpertMainWidgets;

extern RexpertMainWidgets main_widgets;

void ui_init ();

#endif /* HAVE_UI_UTILS_H */
