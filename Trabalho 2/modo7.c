/* Marcos Vinícus Firmino Pietrucci 10770072 */

#include"header/modo7.h"
#include"header/fornecido.h"
#ifndef STDLIB_H
#define STDLIB_H
#include<stdlib.h>
#endif

//Função que inicia a leitura das entradas e o processamento do modo 6
void modo7()
{
    //Continuar com a leitura
    char arq_segue_nome[15], nome_arq_ordenado[15];

    le_entradas_modo7(arq_segue_nome, nome_arq_ordenado);

    FILE *arq_segue = le_arquivo(arq_segue_nome, "rb", 1);
    if(arq_segue == NULL && !teste_consistencia_cabecalho(arq_segue, 7) ) 
        return;
    FILE *arq_ordenado = le_arquivo(nome_arq_ordenado, "wb", 1);
    if(arq_ordenado == NULL)
        return;
    
    //Lê os dados do arquivo
    int num_segue = 0;
    Segue *vetSegue = le_dados_arqSegue_BIN(arq_segue, &num_segue);

    //Ordena os dados
    ordena_vetSegue(vetSegue, num_segue);
}

void le_entradas_modo7(char *arq_segue_nome, char *nome_arq_ordenado)
{
    char lixo;
    scanf("%c", &lixo);
    fflush(stdin);
    scanf("%s", arq_segue_nome);
    fflush(stdin);
    scanf("%c", &lixo);
    fflush(stdin);    
    scanf("%s", nome_arq_ordenado);
}

int compara_vetSegue(Segue a, Segue b)
{
    if(a.idPessoaQueSegue > b.idPessoaQueSegue ||
       a.idPessoaQueESeguida > b.idPessoaQueESeguida ||
       strcmp(a.dataInicioQueSegue, b.dataInicioQueSegue) > 0 || //Não tenho certeza disso aqui
       strcmp(a.dataFimQueSegue, b.dataFimQueSegue) > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void ordena_vetSegue(Segue *vetSegue, int num_segue)
{
    //Será utilizado insertion sort para ordenar
    int i, j;
    Segue key;  
    for (i = 1; i < num_segue; i++) 
    {  
        key = vetSegue[i];  
        j = i - 1;  
        while (j >= 0 &&  compara_vetSegue(vetSegue[j], key)) 
        {  
            vetSegue[j + 1] = vetSegue[j];  
            j = j - 1;  
        }  
        vetSegue[j + 1] = key;  
    }  

}