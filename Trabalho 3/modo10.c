/* Marcos Vinícius Firmino Pietrucci 10770072*/

#include"modo10.h"
#include"grafo.h"

//Função que inicia o modo 10
void modo10()
{
    //Continuar com a leitura
    char nome_arq_pessoa[30], nome_arq_index[30], nome_arq_segue[30];
    le_entradas_modo10(nome_arq_pessoa, nome_arq_index, nome_arq_segue);

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

    //Transpor o grafo lido
    Grafo *gr_t = transpoe_grafo(gr);

    //Apresentar resultado
    imprime_grafo(gr_t);

    //Libera todos os itens alocados
    libera_grafo(gr);
    libera_grafo(gr_t);
    fclose(arq_pessoa);
    fclose(arq_index);
    fclose(arq_segue);
}

//Função que lê as entradas do modo 10
void le_entradas_modo10(char *nome_arq_pessoa, char *nome_arq_index, char *nome_arq_segue)
{
    char lixo;
    scanf("%c", &lixo);
    scanf("%s", nome_arq_pessoa);
    scanf("%c", &lixo);
    scanf("%s", nome_arq_index);
    scanf("%c", &lixo);
    scanf("%s", nome_arq_segue);
}