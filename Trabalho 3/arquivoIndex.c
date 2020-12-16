#include"arquivoIndex.h"

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
    
    return -1;
}