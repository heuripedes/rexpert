## Process this file with automake to produce Makefile.in

SUBDIRS = src 

EXTRA_DIST = config.rpath m4/ChangeLog  \
	autogen.sh \
	rexpert.glade \
	rexpert.gladep

install-data-local:
	@$(NORMAL_INSTALL)
	if test -d $(srcdir)/pixmaps; then \
	  $(mkinstalldirs) $(DESTDIR)$(pkgdatadir)/pixmaps; \
	  for pixmap in $(srcdir)/pixmaps/*; do \
	    if test -f $$pixmap; then \
	      $(INSTALL_DATA) $$pixmap $(DESTDIR)$(pkgdatadir)/pixmaps; \
	    fi \
	  done \
	fi

dist-hook:
	if test -d pixmaps; then \
	  mkdir $(distdir)/pixmaps; \
	  for pixmap in pixmaps/*; do \
	    if test -f $$pixmap; then \
	      cp -p $$pixmap $(distdir)/pixmaps; \
	    fi \
	  done \
	fi

really-clean:
	-while read i; do \
		echo "[rm] $$i"; \
		find . -iname "$$i" -delete 2&> /dev/null; \
	done < .bzrignore

ACLOCAL_AMFLAGS = -I m4
