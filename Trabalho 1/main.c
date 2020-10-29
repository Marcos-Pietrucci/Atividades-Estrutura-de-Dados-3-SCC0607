/* Marcos Vinícus Firmino Pietrucci 10770072*/
/* Arquivo principal do trabalho, a partir do qual será ativada as funções*/
#include"main.h"
#include"modo1.h"
#include<stdio.h>
#include"modo2.h"

// Função que abre um arquivo com o "nome" e o"modo". Retorna um ponteiro para esse arquivo
FILE* le_arquivo(char *nome, char *modo, int entrada)
{
    FILE *arq;

    arq = fopen(nome, modo);

    if(arq == NULL)
    {
        //A entrada 1 possui uma mensagem de erro diferente
        if(entrada == 1)
            printf("Falha no carregamento do arquivo.");
        else
            printf("Falha no processamento do arquivo.");
        return NULL;
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
        printf("Falha no processamento do arquivo.");
        return 0;
    }
    else
        return 1;
}

//Função que ordena os registros do índice primário pelo idPessoa
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

//Função que escreve um vetor de IndexPesoa no disco
void escreve_index(FILE *index_bin, IndexPessoa * index, int num_pessoas)
{
    //Escrever o registro de cabeçalho
    int i;
    char status = '0';
    fwrite(&status, sizeof(char), 1, index_bin); //Arquivo INCONSISTENTE
    status = '$';
    for(i = 0; i < 7; i++)
        fwrite(&status, sizeof(char), 1, index_bin);

    //Escreve todos os dados
    i = 0;
    while(i != num_pessoas)
    {
        fwrite(&(index[i]).idPessoa, sizeof(int), 1, index_bin);
        fwrite(&(index[i]).RRN, sizeof(int), 1, index_bin);
        i++;
    }

    //Atualiza o registro de cabeçalho
    fseek(index_bin, 0, SEEK_SET);
    status = '1';
    fwrite(&status, sizeof(char), 1, index_bin); //Arquivo CONSISTENTE
}

int main()
{
    int modo;

    scanf("%d", &modo);

    switch(modo)
    {
        case 1: modo1();
                break;

        case 2: modo2();
                break;

        default: printf("Não implementado ainda :)");
                 break;
    }

    return 0;
}