/* Marcos Vinícus Firmino Pietrucci 10770072 */

#include"header/modo6.h"
#include"header/fornecido.h"
#ifndef STDLIB_H
#define STDLIB_H
#include<stdlib.h>
#endif

//Função que inicia a leitura das entradas e o processamento do modo
void modo6()
{
    //Continua com a leitura
    char nome_arq_csv[15], nome_arq_bin[15];

    le_entradas_modo6(nome_arq_csv, nome_arq_bin);

    FILE *arq_csv = le_arquivo(nome_arq_bin, "rb", 1);
    if(arq_csv == NULL)
        return;
    FILE *arq_segue_bin = le_arquivo(nome_arq_bin, "wb", 1);
    if(arq_segue_bin == NULL)
        return;

    int num_segue = 0;
    Segue *vetSegue = le_dados_arqSegue_CSV(arq_csv, &num_segue);

    escreve_arqSegue(arq_segue_bin, vetSegue, num_segue);

    fclose(arq_csv);
    fclose(arq_segue_bin);

    // binarioNaTela1(nome_arq_bin, ) Impossível de ser usado no momento
}

void le_entradas_modo6(char *nome_arq_csv, char *nome_arq_bin)
{
    char lixo;
    scanf("%c", &lixo);
    fflush(stdin);
    scanf("%s", nome_arq_csv);
    fflush(stdin);
    scanf("%c", &lixo);
    fflush(stdin);    
    scanf("%s", nome_arq_bin);
}

Segue* le_dados_arqSegue_CSV(FILE *arq_csv, int *num_segue)
{
    //Criando e alocando o vetor de Segue
    Segue *vetSegue = malloc(sizeof(Segue));
    *num_segue = 0;

    //Cria variáveis axuliares
    char lixo, strLixo[80];
    Segue segueAux;

    //Lê a primeira linha do arquivo (que contém lixo)
    fscanf(arq_csv, "%s", strLixo);

    while(fscanf(arq_csv, "%c", &segueAux.removido) != -1)
    {
        if(segueAux.removido == '0')
        {
            //O registro foi removido, ler o restante como lixo
            fread(strLixo, sizeof(char), 31, arq_csv);
            continue;
        }

        //Lê uma virgula
        fscanf(arq_csv, "%c", &lixo);

        //Lê o ID que segue
        fscanf(arq_csv, "%d", &segueAux.idPessoaQueSegue);

        //Lê uma virgula
        fscanf(arq_csv, "%c", &lixo);

        //Lê o ID que é seguida
        fscanf(arq_csv, "%d", &segueAux.idPessoaQueESeguida);

        //Lê uma virgula
        fscanf(arq_csv, "%c", &lixo);

        //Lê o grau de amizade
        fscanf(arq_csv, "%c", &lixo); //Lê o indicador
        fread(strLixo, sizeof(char), 2, arq_csv); //Lê o \0 e o $
        segueAux.grauAmizade[0] = lixo;
        segueAux.grauAmizade[1] = '\0';
        segueAux.grauAmizade[2] = '$';

        //Lê a data de início que segue
        fread(&segueAux.dataInicioQueSegue, sizeof(char), 10, arq_csv);

        //Lê a data de fim que segue
        fread(&segueAux.dataFimQueSegue, sizeof(char), 10, arq_csv);

        //Considerando que os arquivos não precisam de truncamento nem assumem valores nulos
        vetSegue = realloc(vetSegue, sizeof(Segue) * ((*num_segue) + 1));
        vetSegue[*num_segue] = segueAux;
        (*num_segue)++;

    }

    return vetSegue;
}