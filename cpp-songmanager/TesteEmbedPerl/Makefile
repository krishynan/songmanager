CC=g++
LD=g++

CCFLAGS=$(shell perl -MExtUtils::Embed -e ccopts)
LDFLAGS=$(shell perl -MExtUtils::Embed -e ldopts)

OBJECTS = $(PROGRAM).o

PROGRAM = testaAutor

all:  $(PROGRAM)

$(PROGRAM).o: $(PROGRAM).cpp
		$(CC) $(CCFLAGS) -o $@ -c $<

$(PROGRAM): $(PROGRAM).o
		$(LD) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(OBJECTS) $(PROGRAM)
