CC = clang
CFLAGS = -shared -fpic -g3 -O0 -Wextra -pedantic -pthread $(shell pkg-config --cflags glib-2.0)

all:
	$(CC) $(CFLAGS) -lplayerctl -lprofanity -o profanity-playerctl.so profanity-playerctl.c

install:
	cp profanity-playerctl.so ~/.local/share/profanity/plugins
	
clean:
	rm profanity-playerctl.so
