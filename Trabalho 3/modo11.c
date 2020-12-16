/* Marcos Vinícius Firmino Pietrucci 10770072*/

#include"modo11.h"
#include"fornecido.h"
#include"grafo.h"
#include"arquivoIndex.h"
#include"arquivoPessoa.h"
#include"arquivoSegue.h"

//Função que organiza e executa o modo 11
void modo11()
{
    //Continuar com a leitura
    char nome_arq_pessoa[30], nome_arq_index[30], nome_arq_segue[30], nomeCelebridade[40];
    le_entradas_modo11(nome_arq_pessoa, nome_arq_index, nome_arq_segue, nomeCelebridade);

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

    //Iniciar a busca em largura
    int *vetAntecessores = buscaLargura_Grafo(gr_t, nomeCelebridade);

    //Imprimir os resultados
    imprime_modo11(gr_t, vetAntecessores, nomeCelebridade);

    //Libera todos os itens alocados
    libera_grafo(gr);
    libera_grafo(gr_t);
    fclose(arq_pessoa);
    fclose(arq_index);
    fclose(arq_segue);
}

//Função que lê as entradas do modo 11
void le_entradas_modo11(char *nome_arq_pessoa, char *nome_arq_index, char * nome_arq_segue, char *nomeCelebridade)
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

void imprime_modo11(Grafo *gr_t, int *vetAntecessores, char *nomeCelebridade)
{
     //Imprimir todos os resultados
    int indc = 0, i;
    Vertice *aux;    
    int indc_busca = get_indc_vertice(gr_t, nomeCelebridade);
    
    //Varrer todos os vértices
    for(i = 0; i < gr_t->n ; i ++)
    {   
        if(indc_busca == i)
            continue;
        indc = vetAntecessores[i];

        //Buscar por uma conexão entre o vértice atual e o objetivo
        while(indc != -1 && indc != indc_busca)
        {
            indc = vetAntecessores[indc];
        }
        
        //Caso tenha encontrado
        if(indc == indc_busca)
        {
            //Imprimir o nome da pessoa
            aux = get_vertice_de_indice(gr_t, i);
            printf("%s", aux->nomePessoa);

            //Voltar ao início e imprimir o caminho
            indc = vetAntecessores[i];
            do
            {
                aux = get_vertice_de_indice(gr_t, indc);
                printf(", %s", aux->nomePessoa);
                indc = vetAntecessores[indc];
            }while(indc != -1);

        }
        else //Caso não tenha encontrado
        {   
            //Imprimir apenas a mensagem de não seguir
            aux = get_vertice_de_indice(gr_t, i);
            printf("%s, NAO SEGUE A CELEBRIDADE", aux->nomePessoa);

        }
        printf("\n");
    }
}