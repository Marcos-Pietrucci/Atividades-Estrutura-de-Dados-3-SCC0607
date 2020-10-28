/* Marcos Vinícius Firmino Pietrucci 10770072 */

/* Header referente ao arquivo main */
/* Contém as estruturas e funções comuns à todos os modos*/

#ifndef MAIN_H
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
    int removido;
    int RRN;
}IndexPessoa;

// Função que abre um arquivo cujo nome é "nome", extensão "ext" e modo "modo". Retorna um ponteiro
FILE* le_arquivo(char *nome, char modo);


// Função que verifica se o cabeçalho está consistente
int teste_consistencia_cabecalho(FILE *arq);


#endif