# Makefile
TAR = ecp
CC = gcc #-O6 -Wall
L = -lm
OBJS = main.o dancinglinks.o algorithmx.o sudoku.o
SHAD = -fPIC -shared
LIB = libikax.so

all : $(TAR)
$(TAR): $(OBJS)
	  $(CC) -o $@ $(OBJS) $(L)
clean:
	  rm -f $(OBJS) $(LIB) $(TAR) *~ *.bak

.c.o:	  $(CC) -c $<om

main.o: main.h dancinglinks.o
dancinglinks.o: dancinglinks.h
algorithmx.o: algorithmx.h dancinglinks.o
sudoku.o: sudoku.h algorithmx.h