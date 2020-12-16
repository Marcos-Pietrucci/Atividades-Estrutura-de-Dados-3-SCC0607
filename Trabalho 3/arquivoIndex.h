/* Marcos Vinícius Firmino Pietrucci 10770072 */

#ifndef MAIN_H
#include"main.h"
#endif
#ifndef STDLIB_H
#include<stdlib.h>
#endif

#ifndef INDEX
#define INDEX

//Nodo do index
typedef struct {
    int idPessoa;
    int RRN;
}IndexPessoa;

#endif


/******** Funções referentes ao arquivo Index *********/
//Função que lê um vetor de IndexPesoa do disco. Carrega estes dados num vetor
IndexPessoa* le_index(FILE *index_bin, int *num_pessoas);

//Função que ordena os registros do índice primário pelo idPessoa
void ordena_index(IndexPessoa *index, int num_pessoas);

//Função que escreve um vetor de IndexPesoa no disco
void escreve_index(FILE *index_bin, IndexPessoa *index, int num_pessoas);

//Função que realiza uma busca binária no índice primário pelo RRN correspondente ao ID buscado
int busca_binaria_index(IndexPessoa *index, int num_pessoas, int idPessoa);