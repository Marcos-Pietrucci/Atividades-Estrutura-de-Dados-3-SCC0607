/* Marcos Vinícius Firmino Pietrucci 10770072 */

/* Header referente ao arquivo main */
/* Contém as estruturas e funções comuns à todos os modos*/

#include<stdio.h>
#include<string.h>

typedef struct {
    char removido;
    int idPessoa;
    char nomePessoa[40];
    int idadePessoa;
    char twitterPessoa[15];
}Pessoa;

typedef struct {
    int removido;
    int RRN;
}IndexPessoa;


/* RETORNO:   Ponteiro para este arquivo
/* PARAMETRO: Nome do arquivo binário  */
// Função que lê o arquivo binario cujo nome é "nome"
FILE* le_entrada_binaria(char nome[30], char modo)
{
    FILE *arq;

    arq = fopen(strcat(nome, ".bin"), &modo);

    if(arq == NULL)
    {
        printf()"";
        return NULL;
    }

    return arq;
}
// Função que verifica se o cabeçalho está consistente
int teste_consistencia_cabecalho(FILE *arq)
{
    //Recebi uma cópia do ponteiro do arquivo
    //Espero que manipulá-lo aqui não gere problemas

    /***** Ler o registro de cabeçalho *******/
    int valor;
    fread(&valor, sizeof(int), 1, arq);

    if(!valor)
    {
        printf("Falha no processamento do arquivo");
        return 0;
    }
    else
        return 1;
}