/* Marcos Vinícus Firmino Pietrucci 10770072 */

#include"modo4.h"
#ifndef STDLIB_H
#define STDLIB_H
#include<stdlib.h>
#endif
#ifndef FORNECIDO_H_
#include"fornecido.h"
#define FORNECIDO_H_
#endif

//Função que inicia a leitura das entradas e o processamento do modo
void modo4()
{
    //Continuar com a leitura
    char nome_arq_bin[15], nome_index_bin[15];
    int n;
    le_entradas_modo4(nome_arq_bin, nome_index_bin, &n);

    //Abre e testa a consistência dos arquivos
    FILE *pessoas_bin = le_arquivo(nome_arq_bin, "rb+", 4); //Aberto no modo rb+ para permitir escrita no começo do arquivo
    if(pessoas_bin == NULL || !teste_consistencia_cabecalho(pessoas_bin))
        return;
    FILE *index_bin = le_arquivo(nome_index_bin, "rb", 4); //Aberto no modo ab+ para permitir leitura e escrita no final do arquivo
    if(index_bin == NULL || !teste_consistencia_cabecalho(index_bin))
        return;

    //Ler as entradas iterativamente e inserir o arquivo adequado  
    int num_pessoas = 0;
    IndexPessoa* index = insere_pessoas_bin(pessoas_bin, index_bin, n, &num_pessoas);

    //Ordenar o index com todos os registros
    ordena_index(index, num_pessoas);

    //Reescrever o arquivo de índice
    escreve_index(index_bin, index, num_pessoas);

    fclose(pessoas_bin);
    fclose(index_bin);

    binarioNaTela1(nome_arq_bin,nome_index_bin);
}

void le_entradas_modo4(char *nome_arq_bin, char *nome_index_bin, int *n)
{
    //Lê todas as entradas
    char lixo; 
    scanf("%c",&lixo);
    fflush(stdin);
    scanf("%s", nome_arq_bin);
    fflush(stdin);
    scanf("%c", &lixo);
    fflush(stdin);
    scanf("%s", nome_index_bin);
    fflush(stdin);
    scanf("%c", &lixo);
    fflush(stdin);
    scanf("%d", n);
}

IndexPessoa* insere_pessoas_bin(FILE *pessoas_bin, FILE *index_bin, int n, int *num_pessoas)
{
    //Escrita do registro de cabeçalho do pessoas_bin
    char status = '0';
    fwrite(&status, sizeof(char), 1, pessoas_bin); //Arquivo inconsistente
    
    //Posicionar o ponteiro do arquivo de pessoas no fim
    fseek(pessoas_bin, 0, SEEK_END);

    //Variáveis auxiliares
    Pessoa pAux;
    char substrsing[50], lixo;

    //Indica o registro como não removido
    pAux.removido = '1'; 

    //Lê os índices
    IndexPessoa *index = le_index(index_bin, num_pessoas);
    
    //Ler os registros em loop
    int cont;
    for(cont = 0; cont < n; cont++)
    {
        //Lê o ID da pessoa
        scanf("%d", &pAux.idPessoa);
        fflush(stdin);

        //Lê o espaço
        scanf("%c", &lixo);
        fflush(stdin);

        //Lê a string do nome
        scan_quote_string(substrsing, 40);
        if(substrsing[0] == '\0') //Caso o nome seja NULO
            pAux.nomePessoa[0] = '\0'; //Marcar para remoção do nome
        else
        {
            substrsing[39] = '\0';  //Truncamento do nome
        }
        strcpy(pAux.nomePessoa, substrsing);
        fflush(stdin);

        //Lê o espaço
        scanf("%c", &lixo);
        fflush(stdin);

        //Lê o número da pessoa
        scanf("%s", substrsing); //Vamos ler como uma string, pois pode ser um número ou "NULO"
        if(substrsing[0] == 'N')
            pAux.idadePessoa = -1;
        else
            pAux.idadePessoa = atoi(substrsing);

        //Lê o espaço
        scanf("%c", &lixo);
        fflush(stdin);

        //Lê o twitter da pessoa
        scan_quote_string(substrsing, 15);
        substrsing[14] = '\0';  //Trucamento do twitter
        strcpy(pAux.twitterPessoa, substrsing);
        fflush(stdin);       

        //Feita toda a leitura, preparar os dados para a escrita
        prepara_structPessoa(&pAux);

        //Escreve o registro lido no disco
        fseek(pessoas_bin, 0, SEEK_END);
        fwrite(&pAux.removido, sizeof(char), 1, pessoas_bin);
        fwrite(&pAux.idPessoa, sizeof(int), 1, pessoas_bin);
        fwrite(&pAux.nomePessoa, sizeof(char), 40, pessoas_bin);
        fwrite(&pAux.idadePessoa, sizeof(int), 1, pessoas_bin);
        fwrite(&pAux.twitterPessoa, sizeof(char), 15, pessoas_bin);

        //Adicionar no vetor de index
        index = realloc(index, sizeof(IndexPessoa)*((*num_pessoas) + 1));
        index[*num_pessoas].idPessoa = pAux.idPessoa;
        index[*num_pessoas].RRN = *num_pessoas;
        (*num_pessoas)++;
    }
    
    //Atualiza o registro de cabeçalho do pessoas_bin
    status = '1';
    fseek(pessoas_bin, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, pessoas_bin);  //Arquivo consistente
    fwrite(num_pessoas, sizeof(int), 1, pessoas_bin);

    return index;
}


