/* Marcos Vinícius Firmino Pietrucci 10770072*/

#include"modo12.h"
#include"fornecido.h"
#include"grafo.h"
#include"arquivoIndex.h"
#include"arquivoPessoa.h"
#include"arquivoSegue.h"

void modo12()
{
    //Continuar com a leitura
    char nome_arq_pessoa[30], nome_arq_index[30], nome_arq_segue[30], nomeCelebridade[40];
    le_entradas_modo12(nome_arq_pessoa, nome_arq_index, nome_arq_segue, nomeCelebridade);

    //Abrir os arquivos necessários
    FILE *arq_pessoa = le_arquivo(nome_arq_pessoa, "rb");
    if(arq_pessoa == NULL || !teste_consistencia_cabecalho(arq_pessoa))
        return;
    
    FILE *arq_index = le_arquivo(nome_arq_index, "rb");
    if(arq_index == NULL || !teste_consistencia_cabecalho(arq_index))
        return;

    FILE *arq_segue = le_arquivo(nome_arq_segue, "rb");
    if(arq_segue == NULL || !teste_consistencia_cabecalho(arq_segue))
        return;

    //Lê o arquivo pessoas e gera um grafo
    Grafo *gr = leitura_arq_pessoa_gera_grafo(arq_pessoa, arq_index, arq_segue);

    //Iniciar a busca em profundidade
    int val = busca_em_profundidade(gr,nomeCelebridade);

    if(val == -1)
        printf("A FOFOCA NAO RETORNOU\n");
    else
    {
        printf("%d\n", val);
    }
    
    

    //Libera todos os itens alocados
    libera_grafo(gr);
    fclose(arq_pessoa);
    fclose(arq_index);
    fclose(arq_segue);
}

//Função que lê as entradas do modo 12
void le_entradas_modo12(char *nome_arq_pessoa, char *nome_arq_index, char * nome_arq_segue, char *nomeCelebridade)
{
    char lixo;
    scanf("%c", &lixo);
    scanf("%s", nome_arq_pessoa);
    scanf("%c", &lixo);
    scanf("%s", nome_arq_index);
    scanf("%c", &lixo);
    scanf("%s", nome_arq_segue);
    scanf("%c", &lixo);
    scan_quote_string(nomeCelebridade);
}
