/* Marcos Vinícius Firmino Pietrucci 10770072 */

/* Header referente ao arquivo main */
/* Contém as estruturas básicas do projeto */
/* Contém funções que são usadas por 2 ou mais modos */
#define MAIN_H
#define STDLIB_H
#include<stdlib.h>
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

//Nodo do segue
typedef struct {
    char removido;
    int idPessoaQueSegue;
    int idPessoaQueESeguida;
    char grauAmizade[3];
    char dataInicioQueSegue[11];
    char dataFimQueSegue[11];
}Segue;


/********** Funções usadas por 2 ou mais modos *********/

//Função que abre um arquivo com o "nome" e o"modo". Retorna um ponteiro para esse arquivo
FILE* le_arquivo(char *nome, char *modo, int modo_entrada);

//Função que verifica se o cabeçalho está consistente
int teste_consistencia_cabecalho(FILE *arq, int modo_entrada);

//Função que prepara a struct para o padrão de escrita, adicionando os '$' necessários e adicionando 'removido'
void prepara_structPessoa(Pessoa *pAux);

//Função que lê um vetor de IndexPesoa do disco. Carrega estes dados num vetor
IndexPessoa* le_index(FILE *index_bin, int *num_pessoas);

//Função que ordena os registros do índice primário pelo idPessoa
void ordena_index(IndexPessoa *index, int num_pessoas);

//Função que escreve um vetor de IndexPesoa no disco
void escreve_index(FILE *index_bin, IndexPessoa *index, int num_pessoas);

//Função que realiza uma busca binária no índice primário pelo RRN correspondente ao ID buscado
int busca_binaria_index(IndexPessoa *index, int num_pessoas, int idPessoa, int modo);

//Função que lê a Pessoa do arquvo cujo RRN é "RRN". Retorna uma estrutura com os dados da pessoa
Pessoa busca_RRN_pessoa(FILE *pessoas_bin, int RRN, int modo);

//Função que lê o arquivo binário "Segue" e retorna um vetor com todos os dados
Segue* le_dados_arqSegue_BIN(FILE *arq_segue, int *num_segue);

//Função que escreve o arquivo "Segue" em disco
void escreve_arqSegue(FILE *arq_segue, Segue *vetSegue, int num_segue);

//Função faz uma busca binária no vetorSegue e retorna o índice do registro que contém "idPessoaQueSegue"
int busca_binaria_arqSegue(Segue *vetSegue, int num_segue, int idPessoaQueSegue, int modo_entrada);

