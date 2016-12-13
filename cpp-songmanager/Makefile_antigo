CC = g++
CFLAGS = -Wall

OBJECTS = musica.o repositorio.o main.o
MENU_OBJECTS = menu.o main_menu.o

PROGRAM = main
MENU = menu

all: $(PROGRAM) $(MENU)

$(PROGRAM) : $(OBJECTS)
		$(CC) $(OBJECTS) -o $@

menu_principal: $(MENU)

$(MENU) : $(MENU_OBJECTS)
		$(CC) $(MENU_OBJECTS) -o $@

.c.o:
		$(CC) $(CFLAGS) -c $<

clean:
		rm -vf $(PROGRAM) $(MENU) $(OBJECTS) $(MENU_OBJECTS)
