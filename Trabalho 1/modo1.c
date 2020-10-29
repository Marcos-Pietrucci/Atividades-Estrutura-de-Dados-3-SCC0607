
#include"modo1.h"
#ifndef STDLIB_H
#define STDLIB_H
#include<stdlib.h>
#endif
#ifndef FORNECIDO_H_
#include"fornecido.h"
#define FORNECIDO_H_
#endif

//Função que inicia a leitura das entradas e o processamento do modo1
void modo1()
{
    //Já foi lido o valor inicial, continuar com a leitura
    char nome_arq_csv[15], nome_arq_bin[15], nome_index_bin[15];

    le_entradas_modo1(nome_arq_csv, nome_arq_bin, nome_index_bin);

    //Le o arquivo CSV das entradas
    FILE *pessoas_csv = le_arquivo(nome_arq_csv, "r", 1);
    FILE *pessoas_bin = le_arquivo(nome_arq_bin, "wb", 1);
    FILE *index_bin = le_arquivo(nome_index_bin, "wb", 1);
    if(pessoas_csv == NULL ||pessoas_bin == NULL || index_bin == NULL)
        return;
    
    //Iniciar a leitura e concomitante escrita dos dados
    int num_pessoas = 0;
    IndexPessoa *index = le_dados_csv(pessoas_csv, pessoas_bin, &num_pessoas);

    fclose(pessoas_csv);
    fclose(pessoas_bin);

    //De posse do vetor de Index, devemos ordená-lo
    ordena_index(index, num_pessoas);

    //De posse do vetor de IndexPessoa ordenado, devemos escreve-lo
    escreve_index(index_bin, index, num_pessoas);

    fclose(index_bin);
    free(index);

    binarioNaTela1(nome_arq_bin, nome_index_bin);

}

//Função que lê as entradas do modo 1
void le_entradas_modo1(char *nome_arq_csv, char *nome_arq_bin, char *nome_index_bin)
{
    //Lê todas as entradas
    char lixo; 
    scanf("%c",&lixo);
    fflush(stdin);
    scanf("%s", nome_arq_csv);
    fflush(stdin);
    scanf("%c", &lixo);
    fflush(stdin);
    scanf("%s", nome_arq_bin);
    fflush(stdin);
    scanf("%s", nome_index_bin);
}

//Função que lê os dados do arquivo CSV, escreve no disco e organiza o index. Retorna um ponteiro para um vetor de IndexPessoa
IndexPessoa* le_dados_csv(FILE *pessoas_csv, FILE *pessoas_bin, int *num_pessoas)
{
    //Escrita do registro de cabeçalho do pessoas_bin
    int i;
    char status = '0';
    fwrite(&status, sizeof(char), 1, pessoas_bin); //Arquivo inconsistente
    fwrite(num_pessoas, sizeof(int), 1, pessoas_bin);
    status = '$';
    for(i = 0; i < 59; i++)
        fwrite(&status, sizeof(char), 1, pessoas_bin);

    //Vetor de index a ser retornado
    IndexPessoa *index = malloc(sizeof(IndexPessoa));
    *num_pessoas = -1;

    /* Variáveis axuliares */
    Pessoa pAux;
    int indc;
    char lixo = (char) 0;
    char str_lixo[50];

    //Lê a primeira linha do arquivo csv, que contém dados invalidos
    fscanf(pessoas_csv, "%s", str_lixo);
    fscanf(pessoas_csv, "%c", &lixo);

    //Lê os dados do arquivo iterativamente
    while(fscanf(pessoas_csv, "%d", &pAux.idPessoa) != -1)
    {
        //Lê uma virgula no arquivo
        fscanf(pessoas_csv, "%c", &lixo);
       
        /* ------------ Lê o nome no arquivo --------------*/
        indc = 0;
        fscanf(pessoas_csv, "%c", &lixo);
        while(lixo != ',' && indc != 39)
        { 
            pAux.nomePessoa[indc++] = lixo;
            fscanf(pessoas_csv, "%c", &lixo); 
        }
        pAux.nomePessoa[indc] = '\0'; //Esse tratamento e a função "prepara_structPessoa" corrige o caso da entrada ser nula
        
        //Caso tenha ocorrido truncamento no nome, continuar lendo lixo
        if(indc == 39)
            while(lixo != ',')
                fscanf(pessoas_csv, "%c", &lixo);                                   
        /*-----------------------------------*/

        //Lê a idade no arquivo
        if(fscanf(pessoas_csv, "%d", &pAux.idadePessoa) == -1)
        {
            //Campo idade nulo
            pAux.idadePessoa = -1;
        }

        //Lê uma virgula no arquivo
        fscanf(pessoas_csv, "%c", &lixo);

        /*--------- Lê o twitter no arquivo -------------*/
        indc = 0;
        fscanf(pessoas_csv, "%c", &lixo);
        while(lixo != '\n' && indc != 14)
        { 
            pAux.twitterPessoa[indc++] = lixo;
            fscanf(pessoas_csv, "%c", &lixo);         
        }
        pAux.twitterPessoa[indc] = '\0';

        //Preparar os dados do registro lido
        prepara_structPessoa(&pAux); 

        //Escreve o registro lidono disco
        fwrite(&pAux.removido, sizeof(char), 1, pessoas_bin);
        fwrite(&pAux.idPessoa, sizeof(int), 1, pessoas_bin);
        fwrite(&pAux.nomePessoa, sizeof(char), 40, pessoas_bin);
        fwrite(&pAux.idadePessoa, sizeof(int), 1, pessoas_bin);
        fwrite(&pAux.twitterPessoa, sizeof(char), 15, pessoas_bin);

        //Adicionar no vetor de index
        (*num_pessoas)++;
        index = realloc(index, sizeof(IndexPessoa)*((*num_pessoas) + 1));
        index[*num_pessoas].idPessoa = pAux.idPessoa;
        index[*num_pessoas].RRN = *num_pessoas;
    }
    //Corrigir o valor do numero de pessoas
    (*num_pessoas)++;

    //Atualiza o registro de cabeçalho do pessoas_bin
    status = '1';
    fseek(pessoas_bin, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, pessoas_bin);  //Arquivo consistente
    fwrite(num_pessoas, sizeof(int), 1, pessoas_bin);

    return index;
}

//Função que prepara a struct para o padrão de escrita, adicionando os '$' necessários e adicionando 'removido'
void prepara_structPessoa(Pessoa *pAux)
{    
    int i, flag = 0;

    //Valor padrão do removido
    pAux->removido = '1'; 

    for(i = 0;i < 15; i++)
    {
        //Ao ativar 'flag', escrever '$' no restante da string
        if(flag)   
            pAux->twitterPessoa[i] = '$';
        //Ao encontrar o final da string, ativar 'flag'
        else if(pAux->twitterPessoa[i] == '\0')
            flag = 1;
    }

    flag = 0;
    for(i = 0; i < 40; i++)
    {
        //Ao ativar 'flag', escrever '$' no restante da string
        if(flag)    
            pAux->nomePessoa[i] = '$';
        //Ao encontrar o final da string, ativar 'flag'
        else if(pAux->nomePessoa[i] == '\0')
            flag = 1;
    }
}
