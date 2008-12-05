CFLAGS=-I/usr/include/gtk-2.0 -I/usr/lib/gtk-2.0/include -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12  
CLIBS=-lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lpangoft2-1.0 -lgdk_pixbuf-2.0 -lm -lpangocairo-1.0 -lgio-2.0 -lcairo -lpango-1.0 -lfreetype -lz -lfontconfig -lgobject-2.0 -lgmodule-2.0 -lglib-2.0  
OBJS=src/main.o
SRC=src/main.c
CC=gcc -g -Wall
TARGET=rexpert

all: src/main.o
	$(CC) $(CLIBS) $(OBJS) -o $(TARGET)

clean:
	rm -f src/*.o gregex

install:
	mkdir -p /usr/local/lib/geany
	cp $(TARGET) /usr/local/lib/geany/$(TARGET)
	chmod 755 /usr/local/lib/geany/$(TARGET)
uninstall:
	rm -f /usr/local/lib/geany/$(TARGET)

deinstall:
	rm -f /usr/local/lib/geany/$(TARGET)

src/main.o: src/main.c
	$(CC) $(CFLAGS)-c src/main.c -o src/main.o

