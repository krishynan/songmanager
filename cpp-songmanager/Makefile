CC=g++
LD=g++

CCFLAGS=$(shell perl -MExtUtils::Embed -e ccopts)
LDFLAGS=$(shell perl -MExtUtils::Embed -e ldopts)

AUXILIAR = musica
OBJECTS = $(PROGRAM)Aux
POBJECTS= $(PROGRAM).o

PROGRAM = SongManager

all: $(PROGRAM) $(OBJECTS).o $(AUXILIAR).o

objects: $(OBJECTS).o

$(AUXILIAR).o: $(AUXILIAR).cpp
		$(CC) -o $@ -c $<

$(OBJECTS).o: $(OBJECTS).cpp
		$(CC) $(CCFLAGS) -o $@ -c $<

$(PROGRAM).o: $(PROGRAM).cpp
		$(CC) $(CCFLAGS) -o $@ -c $<

$(PROGRAM): $(PROGRAM).o $(OBJECTS).o $(AUXILIAR).o
		$(LD) -o $@ $(OBJECTS).o $(AUXILIAR).o $< $(LDFLAGS)

clean:
	rm -vf $(PROGRAM) $(POBJECTS) $(OBJECTS).o $(AUXILIAR).o
