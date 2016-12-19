# /*
# #   Universidade Federal do Rio de Janeiro
# #   Departamento de Eletronica e de Computacao
# #   Linguagens de Programacao
# #
# #   Trabalho 03
# #
# #   Grupo:
# #      Krishynan Shanty
#       Nicholas Quagliani
# */


CC=g++
LD=g++

CCFLAGS=$(shell perl -MExtUtils::Embed -e ccopts)
LDFLAGS=$(shell perl -MExtUtils::Embed -e ldopts)

MUSICA = musica
OBJECTS = $(PROGRAM)Aux
POBJECTS= $(PROGRAM).o

PROGRAM = SongManager

all: $(PROGRAM) $(OBJECTS).o $(MUSICA).o

objects: $(OBJECTS).o

$(MUSICA).o: $(MUSICA).cpp
		$(CC) -o $@ -c $<

$(OBJECTS).o: $(OBJECTS).cpp
		$(CC) $(CCFLAGS) -o $@ -c $<

$(PROGRAM).o: $(PROGRAM).cpp
		$(CC) $(CCFLAGS) -o $@ -c $<

$(PROGRAM): $(PROGRAM).o $(OBJECTS).o $(MUSICA).o
		$(LD) -o $@ $(OBJECTS).o $(MUSICA).o $< $(LDFLAGS)

clean:
	rm -vf $(PROGRAM) $(POBJECTS) $(OBJECTS).o $(MUSICA).o
