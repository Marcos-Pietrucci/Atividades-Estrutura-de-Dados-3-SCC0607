#ifndef MAIN_H
#define MAIN_H
#include"main.h"
#endif

//Função que inicia a leitura das entradas e o processamento do modo
void modo3();

//Função que lê as entradas do modo 3
Pessoa* le_entradas_modo3(char *nome_arq_binchar, char *nome_index_bin, char *nome_campo);

//Função que busca o registro solicitado
void busca_registro(FILE *pessoas_bin, FILE *index_bin, char *nome_campo, Pessoa *PessoaBusca);

//Função que busca o registro solicitado por meio de busca indexada com o idPessoa
void busca_registro_indexada(FILE *pessoas_bin, FILE *index_bin, int idPessoa);

