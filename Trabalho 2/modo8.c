#include"modo8.h"
#ifndef FORNECIDO_H_
#define FORNECIDO_H_
#include"fornecido.h"
#endif
#ifndef STDLIB_H
#define STDLIB_H
#include<stdlib.h>
#endif


//Função que inicia a leitura das entradas e o processamento do modo 8
void modo8()
{
    //Continuar com a leitura da entrada
    char nome_pesosas_bin[30], nome_index_bin[30], nome_arqSegue_bin[30];
    int idPessoaBusca;

    //Lê as entradas
    le_entradas_modo8(nome_pesosas_bin, nome_index_bin, &idPessoaBusca, nome_arqSegue_bin);

    FILE *arq_pessoas_bin = le_arquivo(nome_pesosas_bin, "rb", 8);
    if(arq_pessoas_bin == NULL || !teste_consistencia_cabecalho(arq_pessoas_bin, 8))
        return;

    FILE *arq_index_bin = le_arquivo(nome_index_bin, "rb", 8);
    if(arq_index_bin == NULL || !teste_consistencia_cabecalho(arq_index_bin, 8))
        return;

    FILE *arq_segue_bin = le_arquivo(nome_arqSegue_bin, "rb", 8); 
    if(arq_segue_bin == NULL || !teste_consistencia_cabecalho(arq_segue_bin, 8))
        return;

    //Realizar a busca indexada pela pessoa e suas informações
    Pessoa pessoaBusca = busca_pessoa_indexada(arq_pessoas_bin, arq_index_bin, idPessoaBusca);
    if(pessoaBusca.idPessoa == -1)
        return;
    
    //De posse da pessoa a ser buscada, exibir suas informações
    exibe_informacoes_pessoa(pessoaBusca);

    //Realizar a busca de registros no arquivo "segue"
    busca_arqSegue_idPessoaQueSegue(arq_segue_bin, idPessoaBusca);

    fclose(arq_segue_bin);
    fclose(arq_pessoas_bin);
    fclose(arq_index_bin);
}

//Função que lê as entradas do modo 8
void le_entradas_modo8(char *nome_pesosas_bin, char *nome_index_bin, int *idPessoaBusca, char *nome_arqSegue_bin)
{
    char lixo, strlixo[50];
    scanf("%c", &lixo);
    fflush(stdin);
    scanf("%s", nome_pesosas_bin);
    fflush(stdin);
    scanf("%c", &lixo);
    fflush(stdin);
    scanf("%s", nome_index_bin);
    fflush(stdin);
    scanf("%c", &lixo);
    fflush(stdin);
    scanf("%s", strlixo);
    fflush(stdin);
    scanf("%c", &lixo);
    fflush(stdin);
    scanf("%d", idPessoaBusca);
    fflush(stdin);
    scanf("%c", &lixo);
    fflush(stdin);
    scanf("%s", nome_arqSegue_bin);
}

//Função que realiza a busca indexada pela pessoa
Pessoa busca_pessoa_indexada(FILE* arq_pessoas_bin, FILE *arq_index_bin, int idPessoaBusca)
{
    //Pessoa que está sendo buscada
    Pessoa pessoaBusca;

    //Lê o index da memória
    int num_pessoas;
    IndexPessoa *index = le_index(arq_index_bin, &num_pessoas);

    //Inicia a busca pela pessoa
    int RRN = busca_binaria_index(index, num_pessoas, idPessoaBusca, 3);
    if(RRN == -1)
    {
        pessoaBusca.idPessoa = -1;
        return pessoaBusca;
    }
    
    //De posse do RRN, buscar a pessoa
    pessoaBusca = busca_RRN_pessoa(arq_pessoas_bin, RRN, 3);
        
    return pessoaBusca;
}

void exibe_informacoes_pessoa(Pessoa pAux)
{
    //Exibe as informações da Pessoa conforme formatação indicada
    int flag_idade;
    if(pAux.nomePessoa[0] == '\0')
    {
        pAux.nomePessoa[0] = '-';
        pAux.nomePessoa[1] = '\0';
    }
    if(pAux.idadePessoa == -1)
        flag_idade = 1;

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

//Fimção que exibe na tela as informações da relação "Segue" cujo índice é "indc_no_vetor"
void exibe_informacoes_segue(Segue *vetSegue, int indc_no_vetor)
{
    //Exibe informações do relacionamento "Segue" conforme formatação indicada
    Segue aux = vetSegue[indc_no_vetor];
    printf("Segue a pessoa de código: %d", aux.idPessoaQueESeguida);
    printf("\nJustificativa para seguir: ");

    char amiz = aux.grauAmizade[0];
    switch (amiz)
    {
        case '0': printf("segue porque é uma celebridade");
                  break;

        case '1': printf("segue porque é amiga de minha amiga");
                  break;

        case '2': printf("segue porque é minha amiga");
                  break;
    }

    printf("\nComeçou a seguir em: %s", aux.dataInicioQueSegue);
    printf("\nParou de seguir em: %s\n\n", aux.dataFimQueSegue);

}

//Função que busca e exibe todos os registros que possuem um determinado "idPessoaQueSegue"
void busca_arqSegue_idPessoaQueSegue(FILE *arq_segue_bin, int idPessoaQueSegue)
{
    //Lê o vetor "segue" da memória
    int num_segue;
    Segue *vetSegue = le_dados_arqSegue_BIN(arq_segue_bin, &num_segue);

    //Busca binária pelo índice no vetor correspondente ao registro com "idPessoaQueSegue"
    int i;
    int indc_no_vetor = busca_binaria_arqSegue(vetSegue, num_segue, idPessoaQueSegue, 8);
    i = indc_no_vetor;

    //Navegar PARA TRÁS no vetor de registros
    i--;
    while(vetSegue[i].idPessoaQueSegue == idPessoaQueSegue)
        i--;

    i++;

    //Exibe as informações de trás para frente
    while(vetSegue[i].idPessoaQueSegue == idPessoaQueSegue)
    {
        exibe_informacoes_segue(vetSegue, i);
        i++;
    }    
}
