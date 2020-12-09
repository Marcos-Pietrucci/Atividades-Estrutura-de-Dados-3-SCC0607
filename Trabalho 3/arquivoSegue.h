/* Marcos Vinícius Firmino Pietrucci 10770072 */

#ifndef MAIN_H
#include"main.h"
#endif
#ifndef STDLIB_H
#include<stdlib.h>
#endif

/******** Funções referentes ao arquivo segue *********/

//Função que lê o arquivo binário "Segue" e retorna um vetor com todos os dados
Segue* le_dados_arqSegue_BIN(FILE *arq_segue, int *num_segue);

//Função que escreve o arquivo "Segue" em disco
void escreve_arqSegue(FILE *arq_segue, Segue *vetSegue, int num_segue);

//Função faz uma busca binária no vetorSegue e retorna o índice do registro que contém "idPessoaQueSegue"
int busca_binaria_arqSegue(Segue *vetSegue, int num_segue, int idPessoaQueSegue, int modo_entrada);