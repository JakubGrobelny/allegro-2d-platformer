#Plik makefile sluzacy do skompilowania calego projektu
#W celu kompilacji nalezy uzyc polecenia "make"

CC = gcc
LDFLAGS = -L/usr/lib -lallegro -lallegro_primitives
INCLUDE = -I. -I/usr/include/allegro5
LIBS = -lallegro -lm

SRCS = main.c object.c hitbox.c sprite.c util.c physics.c list.c
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
	$(RM) *.o *~ $(MAIN)

#ciagle myle sie i wpisuje clear wiec niech bedzie tez clear
clear:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDE) $^
