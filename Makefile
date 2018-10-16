#Makefile
# To use this Makefile, you type:
#
#        make mingen
#                 
# A binary named mingen will be produced

CC = gcc
C++ = g++ 
LIBDIRS = -L/usr/lib64
INCDIRS = -I/usr/include
LDLIBS =  -lglut -lGL -lGLU -lX11 -lm

INCLUDES   = includes.h
HEADERS    = Molecule.h Individual.h Population.h structs.h
PROTOTYPES = prototypes.h
GLOBALS    = globals.h
OBJS 	   = Molecule.o Individual.o Population.o genalg.o

all : mingen

mingen: main.o $(INCLUDES) $(HEADERS) $(PROTOTYPES) $(GLOBALS) $(OBJS) 
	$(C++) -o mingen main.o $(OBJS) $(INCDIRS) $(LIBDIRS) $(LDLIBS) 

Molecule.o : Molecule.cc $(INCLUDES) $(HEADERS)
	$(C++) -c Molecule.cc
 
Individual.o : Individual.cc $(INCLUDES) $(HEADERS)
	$(C++) -c Individual.cc

Population.o : Population.cc $(INCLUDES) $(HEADERS)
	$(C++) -c Population.cc

genalg.o : genalg.cc $(INCLUDES) $(HEADERS) $(PROTOTYPES)
	$(C++) -c genalg.cc

main.o : main.cc $(INCLUDES) $(HEADERS) $(PROTOTYPES) $(OBJS) 
	$(C++) -c main.cc


clean :
	rm gatest.xyz
	rm *.o

reset :
	rm gentest.xyz
	rm *.o
	rm mingen
