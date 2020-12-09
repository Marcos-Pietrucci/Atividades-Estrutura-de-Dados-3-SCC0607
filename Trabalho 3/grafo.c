#include"grafo.h"

/************************ Funções do grafo ***************************/
//Função que cria um grafo e retorna um ponteiro para ele
Grafo* cria_grafo(int n)
{ 
    Grafo *gr;

    //Alocar gr
    gr = (Grafo *) malloc(sizeof(Grafo));
    
    //Cria um vetor de ponteiros de vértices
    gr->lista = (Vertice**) calloc(n, sizeof(Vertice*));
    gr->n = n;

    return gr;
}

//Função que libera todo o grafo adequadamente
void libera_grafo(Grafo *gr)
{
    //Variáveis auxiliares
    Vertice *aux, *aux2, *percorre_lista;
    int i;

    //Percorrer as listar e ir liberando
    for (i = 0; i < gr->n; i++)
    {   
        percorre_lista = aux->segue;
        if(percorre_lista != NULL)
            while(percorre_lista->prox != NULL) //Percorrer a lista de seguidores
            {
                aux2 = percorre_lista;
                percorre_lista = percorre_lista->prox;
                free(aux2);
            }

        aux2 = aux;
        aux = aux->prox;
        free(aux2);
    }

    free(gr->lista);
}

//Função que imprime o grafo conforme especificado
void imprime_grafo(Grafo* gr)
{
    //Variáveis auxiliares
    Vertice *percorre_lista;
    Vertice *aux = *(gr->lista);

    //Percorrer o vetor
    int i;
    for(i = 0 ; i < gr->n ; i++)
    {
        printf("%s", aux->nomePessoa);
        percorre_lista = aux->segue;
        if(percorre_lista != NULL)
        {
            while(percorre_lista != NULL) //Percorrer a lista de seguidores
            {
                //Imprimir os elementos da sub-lista
                printf(", %s", percorre_lista->nomePessoa);
                percorre_lista = percorre_lista->prox;
            }
        }
        aux = aux->prox;
        printf("\n");
    }
}

//Função que adiciona um vértice no gráfico, uma pessoa no vetor de de pessoas
void adiciona_vertice_ordenado(Grafo *gr, char nome[40])
{
    //Carrega em AUX o ponteiro para o início do vetor de vértices
    Vertice *aux = *(gr->lista);
    Vertice *ant = NULL;
    Vertice *novo = (Vertice *) malloc(sizeof(Vertice));
    
    //Adicionar informações ao novo nó
    novo->prox = NULL;
    novo->segue = NULL;
    strcpy(novo->nomePessoa, nome);

    //Verificar se é a primeira inserção
    if(aux == NULL)
    {
        *(gr->lista) = novo;
    }
    else
    {
        //Percorre o vetor enquanto não encontrar o local apropriado
        while( aux != NULL && strcmp(aux->nomePessoa, nome) < 0)
        {
            ant = aux;
            aux = aux->prox;
        }

        //Considerando que não há repetições, inserir ordenado
        if(ant != NULL)
        {
            ant->prox = novo;
            novo->prox = aux; 
        }
        else
        {
            //Inserir no início
            (*(gr->lista)) = novo;
            novo->prox = aux;
        }
    }
}

//Função que adiciona a pessoa seguida na sub-lista da pessoa que segue
void adiciona_relacao(Grafo *gr, char nomePessoaQueSegue[40], char nomePessoaQueESeguida[40])
{
    //Cria as variáveis necessárias
    Vertice *aux2, *ant;
    Vertice *aux = *(gr->lista);
    Vertice *novo = (Vertice *) malloc(sizeof(Vertice));

    strcpy(novo->nomePessoa, nomePessoaQueESeguida);
    novo->segue = NULL;
    novo->prox = NULL;

    //Percorrer o vetor de pessoas
    while(aux != NULL)
    {
        if(strcmp(aux->nomePessoa, nomePessoaQueSegue) == 0)
        {
            //Adicionar ordenado nesta sub-lista
            
            if(aux->segue == NULL) //Verificar se é a primeira inserção
            {
                aux->segue = novo;
                return;
            }
            else
            {
                //Percorrer a sub-lista para encontrar o local apropriado 
                ant = NULL;
                aux2 = aux->segue;
                
                //Percorre o vetor enquanto não encontrar o local apropriado
                while( aux2 != NULL && strcmp(aux2->nomePessoa, nomePessoaQueESeguida) < 0)
                {
                    ant = aux2;
                    aux2 = aux2->prox;
                }

                //Considerando que não há repetições, inserir ordenado
                if(ant != NULL)
                {
                    ant->prox = novo;
                    novo->prox = aux2; 
                }
                else
                {
                    //Inserir no início da sub-lista
                    aux->segue = novo;
                    novo->prox = aux2;
                }

                return;
            }
        }
        else
        {
            aux = aux->prox;
        }
    }    
}