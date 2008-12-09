## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = rexpert

rexpert_SOURCES = \
	main.c \
	rexpert.h \
	ui_utils.c ui_utils.h \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h

rexpert_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

