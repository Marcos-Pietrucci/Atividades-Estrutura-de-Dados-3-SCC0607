/* Marcos Vinícus Firmino Pietrucci 10770072 */

/* Header referente ao modo 6 */
#ifndef MAIN_H
#define MAIN_H
#include"main.h"
#endif

//Função que inicia a leitura das entradas e o processamento do modo 8
void modo8();

//Função que lê as entradas do modo 8
void le_entradas_modo8(char *nome_pesosas_bin, char *nome_index_bin, int *idPessoaBusca, char *nome_arqSegue_bin);

//Função que realiza a busca indexada pela pessoa
Pessoa busca_pessoa_indexada(FILE* arq_pessoas_bin, FILE *arq_index_bin, int idPessoaBusca);

//Função que exibe na tela as informações da pessoa p
void exibe_informacoes_pessoa(Pessoa pAux);

//Função que busca e exibe todos os registros que possuem um determinado "idPessoaQueSegue"
void busca_arqSegue_idPessoaQueSegue();

//Fimção que exibe na tela as informações da relação "Segue" cujo índice é "indc_no_vetor"
void exibe_informacoes_segue(Segue *vetSegue, int indc_no_vetor);
