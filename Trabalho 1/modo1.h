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
void le_entradas_modo1(char *nome_arq_csv, char *nome_arq_bin, char *nome_index_bin);

//Função que lê os dados do arquivo CSV, escreve no disco e organiza o index
IndexPessoa* le_dados_csv(FILE *pessoas_csv, FILE *pessoas_bin, int *num_pessoas);

//Função que prepara a struct para o padrão de escrita, adicionando os '$' necessários
void prepara_structPessoa(Pessoa *pAux);

