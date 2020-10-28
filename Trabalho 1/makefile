CC=gcc					# C compiler

CFLAGS=-I. -g -Wall

#LIBS=-lm

DEPS= main.h modo1.h fornecido.h	

#OBJ= buscaRecursiva.o TAD_lista.o mergesort.o main.o 
OBJ= main.c modo1.c fornecido.c 
#So colocar aqui o nome do .c do seu programa

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