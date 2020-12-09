/* Marcos Vinícius Firmino Pietrucci 10770072*/

// STDLIB_H
#ifndef MAIN_H
#include"main.h"
#endif
#ifndef STDLIB_H
#include<stdlib.h>
#endif

//Função que inicia o modo 9
void modo9();

void le_entradas_modo9(char *nome_arq_pessoa, char *nome_arq_index, char *nome_arq_segue);


Grafo* leitura_arq_pessoa_gera_grafo(Grafo *gr, 
FILE *arq_pessoa, IndexPessoa *index, Segue *vetSegue, int num_pessoas, int num_segue);
