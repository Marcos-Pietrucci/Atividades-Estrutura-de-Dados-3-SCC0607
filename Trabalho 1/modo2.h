#ifndef MAIN_H
#define MAIN_H
#include"main.h"
#endif

//Função que inicia a leitura das entradas e o processamento do modo
void modo2();

//Função que lê as entradas do modo 2
void le_entradas_modo2(char *nome_arq_bin);

//Função que lê os dados do arquivo bin e exibe na tela os registros não removidos
void exibe_dados_bin(FILE *pessoas_bin);
