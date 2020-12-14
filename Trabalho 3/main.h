/* Marcos Vinícius Firmino Pietrucci 10770072 */

/* Header referente ao arquivo main */
/* Contém as estruturas básicas do projeto */
/* Contém funções que são usadas por 2 ou mais modos */
#define MAIN_H
#define STDLIB_H
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/********** Funções de uso geral que não pertecem à modos *********/

//Função que abre um arquivo com o "nome" e o"modo". Retorna um ponteiro para esse arquivo
FILE* le_arquivo(char *nome, char *modo);

//Função que verifica se o cabeçalho está consistente
int teste_consistencia_cabecalho(FILE *arq);
