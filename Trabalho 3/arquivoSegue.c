#include"arquivoSegue.h"

//Função que lê o arquivo binário "Segue" e retorna um vetor com todos os dados
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
        printf("Falha na execução da funcionalidade.");
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

//Função que escreve o os registros no vetor de "Segue" em disco
void escreve_arqSegue(FILE *arq_segue, Segue *vetSegue, int num_segue)
{
    //Escrever o registro de cabeçalho
    int i;
    char status = '0';
    fwrite(&status, sizeof(char), 1, arq_segue); //Arquivo INCONSISTENTE
    fwrite(&num_segue, sizeof(int), 1, arq_segue);
    status = '$';
    for(i = 0; i < 27; i++)
        fwrite(&status, sizeof(char), 1, arq_segue);

    //Escreve todos os dados
    i = 0;
    while(i != num_segue)
    {
        //Escreve os valores do vetor de estruturas em disco
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

//Função faz uma busca binária no vetorSegue e retorna o índice do registro que contém "idPessoaQueSegue"
int busca_binaria_arqSegue(Segue *vetSegue, int num_segue, int idPessoaQueSegue)
{
    //Algoritmo da busca binária
    int inf = 0;
    int sup = num_segue-1;
    int meio;
    while(inf <= sup)
    {
        meio = (inf+sup)/2;

        if(vetSegue[meio].idPessoaQueSegue == idPessoaQueSegue)
            return meio;
        
        else if(vetSegue[meio].idPessoaQueSegue > idPessoaQueSegue)
            sup = meio-1;
        else
            inf = meio+1;
    }
    return -1;
}