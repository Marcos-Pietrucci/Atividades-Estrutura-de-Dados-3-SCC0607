/* Marcos Vinícus Firmino Pietrucci 10770072 */

/* Arquivo principal do trabalho, a partir do qual será ativada as funcionalidades*/
#include"main.h"
#include"modo9.h"
#include<stdio.h>
#include<stdlib.h>

/*** As funções abaixo são usadas por 2 ou mais modos diferentes  ***/

// Função que abre um arquivo com o "nome" e o "modo". Retorna um ponteiro para esse arquivo
FILE* le_arquivo(char *nome, char *modo)
{
    FILE *arq;

    arq = fopen(nome, modo);

    if(arq == NULL)
    {
        printf("Falha na execução da funcionalidade.");
        return 0;
    }

    return arq;
}

// Função que verifica se o cabeçalho está consistente
int teste_consistencia_cabecalho(FILE *arq)
{
    /***** Ler o registro de cabeçalho *******/
    char status;
    fread(&status, sizeof(char), 1, arq);

    //Voltar o ponteiro para o inicio
    fseek(arq, 0, SEEK_SET); 

    if(status == '0')
    {    
        printf("Falha na execução da funcionalidade.");
        return 0;
    }
    else
        return 1;
}

int main()
{
    int modo;

    scanf("%d", &modo);

    switch (modo)
    {
        case 9: modo9();
                break;

        default: printf("Não implementado ainda");
                break;
    }

    return 0;
}
