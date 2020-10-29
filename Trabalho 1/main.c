/* Marcos Vinícus Firmino Pietrucci 10770072*/
/* Arquivo principal do trabalho, a partir do qual será ativada as funções*/
#include"main.h"
#include"modo1.h"
#include"modo2.h"
#include"modo3.h"
#include<stdio.h>
#include<stdlib.h>


// Função que abre um arquivo com o "nome" e o "modo". Retorna um ponteiro para esse arquivo
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
void escreve_index(FILE *index_bin, IndexPessoa *index, int num_pessoas)
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

IndexPessoa* le_index(FILE *index_bin, int *num_pessoas)
{
    //Variáveis axuliares
    *num_pessoas = -1;
    IndexPessoa *index = malloc(sizeof(IndexPessoa));
    IndexPessoa indxAux;

    //Lê o registro de cabeçalho que contém lixo
    char str_lixo[10];
    fread(str_lixo, sizeof(char), 8, index_bin);

    //Inicia a leitura dos dados
    while(fread(&indxAux.idPessoa, sizeof(int), 1, index_bin) != 0)
    {
        fread(&indxAux.RRN, sizeof(int), 1, index_bin);
        (*num_pessoas)++;
        index = realloc(index, sizeof(IndexPessoa)*((*num_pessoas) + 1));

        //Armazena o index lido no vetor
        index[*num_pessoas].idPessoa = indxAux.idPessoa;
        index[*num_pessoas].RRN = indxAux.RRN;
    }
    (*num_pessoas)++;

    return index;
}

int busca_binaria_index(IndexPessoa *index, int num_pessoas, int idPessoa)
{
    //Algoritmo da busca binária
    int inf = 0;
    int sup = num_pessoas-1;
    int meio;
    while(inf <= sup)
    {
        meio = (inf+sup)/2;

        if(index[meio].idPessoa == idPessoa)
            return index[meio].RRN;
        
        else if(index[meio].idPessoa > idPessoa)
            sup = meio-1;
        else
            inf = meio+1;
    }

    //Não encontrou o registro com este ID
    printf("Registro inexistente.");
    return -1;
}

Pessoa busca_RRN_pessoa(FILE *pessoas_bin, int RRN)
{
    //Variáveis auxiliares
    Pessoa pAux;
    char str_lixo[65];
    
    //Ler o registro de cabeçalho, que é lixo
    fread(str_lixo, sizeof(char), 64, pessoas_bin);

    //Posicionar o ponteiro na posição correta
    fseek(pessoas_bin, RRN*64, SEEK_CUR);

    //Ler os dados
    fread(&pAux.removido, sizeof(char), 1, pessoas_bin);
    if(pAux.removido == '0')
    {
        printf("Registro inexistente.");
        pAux.idPessoa = -1;
    }
    else
    {
        //Lê o ID no arquivo
        fread(&pAux.idPessoa, sizeof(int), 1, pessoas_bin);

        //Lê o nome no arquivo
        fread(&pAux.nomePessoa, sizeof(char), 40, pessoas_bin);
        //Caso o nome seja nulo, adicionar o hifen
        if(pAux.nomePessoa[0] == '\0')
        {
            pAux.nomePessoa[0] = '-';
            pAux.nomePessoa[1] = '\0';
        }

        //Lê a idade no arquivo
        fread(&pAux.idadePessoa, sizeof(int), 1, pessoas_bin);

        //Lê o twitter no arquivo
        fread(&pAux.twitterPessoa, sizeof(char), 15, pessoas_bin);
    }

    return pAux;
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
        
        case 3: modo3();
                break;

        default: printf("Não implementado ainda :)");
                 break;
    }

    return 0;
}