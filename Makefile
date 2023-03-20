OBJS = app.o api.o langs.o lang_utils.o
PROG = app

%.o: %.c
	# $@ is the target
	# $< is the first dependency
	gcc $$( pkg-config --cflags gtk4 ) -c -g -o $@ $< $$( pkg-config --libs gtk4 ) -lcurl

$(PROG): $(OBJS)
	gcc $$( pkg-config --cflags gtk4 ) -g -o $@ $^ $$( pkg-config --libs gtk4 ) -lcurl

clean:
	rm -f app .*.sw* *.o

