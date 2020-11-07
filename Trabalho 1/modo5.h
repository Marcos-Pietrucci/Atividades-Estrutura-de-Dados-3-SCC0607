#ifndef MAIN_H
#define MAIN_H
#include"main.h"
#endif
#ifndef STDLIB_H
#define STDLIB_H
#include<stdlib.h>
#endif

//Função que inicia a leitura das entradas e o processamento do modo
void modo5();

//Função que lê os nomes dos arquivos e a quantidade de alterações
void le_entradas_modo5(char *nome_arq_bin, char *nome_index_bin, int *n);

//Função que processa o modo: lê os pedidos de alteração, faz a busca sequencial no arquivo binário, altera o registro em memória e o reescreve no disco 
void atualiza_pessoas_bin(FILE *pessoas_bin, IndexPessoa* index, int n, int num_pessoas);

//Função que realiza a busca e alteração dos registros por meio de uma busca indexada, quando o idPessoa é fornecido
void atualiza_pessoas_bin_indexada(FILE *pessoas_bin, IndexPessoa *index, int num_pessoas, int idPessoa, Pessoa pAltera); //É chamada dentro da atualiza_pessoas_bin

//Função que coloca dados inválidos na Pessoa apontada por p
void invalida_pessoa(Pessoa *p); //Útil no momento da comparação, pois me poupa de vários 'if'

//Função que atualiza o index em memória, busca pelo registro com 'idAntigo' e substitiu pelo 'idNovo' 
void atualiza_index(IndexPessoa *index, int num_pessoas, int idAntigo, int idNovo);
