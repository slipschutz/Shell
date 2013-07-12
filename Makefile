CFLAGS=-c -g -Wall

SOURCES=$(shell ls *.cc)
OBJECTS=$(SOURCES:.cc=.o) 
HEADERS=$(SOURCES:.cc=.hh)
MAINO=main.o
EXE=Nucleus

$(EXE): $(OBJECTS) $(MAINO) $(HEADERS)
	g++ $(OBJECTS) -o $@

%.o: %.cc
	g++ $(CFLAGS) $< -o $@

%.hh :
	@

clean:
	rm -f $(OBJECTS) $(MAINO)
	rm -f $(EXE)
