#Makefile
# To use this Makefile, you type:
#
#        make gadec
#                 
# A binary named gadec will be produced

CC = gcc
C++ = g++ 
LIBDIRS = -L/usr/lib64
INCDIRS = -I/usr/include

.c:
	$(CC)  $@.c $(INCDIRS) $(LIBDIRS) -o $@

.cpp:
	$(C++)  -O $@.cpp -g $(INCDIRS) $(LIBDIRS) -o $@

clean :
	rm gatest.xyz

reset :
	rm gentest.xyz
	rm gadec
