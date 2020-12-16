/* Marcos Vinícus Firmino Pietrucci 10770072 */

/* Header referente ao modo 4 */
#ifndef MAIN_H
#define MAIN_H
#include"main.h"
#endif

//Função que inicia a leitura das entradas e o processamento do modo 4
void modo4();

//Função que lê as entradas do modo 4
void le_entradas_modo4(char *nome_arq_bin, char *nome_index_bin, int *n);

//Função que lê as entradas a serem inseridas no arquivo e adiciona ao final do arquivo
IndexPessoa* insere_pessoas_bin(FILE *pessoas_bin, FILE *index_bin, int n, int *num_pessoas);
