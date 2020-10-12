CC=gcc					# C compiler

CFLAGS=-I. -g -Wall

#LIBS=-lm

#DEPS= prototipos.h	

#OBJ= buscaRecursiva.o TAD_lista.o mergesort.o main.o 
OBJ= Exercicio1.o #buscaRecursiva.o mergesort.o manipularFiles.o main.o 
#So colocar aqui o nome do .c do seu programa

# rule for files ending in .o (.o file depends upon the .c version of the file and the .h files in the DEPS macro)

#Aparentemente $@ significa o nome a funcao que foi chamada
%.o: %.c $(DEPS)		
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o prog $^ $(CFLAGS) $(LIBS)

.PHONY: run

run:
	./prog

.PHONY: clean

clean:
	rm -f *.o prog  

.PHONY: debug

debug:
	gdb ./prog