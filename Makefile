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
OBJS 	   = Molecule.o Individual.o Population.o genalg.o genetester.o

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

genetester.o : genetester.cc $(INCLUDES) $(HEADERS) $(PROTOTYPES)
	$(C++) -c genetester.cc

main.o : main.cc $(INCLUDES) $(HEADERS) $(PROTOTYPES) $(OBJS) 
	$(C++) -c main.cc

#analysis

CFLAG=

zmtconv : zmtconv.o
	$(C++) $(CFLAG) -o zmtconv zmtconv.o $(INCDIRS) $(LIBDIRS) $(LDLIBS)

zmtconv.o : zmtconv.cc
	$(C++) $(CFLAG) -c zmtconv.cc

#zmtconv

datagraph : datagraph.o
	$(C++) $(CFLAG) -o datagraph datagraph.o $(INCDIRS) $(LIBDIRS) $(LDLIBS)

datagraph.o : datagraph.cc
	$(C++) $(CFLAG) -c datagraph.cc

clean :
	rm gentest.xyz
	rm *.o

pristine :
	rm gentest.xyz
	rm *.o
	rm mingen

dgclean :
	rm ./analysis/*.eps

dgpristine :
	rm ./analysis/*.dat
	rm ./analysis/*.eps
	rm ./analysis/datagraph
