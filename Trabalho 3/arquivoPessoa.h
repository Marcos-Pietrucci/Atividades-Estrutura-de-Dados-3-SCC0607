#ifndef MAIN_H
#include"main.h"
#endif
#ifndef STDLIB_H
#include<stdlib.h>
#endif

/******** Funções referentes ao arquivo Pessoa *********/

//Função que prepara a struct para o padrão de escrita, adicionando os '$' necessários e adicionando 'removido'
void prepara_structPessoa(Pessoa *pAux);

//Função que lê a Pessoa do arquvo cujo RRN é "RRN". Retorna uma estrutura com os dados da pessoa
Pessoa busca_RRN_pessoa(FILE *pessoas_bin, int RRN);