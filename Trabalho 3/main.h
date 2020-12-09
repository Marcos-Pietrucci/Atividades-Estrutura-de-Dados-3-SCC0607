/* Marcos Vinícius Firmino Pietrucci 10770072 */

/* Header referente ao arquivo main */
/* Contém as estruturas básicas do projeto */
/* Contém funções que são usadas por 2 ou mais modos */
#define MAIN_H
#define STDLIB_H
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/**** Estruturas do trabalho ****/
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

/* Estrutura do grafo */
typedef struct no {
  char nomePessoa[40];
  struct no* segue;
  struct no* prox;
}Vertice;

typedef struct grafo {
    int n;      /* Número de nós */
    Vertice** lista;
}Grafo;

/********** Funções de uso geral que não pertecem à modos *********/

//Função que abre um arquivo com o "nome" e o"modo". Retorna um ponteiro para esse arquivo
FILE* le_arquivo(char *nome, char *modo);

//Função que verifica se o cabeçalho está consistente
int teste_consistencia_cabecalho(FILE *arq);
