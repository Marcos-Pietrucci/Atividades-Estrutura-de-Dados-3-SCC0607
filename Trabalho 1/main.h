/* Marcos Vinícius Firmino Pietrucci 10770072 */

/* Header referente ao arquivo main */
/* Contém as estruturas e funções comuns à todos os modos*/
#define MAIN_H
#include<stdio.h>
#include<string.h>

//Nodo das pessoas
typedef struct {
    char removido;
    int idPessoa;
    char nomePessoa[40];
    int idadePessoa;
    char twitterPessoa[15];
}Pessoa;

//Nodo do index
typedef struct {
    int idPessoa;
    int RRN;
}IndexPessoa;

// Função que abre um arquivo com o "nome" e o"modo". Retorna um ponteiro para esse arquivo
FILE* le_arquivo(char *nome, char *modo, int entrada);

// Função que verifica se o cabeçalho está consistente
int teste_consistencia_cabecalho(FILE *arq);

//Função que ordena os registros do índice primário pelo idPessoa
void ordena_index(IndexPessoa *index, int num_pessoas);

//Função que escreve um vetor de IndexPesoa no disco
void escreve_index(FILE *index_bin, IndexPessoa * index, int num_pessoas);
