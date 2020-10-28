/* Marcos Vinícus Firmino Pietrucci 10770072*/
/* Arquivo principal do trabalho, a partir do qual será ativada as funções*/

#include"main.h"
#include"modo1.h"
#include<stdio.h>

FILE* le_arquivo(char *nome,char modo)
{
    FILE *arq;

    arq = fopen(nome, &modo);

    if(arq == NULL)
    {
        printf("Falha no processamento do arquivo");
        return NULL;
    }

    return arq;
}

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


int main()
{
    int modo;

    scanf("%d", &modo);

    switch(modo)
    {
        case 1: modo1();
                break;
    
    }

    return 0;
}