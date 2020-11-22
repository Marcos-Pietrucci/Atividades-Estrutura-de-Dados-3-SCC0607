/* Marcos Vinícus Firmino Pietrucci 10770072 */

#include"header/modo2.h"

//Função que inicia a leitura das entradas e o processamento do modo
void modo2()
{
    //Continuar com a leitura
    char nome_arq_bin[15];

    //Lê a entrada
    le_entradas_modo2(nome_arq_bin);

    //Abre o arquivo
    FILE *pessoas_bin = le_arquivo(nome_arq_bin, "rb", 2);
    if(pessoas_bin == NULL)
        return;

    //Teste de consistencia do cabeçalho
    if(!teste_consistencia_cabecalho(pessoas_bin))
        return;
    
    //Lê o arquivo e exibe na tela
    exibe_dados_bin(pessoas_bin);

    fclose(pessoas_bin);
}

//Função que lê as entradas do modo 2
void le_entradas_modo2(char *nome_arq_bin)
{
    //Lê a entrada
    char lixo; 
    scanf("%c",&lixo);
    fflush(stdin);
    scanf("%s", nome_arq_bin);
    fflush(stdin);
}

//Função que lê os dados do arquivo bin e exibe na tela os registros não removidos
void exibe_dados_bin(FILE *pessoas_bin)
{
    /* Variáveis axuliares */
    Pessoa pAux;
    int cont = 0, flag_idade = 0;
    char str_lixo[65];

    //Lê o registro de cabeçalho (que contém dados irrelevantes)
    fread(str_lixo, sizeof(char), 64, pessoas_bin);
   
    //Lê os dados do arquivo iterativamente
    while(fread(&pAux.removido, sizeof(char), 1, pessoas_bin) != 0)
    { 
        //Testa se o registro foi removido
        if(pAux.removido == '0')
        {
            //Se foi removido, lê o restante como lixo
            fread(str_lixo, sizeof(char), 63, pessoas_bin);
            continue;
        }
        else
            cont++;
        
        //Lê o ID no arquivo
        fread(&pAux.idPessoa, sizeof(int), 1, pessoas_bin);

        //Lê o nome no arquivo
        fread(&pAux.nomePessoa, sizeof(char), 40, pessoas_bin);
        if(pAux.nomePessoa[0] == '\0')
        {
            pAux.nomePessoa[0] = '-';
            pAux.nomePessoa[1] = '\0';
        }

        //Lê a idade no arquivo
        fread(&pAux.idadePessoa, sizeof(int), 1, pessoas_bin);
        if(pAux.idadePessoa == -1)
            flag_idade = 1;

        //Lê o twitter no arquivo
        fread(&pAux.twitterPessoa, sizeof(char), 15, pessoas_bin);

        //Exibir o registro lido
        printf("Dados da pessoa de código %d", pAux.idPessoa);
        printf("\nNome: %s", pAux.nomePessoa);

        //Caso a idade não tenha sido informada
        if(!flag_idade)
            printf("\nIdade: %d anos\nTwitter: %s\n\n", pAux.idadePessoa, pAux.twitterPessoa);
        else
        {
            flag_idade = 0;
            printf("\nIdade: -\nTwitter: %s\n\n", pAux.twitterPessoa);
        }
        
    }

    //Caso não tenha lido nenhum registro
    if(!cont)
        printf("Registro inexistente.");
}
