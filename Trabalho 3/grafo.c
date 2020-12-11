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
    Vertice *inicio = *(gr->lista);
    Vertice *aux, *percorre_lista;
    int i;

    //Percorrer as listar e ir liberando
    for (i = 0; i < gr->n; i++)
    {   
        percorre_lista = inicio->segue;
        if(percorre_lista != NULL)
            while(percorre_lista->prox != NULL) //Percorrer a lista de seguidores
            {
                aux = percorre_lista;
                percorre_lista = percorre_lista->prox;
                free(aux);
            }

        aux = inicio;
        inicio = inicio->prox;
        free(aux);
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
    Vertice *inicio = *(gr->lista);
    Vertice *novo = (Vertice *) malloc(sizeof(Vertice));

    strcpy(novo->nomePessoa, nomePessoaQueESeguida);
    novo->segue = NULL;
    novo->prox = NULL;

    //Percorrer o vetor de pessoas
    while(inicio != NULL)
    {
        if(strcmp(inicio->nomePessoa, nomePessoaQueSegue) == 0)
        {
            //Adicionar ordenado nesta sub-lista
            
            if(inicio->segue == NULL) //Verificar se é a primeira inserção
            {
                inicio->segue = novo;
                return;
            }
            else
            {
                //Percorrer a sub-lista para encontrar o local apropriado 
                ant = NULL;
                aux2 = inicio->segue;
                
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
                    inicio->segue = novo;
                    novo->prox = aux2;
                }

                return;
            }
        }
        else
        {
            inicio = inicio->prox;
        }
    }    
}

//Função que lê um arquivo de pessoas e gera o grafo
void leitura_arq_pessoa_gera_grafo(Grafo *gr, FILE *arq_pessoa, IndexPessoa *index, Segue *vetSegue, int num_segue)
{

    /* Variáveis axuliares */
    Pessoa pAux, pSegue;
    int indc_seguido = 0, RRN_seguido = 0;
    char str_lixo[65];
    int num_pessoas = gr->n;

    //Lê o registro de cabeçalho (que contém dados irrelevantes)
    fread(str_lixo, sizeof(char), 64, arq_pessoa);
   
    //Lê os dados do arquivo iterativamente
    while(fread(&pAux.removido, sizeof(char), 1, arq_pessoa) != 0)
    { 
        //Testa se o registro foi removido
        if(pAux.removido == '0')
        {
            //Se foi removido, lê o restante como lixo
            fread(str_lixo, sizeof(char), 63, arq_pessoa);
            continue;
        }
        
        //Lê o ID no arquivo
        fread(&pAux.idPessoa, sizeof(int), 1, arq_pessoa);

        //Lê o nome no arquivo
        fread(&pAux.nomePessoa, sizeof(char), 40, arq_pessoa);
        if(pAux.nomePessoa[0] == '$')
        {
            fread(str_lixo, sizeof(char), 19, arq_pessoa);
            continue;
        }

        //Lê o restante do arquivo, o qual não nos interessa
        fread(str_lixo, sizeof(char), 19, arq_pessoa);

        //De posse das informações da pessoa, adicioná-la no grafo
        adiciona_vertice_ordenado(gr, pAux.nomePessoa);

        pSegue = pAux;

        //De posse do índice, percorrer o vetor de segue
        indc_seguido = 0;
        while(indc_seguido < num_segue)
        {
            if(vetSegue[indc_seguido].idPessoaQueSegue == pSegue.idPessoa)
            {
                //Busca pelo RRN da pessoa SEGUIDA
                RRN_seguido = busca_binaria_index(index, num_pessoas, vetSegue[indc_seguido].idPessoaQueESeguida);

                //Recebe as informações da pessoa SEGUIDA
                pAux = busca_RRN_pessoa(arq_pessoa, RRN_seguido);

                //Adiciona no grafo a relação encontrada
                adiciona_relacao(gr, pSegue.nomePessoa, pAux.nomePessoa);
            }

            indc_seguido++;
        }
        
    }
}

Grafo* transpoe_grafo(Grafo *gr)
{
    //Variáveis auxiliares
    Vertice *aux;
    Vertice *inicio = *(gr->lista);

    //Cria o grafo transposto
    Grafo *gr_t = (Grafo *) cria_grafo(gr->n); 

    //Preenche o vetor de pessoas
    while(inicio != NULL)
    {
        adiciona_vertice_ordenado(gr_t, inicio->nomePessoa);
        inicio = inicio->prox;
    }

    inicio = *(gr->lista);

    //Preenchido o vetor da lista de adjacencias, iniciar a transposição
    while(inicio != NULL)
    {
        aux = inicio->segue;

        //Entra na sub-lista do vertice
        while(aux != NULL)
        {
            //Adiciona a relação de forma "invertida"
            adiciona_relacao(gr_t, aux->nomePessoa, inicio->nomePessoa);
            aux = aux->prox;
        }

        inicio = inicio->prox;
    }

    return gr_t;
}
