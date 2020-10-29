#include"modo3.h"
#ifndef STDLIB_H
#define STDLIB_H
#include<stdlib.h>
#endif

//Função que inicia a leitura das entradas e o processamento do modo
void modo3()
{
    //Continuar com a leitura
    char nome_arq_bin[15], nome_index_bin[15], nome_campo[15];

    //Lê as entradas
    Pessoa *PessoaBusca;
    PessoaBusca = le_entradas_modo3(nome_arq_bin, nome_index_bin, nome_campo);

    //Abre os arquivos
    FILE *pessoas_bin = le_arquivo(nome_arq_bin, "rb", 3);
    if(pessoas_bin == NULL || !teste_consistencia_cabecalho(pessoas_bin))
        return;
    FILE *index_bin = le_arquivo(nome_index_bin, "rb", 3);
    if(index_bin == NULL || !teste_consistencia_cabecalho(index_bin))
        return;
    
    //Inicia a busca pelo registro
    busca_registro(pessoas_bin, index_bin, nome_campo, PessoaBusca);

}

Pessoa* le_entradas_modo3(char *nome_arq_bin, char *nome_index_bin, char *nome_campo)
{
    Pessoa *pAux = malloc(sizeof(Pessoa));

    //Adicionadno valores inválidos ao pAux
    pAux->idadePessoa = -1;
    pAux->idPessoa = -1;
    pAux->nomePessoa[0] = '$';
    pAux->nomePessoa[1] = '\0';
    pAux->twitterPessoa[0] = '$';
    pAux->twitterPessoa[1] = '\0';

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
    scanf("%s", nome_campo);

    if(strcmp(nome_campo, "idPessoa") == 0)
    {
        int aux;
        fflush(stdin);
        scanf("%c",&lixo);
        fflush(stdin);
        scanf("%d", &aux);
        pAux->idPessoa = aux;
    }
    else if(strcmp(nome_campo, "idadePessoa") == 0)
    {
        int aux;
        fflush(stdin);
        scanf("%c",&lixo);
        fflush(stdin);
        scanf("%d", &aux);
        pAux->idadePessoa = aux;
    }
    else if(strcmp(nome_campo, "nomePessoa") == 0)
    {
        char str_aux[40];
        fflush(stdin);
        scanf("%c",&lixo);
        fflush(stdin);
        scanf("%s", str_aux);
        strcpy(pAux->nomePessoa, str_aux);
    }
    else if(strcmp(nome_campo, "twitterPessoa") == 0)
    {
        char str_aux[15];
        fflush(stdin);
        scanf("%c",&lixo);
        fflush(stdin);
        scanf("%s", str_aux);
        strcpy(pAux->twitterPessoa, str_aux);
    }

    return pAux;
}

void busca_registro(FILE *pessoas_bin, FILE *index_bin, char *nome_campo, Pessoa *PessoaBusca)
{   
    //Caso a busca seja pelo idPessoa, realizar uma busca indexada
    if(strcmp(nome_campo, "idPessoa") == 0)
    {
        busca_registro_indexada(pessoas_bin, index_bin, PessoaBusca->idPessoa);
        return;
    }

    //Caso não foi solicitado pelo idPessoa, realizar uma busca sequencial
    /* Variáveis axuliares */
    Pessoa pAux;
    int cont = 0, flag_idade = 0;
    char str_lixo[65];

    //Lê o registro de cabeçalho (que contém dados irrelevantes)
    fread(str_lixo, sizeof(char), 64, pessoas_bin);
   
    //Lê os dados do arquivo iterativamente
    while(fread(&pAux.removido, sizeof(char), 1, pessoas_bin) != 0)
    { 
        //Testa se o registro foi removido
        if(pAux.removido == '0')
        {
            //Se foi removido, lê o restante como lixo
            fread(str_lixo, sizeof(char), 63, pessoas_bin);
            continue;
        }
        
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
        if(pAux.idadePessoa == -1)
            flag_idade = 1;

        //Lê o twitter no arquivo
        fread(&pAux.twitterPessoa, sizeof(char), 15, pessoas_bin);

        //Verificar se o registro lido é o registro procurado
        //PessoaBusca possui dados inválidos em todos os campos, menos o que está sendo pesquisado. Por isso este 'if' é seguro
        if(pAux.idadePessoa == PessoaBusca->idadePessoa || strcmp(pAux.nomePessoa, PessoaBusca->nomePessoa) == 0 ||
           strcmp(pAux.twitterPessoa, PessoaBusca->twitterPessoa) == 0)
        {
            cont++;
            //Exibir o registro lido
            printf("Dados da pessoa de código %d", pAux.idPessoa);
            printf("\nNome: %s", pAux.nomePessoa);
            
            //Caso a idade não tenha sido informada
            if(!flag_idade)
                printf("\nIdade: %d anos\nTwitter: %s\n\n", pAux.idadePessoa, pAux.twitterPessoa);
            else
            {
                flag_idade = 0;
                printf("\nIdade: -\nTwitter: %s\n\n", pAux.twitterPessoa);
            }
        }
    }
    //Se nenhum registro foi encontrado
    if(!cont)
        printf("Registro inexistente.");
}

void busca_registro_indexada(FILE *pessoas_bin, FILE *index_bin, int idPessoa)
{
    //Carregar o index para a memória
    int num_pessoas;
    IndexPessoa *index = le_index(index_bin, &num_pessoas);
    if(index == NULL)
        return;
    
    //Realiza uma busca binária no índice primário
    int RRN = busca_binaria_index(index, num_pessoas, idPessoa);
    if(RRN == -1)
        return;
    
    //De posse do RRN, navegar pelo aquivo usando o RRN encontrado para exibir na tela
    Pessoa pAux = busca_RRN_pessoa(pessoas_bin, RRN);
    if(pAux.idPessoa == -1)
        return;
    else
    {
        //Exibir os dados da pessoa
        printf("Dados da pessoa de código %d", pAux.idPessoa);
        printf("\nNome: %s", pAux.nomePessoa);
            
        //Caso a idade não tenha sido informada
        if(pAux.idadePessoa != -1)
            printf("\nIdade: %d anos\nTwitter: %s\n\n", pAux.idadePessoa, pAux.twitterPessoa);
        else
            printf("\nIdade: -\nTwitter: %s\n\n", pAux.twitterPessoa);
    }
}

