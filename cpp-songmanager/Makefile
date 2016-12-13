CC=g++
LD=g++

CCFLAGS=$(shell perl -MExtUtils::Embed -e ccopts)
LDFLAGS=$(shell perl -MExtUtils::Embed -e ldopts)

#OBJECTS = $(PROGRAM)Aux
POBJECTS=$(PROGRAM).o

PROGRAM = SongManager

all: $(PROGRAM)

#$(OBJECTS).o: $(OBJECTS).cpp
#		$(CC) $(CCFLAGS) -o $@ -c $<

$(PROGRAM).o: $(PROGRAM).cpp
		$(CC) $(CCFLAGS) -o $@ -c $<

$(PROGRAM): $(PROGRAM).o
		$(LD) -o $@ $(OBJECTS) $< $(LDFLAGS)

clean:
	rm -f $(PROGRAM) $(POBJECTS)
