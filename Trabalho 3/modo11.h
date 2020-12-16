/* Marcos Vinícius Firmino Pietrucci 10770072*/

#ifndef MAIN_H
#include"main.h"
#endif
#ifndef STDLIB_H
#include<stdlib.h>
#endif
#include"grafo.h"

//Função que organiza e executa o modo 11
void modo11();

//Função que lê as entradas do modo 11
void le_entradas_modo11(char *nome_arq_pessoa, char *nome_arq_index, char * nome_arq_segue, char *nomeCelebridade);

void imprime_modo11(Grafo *gr_t, int *vetAntecessores, char *nomeCelebridade);