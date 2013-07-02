CFLAGS=-c -g -Wall

SOURCES=$(shell ls *.cc)
OBJECTS=$(SOURCES:.cc=.o) 
MAINO=main.o
EXE=Nucleus

$(EXE): $(OBJECTS) $(MAINO)
	g++ $(OBJECTS) -o $@

%.o: %.cc
	g++ $(CFLAGS) $< -o $@
clean:
	rm -f $(OBJECTS) $(MAINO)
	rm -f $(EXE)