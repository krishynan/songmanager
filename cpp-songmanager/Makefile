CC=g++
LD=g++

CCFLAGS=$(shell perl -MExtUtils::Embed -e ccopts)
LDFLAGS=$(shell perl -MExtUtils::Embed -e ldopts)

OBJECTS = $(PROGRAM)Aux
POBJECTS=$(PROGRAM).o

PROGRAM = SongManager

all: $(PROGRAM) $(OBJECTS).o

$(OBJECTS).o: $(OBJECTS).cpp
		$(CC) $(CCFLAGS) -o $@ -c $<

$(PROGRAM).o: $(PROGRAM).cpp
		$(CC) $(CCFLAGS) -o $@ -c $<

$(PROGRAM): $(PROGRAM).o $(OBJECTS).o
		$(LD) -o $@ $(OBJECTS).o $< $(LDFLAGS)

clean:
	rm -f $(PROGRAM) $(POBJECTS) $(OBJECTS).o
