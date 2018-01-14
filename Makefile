#Plik makefile sluzacy do skompilowania calego projektu
#W celu kompilacji nalezy uzyc polecenia "make"

CC = gcc
LDFLAGS = -L/usr/lib -lallegro -lallegro_image -lallegro_dialog
INCLUDE = -I. -I/usr/include/allegro5
LIBS = -lallegro -lm

SRCS = src/main.c src/object.c src/hitbox.c src/util.c src/physics.c src/list.c src/player.c src/keyboard.c src/object_updates.c
OBJS = $(SRCS:.c=.o)

MAIN = game

.PHONY: depend clean
all:	$(MAIN)
	@echo Projekt został skompilowany
$(MAIN): $(OBJS)
	$(CC) $(INCLUDE) -o $(MAIN) $(OBJS) $(LDFLAGS) $(LIBS)
.c.o:
	$(CC) $(INCLUDE) -c $< -o $@
clean:
	$(RM) src/*.o *~ $(MAIN)
	$(RM) log $(MAIN)

#ciagle myle sie i wpisuje clear wiec niech bedzie tez clear
clear:
	$(RM) src/*.o *~ $(MAIN)
	$(RM) log $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDE) $^
