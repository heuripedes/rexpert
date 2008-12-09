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


RexpertMainWidgets main_widgets;

void ui_init ()
{
	main_widgets.window = create_main_window ();

	/* Text boxes */
	main_widgets.tv_pattern = lookup_widget ( main_widgets.window, "tv_pattern" );
	main_widgets.tv_subject = lookup_widget ( main_widgets.window, "tv_subject" );

	/* Modifier check buttons */
	main_widgets.chk_mod_g  = lookup_widget ( main_widgets.window, "chk_mod_g" );
	main_widgets.chk_mod_i  = lookup_widget ( main_widgets.window, "chk_mod_i" );
	main_widgets.chk_mod_m  = lookup_widget ( main_widgets.window, "chk_mod_m" );
	main_widgets.chk_mod_s  = lookup_widget ( main_widgets.window, "chk_mod_s" );
	main_widgets.chk_mod_x  = lookup_widget ( main_widgets.window, "chk_mod_g" );

	/* Status labels */
	main_widgets.lbl_pattern_status = lookup_widget ( main_widgets.window, "lbl_pattern_status" );
	main_widgets.lbl_subject_status = lookup_widget ( main_widgets.window, "lbl_subject_status" );

	gtk_widget_show (main_widgets.window);
}
