CXX=$(shell root-config --cxx)
CFLAGS=-c -g -Wall $(shell root-config --cflags) -I./src -I ./include 
LDLIBS=$(shell root-config --glibs)
LDFLAGS=$(shell root-config --ldflags)
#SOURCES=./src/SL_Event.cc ./src/FileManager.cc ./src/Filter.cc

EXTRASOURCE=State.cc Shell.cc
EXTRAOBJS=$(patsubst %.cc,%.o,$(EXTRASOURCE))
EXTRAHEADS=$(patsubst %.cc,%.hh,$(EXTRASOURCE))

ROOTCINT=rootcint

NAME=Nucleus


temp= $(addprefix lib,$(NAME))
temp2=$(addsuffix $(LDFLAGS),$(temp))
LIBRARY= $(addsuffix .so,$(temp))
DICTNAME=$(addsuffix Dictionary,$(NAME))
DICTOBJ=$(addsuffix .o,$(DICTNAME))
OBJECT=$(addsuffix .o, $(NAME))
HEAD=$(addsuffic .hh,$(NAME))
.PHONY: clean get put all test sclean

all: $(LIBRARY) 

$(LIBRARY) : $(OBJECT) $(EXTRAOBJS) $(DICTOBJ) $(EXTRAHEADS) $(HEAD)
	@echo "Building Library"
	@$(CXX) `root-config --cflags` -fPIC -shared -o $@ $^
	@echo "Build succeed"

%Dictionary.o : %.hh $(EXTRAHEADS) %LinkDef.h
	@echo "Generating Dictionary"
	@$(ROOTCINT) -f $(patsubst %.o,%.cc,$@) -c $^;
	@echo "Compiling Dicionary"
	@$(CXX) -p -fPIC $(CFLAGS) -c $(patsubst %.o,%.cc,$@)

%.o : %.cc
	@echo "Compiling" $< "..."
	@$(CXX) $(CFLAGS) -fPIC $< -o $@ 

test:
	@echo $(LIBRARY) : $(DICTOBJ) $(OBJECTS)
	echo $(EXTRAOBJS)
	echo $(FOO)


clean:
	-rm -f $(DICTOBJ) $(OBJECT) $(EXTRAOBJS)
	-rm -f *Dictionary.h
	-rm -f *Dictionary.cc
	-rm -f $(LIBRARY)
	-rm -f *Parsed.cc
	-rm -f *Parsed.o
sclean:
	-rm *~
	make clean