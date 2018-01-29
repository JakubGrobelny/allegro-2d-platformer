CC = gcc
LDFLAGS = -L/usr/lib -lallegro -lallegro_image -lallegro_dialog -lallegro_primitives -lallegro_font -lallegro_ttf -g
INCLUDE = `pkg-config --cflags --libs allegro-5`
LIBS = -lallegro -lm

SRCS = src/main.c src/object.c src/hitbox.c src/util.c src/physics.c src/list.c src/player.c src/keyboard.c src/object_updates.c src/interface.c src/string.c
OBJS = $(SRCS:.c=.o)

MAIN = game

.PHONY: depend clean
all:	$(MAIN)
	@echo Compilation finished.
$(MAIN): $(OBJS)
	$(CC) $(INCLUDE) -o $(MAIN) $(OBJS) $(LDFLAGS) $(LIBS)
.c.o:
	$(CC) $(INCLUDE) -c $< -o $@
clean:
	$(RM) src/*.o *~ $(MAIN)
	$(RM) log $(MAIN)
