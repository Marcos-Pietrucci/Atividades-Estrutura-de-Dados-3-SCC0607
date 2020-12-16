/* Marcos Vinícius Firmino Pietrucci 10770072*/

#include"grafo.h"
#include"queue.h"
#include"stack.h"

/************************ Funções do grafo ***************************/
//Função que cria um grafo e retorna um ponteiro para ele
Grafo* cria_grafo(int n)
{ 
    Grafo *gr;

    //Alocar gr
    gr = (Grafo *) malloc(sizeof(Grafo));
    
    //Cria o início da lista
    gr->lista = (Vertice**) calloc(1, sizeof(Vertice*));
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
            while(percorre_lista != NULL) //Percorrer a lista de seguidores
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
    free(gr);
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
    novo->visitado = 0;
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
Grafo* leitura_arq_pessoa_gera_grafo(FILE *arq_pessoa, FILE *arq_index, FILE *arq_segue)
{
    /* Variáveis axuliares */
    Pessoa pAux, pSegue;
    int indc_seguido = 0, RRN_seguido = 0;
    char str_lixo[65];
    int num_pessoas, num_segue;

    //Carregar na memória vetor de index
    IndexPessoa *index = le_index(arq_index, &num_pessoas);

    //Carregar na memória vetor de Segue
    Segue *vetSegue = le_dados_arqSegue_BIN(arq_segue, &num_segue);

    //Buscar pelas pessoas no arquivo pessoa
    Grafo *gr = cria_grafo(num_pessoas);

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

    //Liberar as listas alocadas
    free(index);
    free(vetSegue);

    return gr;
}

//Função que transpoe um grafo
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

//Função que retorna o índice de um vértice dado seu nome
int get_indc_vertice(Grafo *gr_t, char *nomeAux)
{   
    int i;
    Vertice *aux = *(gr_t->lista);
    
    for(i = 0 ; i < gr_t->n ; i++)
    {
        if(strcmp(nomeAux, aux->nomePessoa) == 0)
        {
            //Encontrou o indice
            return i;
        }

        aux = aux->prox;
    }

    return -1;
}

//Função que retorna um vértice dado seu índice
Vertice* get_vertice_de_indice(Grafo *gr_t, int indc)
{
    Vertice* aux = *(gr_t->lista);

    int i;
    for(i = 0; i < indc; i++)
    {
        aux = aux->prox;
    }

    return aux;
}

//Função que executa uma busca em largura
int* buscaLargura_Grafo(Grafo *gr_t, char *nomeCelebridade)
{
    //Cria o vetor de antecessores
    int *vetAnt = calloc(gr_t->n, sizeof(int));
    int i;

    //Zerar o vetor de antecessores
    for(i  = 0; i < gr_t->n; i++)
        vetAnt[i] = -1;

    //Criar fila
    QUEUE *fila = Q_New(sizeof(int));

    //Cria variaveis auxiliares
    Vertice *aux = *(gr_t->lista);
    Vertice *aux_2;
    Vertice *aux_original;

    int indc_inicio = 0, indc_aux = 0;

    for(i = 0 ; i < gr_t->n ; i++)
    {
        //Marcar todos os nós como não_visitados
        aux->visitado = 0;

        if(strcmp(aux->nomePessoa, nomeCelebridade) == 0)
        {
            //Encontrei o vertice inicial
            indc_inicio = i;
            Q_Push( &indc_inicio, fila);
        }

        aux = aux->prox;
    }
    
    vetAnt[indc_inicio] = -1;

    //Iniciar a busca em largura
    while(Q_Size(fila) != 0)
    {
        Q_Shift(&indc_aux, fila);

        //Coletar o vertice atual da fila
        aux = get_vertice_de_indice(gr_t, indc_aux);
        aux_original = aux;

        for(aux = aux->segue; aux != NULL ; aux = aux->prox)
        {   
            //Verificar as pessoas adjacentes
            indc_aux = get_indc_vertice(gr_t, aux->nomePessoa);
            aux_2 = get_vertice_de_indice(gr_t, indc_aux);

            if(aux_2->visitado == 0)
            {
                Q_Push(&indc_aux, fila);
                vetAnt[indc_aux] = get_indc_vertice(gr_t, aux_original->nomePessoa);
                aux_2->visitado = 1;
            }
            
        }
    }

    Q_Destroy(fila);
    vetAnt[indc_inicio] = -1;
    return vetAnt;
}

Vertice* get_seguidor_nao_visitado(Grafo *gr, Vertice *ini)
{
    int indc;
    Vertice *aux = ini;
    Vertice *aux2;

    do
    {
        indc = get_indc_vertice(gr, aux->nomePessoa);
        aux2 = get_vertice_de_indice(gr, indc);
        if (aux2->visitado == 0)
        {
            aux2->visitado = 1;
            return aux;
        }
        else
            aux = aux->prox;
    }while(aux != NULL);

    return NULL;
}

int busca_em_profundidade(Grafo *gr, char *nomeProcura)
{
    /*Variáveis auxiliares*/
    Vertice *aux, *aux2;
    STACK *pilha = S_New(sizeof(int));      //Pilha de registros
    int indc, flag_inicio = 1;
    int contador = 0;
    
    //Adicionar a pessoa inicial na pilha
    indc = get_indc_vertice(gr, nomeProcura);
    S_Push(&indc, pilha);

    do 
    {
        S_Pop(&indc, pilha);

        aux = get_vertice_de_indice(gr, indc); 

        if(strcmp(nomeProcura, aux->nomePessoa) == 0 && !flag_inicio)
        {
            S_Destroy(pilha);
            return contador;
        }
        else
        {
            aux2 = get_seguidor_nao_visitado(gr, aux->segue);

            if(aux2 != NULL)
            {
                contador++;
                indc = get_indc_vertice(gr, aux2->nomePessoa);
                S_Push(&indc, pilha);
            }
            else
            {
                contador--;
            }
            
        }
        
        flag_inicio = 0;
    }while(S_Size(pilha) != 0);

    S_Destroy(pilha);
    return -1;
}
