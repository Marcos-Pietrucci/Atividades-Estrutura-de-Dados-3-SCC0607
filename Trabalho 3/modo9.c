/* Marcos Vinícius Firmino Pietrucci 10770072*/
#include"modo9.h"
#include"grafo.h"
#include"arquivoIndex.h"
#include"arquivoSegue.h"
#include"arquivoPessoa.h"

//Função que inicia o modo 9
void modo9()
{
    //Continuar com a leitura
    char nome_arq_pessoa[30], nome_arq_index[30], nome_arq_segue[30];
    le_entradas_modo9(nome_arq_pessoa, nome_arq_index, nome_arq_segue);

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

    //Carregar na memória vetor de index
    int num_pessoas;
    IndexPessoa *index = le_index(arq_index, &num_pessoas);

    //Carregar na memória vetor de Segue
    int num_segue;
    Segue *vetSegue = le_dados_arqSegue_BIN(arq_segue, &num_segue);

    //Buscar pelas pessoas no arquivo pessoa
    Grafo *gr = cria_grafo(num_pessoas);
    leitura_arq_pessoa_gera_grafo(gr, arq_pessoa, index, vetSegue, num_pessoas, num_segue);

    //Apresentar resultado
    imprime_grafo(gr);

    fclose(arq_pessoa);
    fclose(arq_index);
    fclose(arq_segue);
    free(index);
    free(vetSegue);
}

//Função que lê as entradas do modo 9
void le_entradas_modo9(char *nome_arq_pessoa, char *nome_arq_index, char *nome_arq_segue)
{
    char lixo;
    scanf("%c", &lixo);
    scanf("%s", nome_arq_pessoa);
    scanf("%c", &lixo);
    scanf("%s", nome_arq_index);
    scanf("%c", &lixo);
    scanf("%s", nome_arq_segue);
}



Grafo* leitura_arq_pessoa_gera_grafo(Grafo *gr, FILE *arq_pessoa, IndexPessoa *index, Segue *vetSegue, int num_pessoas, int num_segue)
{

    /* Variáveis axuliares */
    Pessoa pAux, pSegue;
    int indc_seguido = 0, RRN_seguido = 0;
    char str_lixo[65];

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
    return gr;
}
