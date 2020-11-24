/* Marcos Vinícus Firmino Pietrucci 10770072 */

/* Arquivo principal do trabalho, a partir do qual será ativada as funcionalidades*/
#include"main.h"
#include"modo6.h"
#include"modo7.h"
#include<stdio.h>
#include<stdlib.h>

/*** As funções abaixo são usadas por 2 ou mais modos diferentes  ***/

// Função que abre um arquivo com o "nome" e o "modo". Retorna um ponteiro para esse arquivo
FILE* le_arquivo(char *nome, char *modo, int modo_entrada)
{
    FILE *arq;

    arq = fopen(nome, modo);

    if(arq == NULL)
    {
        //A entrada 1 possui uma mensagem de erro diferente para o mesmo erro
        if(modo_entrada == 1)
            printf("Falha no carregamento do arquivo.");
        else
            printf("Falha no processamento do arquivo.");
        return NULL;
    }

    return arq;
}

// Função que verifica se o cabeçalho está consistente
int teste_consistencia_cabecalho(FILE *arq, int modo_entrada)
{
    /***** Ler o registro de cabeçalho *******/
    char status;
    fread(&status, sizeof(char), 1, arq);

    //Voltar o ponteiro para o inicio
    fseek(arq, 0, SEEK_SET); 

    if(status == '0')
    {   
        if(modo_entrada == 7)
            printf("Falha no processamento do arquivo.");
        return 0;
    }
    else
        return 1;
}

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

//Função que lê um vetor de IndexPesoa do disco. Carrega estes dados num vetor
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

    //Volta o ponteiro para o início
    fseek(index_bin, 0, SEEK_SET);

    return index;
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
    fseek(index_bin, 0, SEEK_SET);
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

//Função que realiza uma busca binária no índice primário pelo RRN correspondente ao ID buscado
int busca_binaria_index(IndexPessoa *index, int num_pessoas, int idPessoa, int modo_entrada)
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

    //Apenas no modo 3 deve-se imprimir uma mensagem de erro
    if(modo_entrada == 3)
        printf("Registro inexistente.");
    return -1;
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

Segue* le_dados_arqSegue_BIN(FILE *arq_segue, int *num_segue)
{
    //Variáveis axuliares
    *num_segue = -1;
    Segue *vetSegue = malloc(sizeof(Segue));
    Segue auxSegue;
    char str_lixo[35], lixo;

    //Verifica o status
    fread(&lixo, sizeof(char), 1, arq_segue);
    if(lixo == '0')
    {
        printf("Falha no carregamento do arquivo.");
        return NULL;
    }

    //Lê o restante do registro de cabeçalho
    fread(str_lixo, sizeof(char), 31, arq_segue);

    //Inicia a leitura dos dados
    while(fread(&auxSegue.removido, sizeof(char), 1, arq_segue) != 0)
    {
        if(auxSegue.removido == '0')
        {
            //Lê o restante do registro de cabeçalho
            fread(str_lixo, sizeof(char), 31, arq_segue);
        }

        //Lê os dados
        fread(&auxSegue.idPessoaQueSegue, sizeof(int), 1, arq_segue);
        fread(&auxSegue.idPessoaQueESeguida, sizeof(int), 1, arq_segue);
        fread(&auxSegue.grauAmizade, sizeof(char), 3, arq_segue);
        fread(&auxSegue.dataInicioQueSegue, sizeof(char), 10, arq_segue);
        fread(&auxSegue.dataFimQueSegue, sizeof(char), 10, arq_segue);
        auxSegue.dataInicioQueSegue[10] = '\0';
        auxSegue.dataFimQueSegue[10] = '\0';
        (*num_segue)++;

        //Aloca no vetor
        vetSegue = realloc(vetSegue, sizeof(Segue)*((*num_segue) + 1));

        //Armazena o index lido no vetor
        vetSegue[*num_segue] = auxSegue;
    }
    (*num_segue)++;

    //Volta o ponteiro para o início
    fseek(arq_segue, 0, SEEK_SET);

    return vetSegue;
}


void escreve_arqSegue(FILE *arq_segue, Segue *vetSegue, int num_segue)
{
    //Escrever o registro de cabeçalho
    int i;
    char status = '0';
    fseek(arq_segue, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, arq_segue); //Arquivo INCONSISTENTE
    fwrite(&num_segue, sizeof(int), 1, arq_segue);
    status = '$';
    for(i = 0; i < 27; i++)
        fwrite(&status, sizeof(char), 1, arq_segue);

    //Escreve todos os dados
    i = 0;
    while(i != num_segue)
    {
        fwrite(&(vetSegue[i]).removido, sizeof(char), 1, arq_segue);
        fwrite(&(vetSegue[i]).idPessoaQueSegue, sizeof(int), 1, arq_segue);
        fwrite(&(vetSegue[i]).idPessoaQueESeguida, sizeof(int), 1, arq_segue);
        fwrite(&(vetSegue[i]).grauAmizade, sizeof(char), 3, arq_segue);
        fwrite(&(vetSegue[i]).dataInicioQueSegue, sizeof(char), 10, arq_segue);
        fwrite(&(vetSegue[i]).dataFimQueSegue, sizeof(char), 10, arq_segue);
        i++;
    }

    //Atualiza o registro de cabeçalho
    fseek(arq_segue, 0, SEEK_SET);
    status = '1';
    fwrite(&status, sizeof(char), 1, arq_segue); //Arquivo CONSISTENTE

}

int main()
{
    int modo;

    scanf("%d", &modo);

    switch(modo)
    {
        case 6: modo6();
                break;

        case 7: modo7();
                break;

        default: printf("Ainda não foi implementado");
                 break;
    }

    return 0;
}
