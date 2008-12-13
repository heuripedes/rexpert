/*
 *      rexpert.h
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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include <glib.h>
#include <glib/gprintf.h>
#include <gtk/gtk.h>


#ifndef HAVE_REXPERT_H
#define HAVE_REXPERT_H

#include "interface.h"
#include "support.h"
#include "callbacks.h"
#include "ui_utils.h"

typedef struct
{
	gboolean debug;
}
CommandLineOptions;

extern CommandLineOptions cl_options;

#define G_VALUE_NEW_STRING(x, y) \
	x = g_new0(GValue, 1); \
	g_value_init(x, G_TYPE_STRING); \
	g_value_set_string(x, y);

#define G_VALUE_NEW_INT(x, y) \
	x = g_new0(GValue, 1); \
	g_value_init(x, G_TYPE_INT); \
	g_value_set_int(x, y);

#define G_VALUE_FREE(x) \
	g_value_unset(x); \
	g_free(x);

#endif /* HAVE_REXPERT_H */
