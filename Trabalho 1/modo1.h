/* Marcos Vinícius Firmino Pietrucci 10770072 */

/* Header referente ao modo de entrada 1 */ 
#ifndef DECLARA_MAIN_MODO1
#define DECLARA_MAIN_MODO1

#include"main.h"

#endif

Pessoa p;

//Função que inicia a leitura das entradas e o processamento do modo1
void modo1();

//Função que lê as entradas do modo 1
void le_entradas_modo1(char *arq_csv, char *arq_bin, char *index_bin);

//Função que lê os dados do arquivo CSV e retorna um vetor dinâmico com os dados
Pessoa* le_dados_csv(FILE* arq, int *num_pessoas);

