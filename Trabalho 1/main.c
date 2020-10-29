/* Marcos Vinícus Firmino Pietrucci 10770072*/
/* Arquivo principal do trabalho, a partir do qual será ativada as funções*/

#include"main.h"
#include"modo1.h"
#include<stdio.h>

FILE* le_arquivo(char *nome, char *modo)
{
    FILE *arq;

    arq = fopen(nome, modo);

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

void ordena_index(IndexPessoa *index, int num_pessoas)
{
    //Será utilizado insertion sort para ordenar
    int i, j;
    IndexPessoa key;  
    for (i = 1; i < num_pessoas; i++) 
    {  
        key = index[i];  
        j = i - 1;  
        while (j >= 0 && (index[j]).idPessoa >  key.idPessoa) 
        {  
            index[j + 1] = index[j];  
            j = j - 1;  
        }  
        index[j + 1] = key;  
    }  
}

void escreve_index(FILE *index_bin, IndexPessoa * index, int num_pessoas)
{
    //Escrever o registro de cabeçalho
    int i;
    char status = '0';
    fwrite(&status, sizeof(char), 1, index_bin); //Arquivo inconsistente
    status = '$';
    for(i = 0; i < 7; i++)
        fwrite(&status, sizeof(char), 1, index_bin);

    i = 0;
    while(i != num_pessoas)
    {
        fwrite(&(index[i]).idPessoa, sizeof(int), 1, index_bin);
        fwrite(&(index[i]).RRN, sizeof(int), 1, index_bin);
        i++;
    }
    
    fseek(index_bin, 0, SEEK_SET);
    status = '1';
    fwrite(&status, sizeof(char), 1, index_bin); //Arquivo inconsistente
    status = '$';
    for(i = 0; i < 7; i++)
        fwrite(&status, sizeof(char), 1, index_bin);
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