/* Marcos Vinícus Firmino Pietrucci 10770072 */

/* Arquivo principal do trabalho, a partir do qual será ativada as funcionalidades*/
#include"main.h"
#include<stdio.h>
#include<stdlib.h>

/*** As funções abaixo são usadas por 2 ou mais modos diferentes  ***/

// Função que abre um arquivo com o "nome" e o "modo". Retorna um ponteiro para esse arquivo
FILE* le_arquivo(char *nome, char *modo, int modo_entrada)
{
    FILE *arq;

    arq = fopen(nome, modo);

    if(arq == NULL)
    {
        //A entrada 1 possui uma mensagem de erro diferente para o mesmo erro
        if(modo_entrada == 1)
            printf("Falha no carregamento do arquivo.");
        else
            printf("Falha no processamento do arquivo.");
        return NULL;
    }

    return arq;
}

// Função que verifica se o cabeçalho está consistente
int teste_consistencia_cabecalho(FILE *arq, int modo_entrada)
{
    /***** Ler o registro de cabeçalho *******/
    char status;
    fread(&status, sizeof(char), 1, arq);

    //Voltar o ponteiro para o inicio
    fseek(arq, 0, SEEK_SET); 

    if(status == '0')
    {   
        if(modo_entrada == 7)
            printf("Falha no carregamento do arquivo.");
        else if(modo_entrada == 8)
            printf("Falha no processamento do arquivo.");
        return 0;
    }
    else
        return 1;
}

int main()
{
    int modo;

    scanf("%d", &modo);

    return 0;
}
