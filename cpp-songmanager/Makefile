CC = g++
CFLAGS = -Wall

OBJECTS = musica.o repositorio.o main.o

PROGRAM = main

all: $(PROGRAM)

$(PROGRAM) : $(OBJECTS)
		$(CC) $(OBJECTS) -o $@

.c.o:
		$(CC) $(CFLAGS) -c $<

clean:
		rm -vf $(PROGRAM) $(OBJECTS)
