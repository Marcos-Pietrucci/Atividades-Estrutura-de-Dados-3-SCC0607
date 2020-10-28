#include"modo1.h"

#ifndef STDLIB_H
#define STDLIB_H
#include<stdlib.h>
#endif
#ifndef DECLARA_MAIN_MODO1
#define DECLARA_MAIN_MODO1
#include"main.h"
#endif


void modo1()
{
    //Já foi lido o valor inicial, continuar com a leitura
    char arq_csv[15], arq_bin[15], index_bin[15];

    le_entradas_modo1(arq_csv, arq_bin, index_bin);

    //Le o arquivo CSV das entradas
    FILE *arq = le_arquivo(arq_csv,'r');

    if(arq == NULL)
        return;
  
    //Proceder para a leitura do arquivo CSV
    int num_pessoa = 0;
    Pessoa *vetP = le_dados_csv(arq, &num_pessoa);


}

void le_entradas_modo1(char *arq_csv, char *arq_bin, char *index_bin)
{
    //Lê o espaço e o nome do arquvo a ser lido
    char lixo; 
    scanf("%c",&lixo);
    fflush(stdin);
    scanf("%s", arq_csv);
    fflush(stdin);
    scanf("%c", &lixo);
    fflush(stdin);
    scanf("%s", arq_bin);
    fflush(stdin);
    scanf("%s", index_bin);

}

Pessoa* le_dados_csv(FILE* arq, int *num_pessoas)
{
    Pessoa *p = (Pessoa*) malloc(sizeof(Pessoa));
    *num_pessoas = 0;

    Pessoa pAux;
    int indc, flag = 0;

    char lixo = (char) 0;
    char str_id[2];
    str_id[0] = 1;
    str_id[1] = 1;

    //Lê a primeira linha do arquivo, que contém dados invalidos
    fscanf(arq, "%s", str_id);
    fscanf(arq, "%c", &lixo);

    //Lê os dados
    while(fread(str_id, sizeof(char), 2, arq) == 2)
    {
        //Li o id como um char
        if(str_id[1] == ',')
        {
            str_id[1] = '\0';
            flag = 1;
        }
        pAux.idPessoa = atoi(str_id);

        //Lê uma virgula
        if(!flag)     
            fscanf(arq, "%c", &lixo);
        else
            flag = 0;
        
        //Lê o nome no arquivo
        indc = 0;
        fscanf(arq, "%c", &lixo);
        while(lixo != ',')
        { 
            pAux.nomePessoa[indc++] = lixo;

            fscanf(arq, "%c", &lixo);    
        }
        pAux.nomePessoa[indc] = '\0';
        
        //Lê a idade no arquivo
        fscanf(arq, "%d", &pAux.idadePessoa);

        //Lê uma virgula
        fscanf(arq, "%c", &lixo);

        //Lê o twitter no arquivo
        indc = 0;
        fscanf(arq, "%c", &lixo);
        while(lixo != '\n' && !feof(arq))
        { 
            pAux.twitterPessoa[indc++] = lixo;
            if(!feof(arq))
                fscanf(arq, "%c", &lixo);         
        }
        pAux.twitterPessoa[indc] = '\0';

        printf("\nTemos: %d | %s | %d | %s", pAux.idPessoa, pAux.nomePessoa, pAux.idadePessoa, pAux.twitterPessoa);
    }
    return p;
    //while(fread(&Nodo.id, sizeof(int), 1, arq) != 0)


}
