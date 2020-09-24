CC=gcc					# C compiler

CFLAGS=-I. -g -Wall

#LIBS=-lm

DEPS= prototipos.h	

#OBJ= buscaRecursiva.o TAD_lista.o mergesort.o main.o 
OBJ= TAD_lista.o buscaRecursiva.o mergesort.o manipularFiles.o main.o 


# rule for files ending in .o (.o file depends upon the .c version of the file and the .h files in the DEPS macro)

%.o: %.c $(DEPS)		
	$(CC) -c -o $@ $< $(CFLAGS)

prog: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: run

run:
	./prog

.PHONY: clean

clean:
	rm -f *.o  

.PHONY: debug

debug:
	gdb ./prog