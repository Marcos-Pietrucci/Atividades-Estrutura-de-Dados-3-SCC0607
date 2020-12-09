#include"arquivoPessoa.h"

//Função que prepara a struct para o padrão de escrita, adicionando os '$' necessários
void prepara_structPessoa(Pessoa *pAux)
{    
    int i, flag = 0;

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

//Função que lê a Pessoa do arquvo cujo RRN é "RRN". Retorna uma estrutura com os dados da pessoa
Pessoa busca_RRN_pessoa(FILE *pessoas_bin, int RRN, int modo_entrada)
{
    //Variáveis auxiliares
    Pessoa pAux;
    char str_lixo[65];
    
    //Ler o registro de cabeçalho, que é lixo
    fseek(pessoas_bin, 0, SEEK_SET);
    fread(str_lixo, sizeof(char), 64, pessoas_bin);

    //Posicionar o ponteiro na posição correta
    fseek(pessoas_bin, RRN*64, SEEK_CUR);

    //Ler os dados
    fread(&pAux.removido, sizeof(char), 1, pessoas_bin);
    if(pAux.removido == '0')
    {
        //Apenas no modo 3 deve-se imprimir uma mensagem de erro
        if(modo_entrada == 3)
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

    //Volta o ponteiro para o início
    fseek(pessoas_bin, 0, SEEK_SET);

    return pAux;
}