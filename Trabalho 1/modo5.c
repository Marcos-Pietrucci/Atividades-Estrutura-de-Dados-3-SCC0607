#include"modo5.h"
#ifndef FORNECIDO_H_
#include"fornecido.h"
#define FORNECIDO_H_
#endif

//Função que inicia a leitura das entradas e o processamento do modo
void modo5()
{
    //Continuar com a leitura
    char nome_arq_bin[15], nome_index_bin[15];
    int n;
    le_entradas_modo5(nome_arq_bin, nome_index_bin, &n);

    //Abre e testa a consistência dos arquivos
    FILE *pessoas_bin = le_arquivo(nome_arq_bin, "rb+", 5); //Aberto no modo rb+ para permitir leitura e escrita no meio do arquivo
    if(pessoas_bin == NULL || !teste_consistencia_cabecalho(pessoas_bin))
        return;
    FILE *index_bin = le_arquivo(nome_index_bin, "rb+", 5); //Aberto no modo rb+ para permitir leitura e escrita no arquivo
    if(index_bin == NULL || !teste_consistencia_cabecalho(index_bin))
        return;
    
    //Ler as entradas iterativamente e inserir o arquivo adequado  
    int num_pessoas = 0;
    IndexPessoa* index = le_index(index_bin, &num_pessoas);
    
    //Faz todo o processamento do modo. Lê as entradas, busca o registro e altera em disco
    atualiza_pessoas_bin(pessoas_bin, index, n, num_pessoas);
    
    //O Index pode ter sido alterado, por isso vamos reescrevê-lo
    ordena_index(index, num_pessoas);
    escreve_index(index_bin, index, num_pessoas);

    free(index);
    fclose(pessoas_bin);
    fclose(index_bin);

    binarioNaTela1(nome_arq_bin, nome_index_bin);
}

//Função que lê os nomes dos arquivos e a quantidade de alterações
void le_entradas_modo5(char *nome_arq_bin, char *nome_index_bin, int *n)
{
    //Lê todas as entradas
    char lixo; 
    scanf("%c",&lixo);
    fflush(stdin);
    scanf("%s", nome_arq_bin);
    fflush(stdin);
    scanf("%c", &lixo);
    fflush(stdin);
    scanf("%s", nome_index_bin);
    fflush(stdin);
    scanf("%c", &lixo);
    fflush(stdin);
    scanf("%d", n);
}

//Função que processa o modo: lê os pedidos de alteração, faz a busca sequencial no arquivo binário, altera o registro em memória e o reescreve no disco 
void atualiza_pessoas_bin(FILE *pessoas_bin, IndexPessoa* index, int n, int num_pessoas)
{
    //Escrita do registro de cabeçalho do pessoas_bin
    char status = '0';
    fwrite(&status, sizeof(char), 1, pessoas_bin); //Arquivo inconsistente

    //Continuar com a leitura, ao mesmo passo da atualização
    /* Variáveis auxiliares  na leitura */
    int i, j, m;
    char nomeCampo[30], lixo = 'a';
    Pessoa pBusca, pAltera;
    invalida_pessoa(&pBusca);   //pBusca armazena os dados de busca da pessoa que será buscada
    invalida_pessoa(&pAltera);  //pAltera armazena os dados dessa pessoa a serem alterados

    /* Variáveis axuliares na busca */
    Pessoa pAux;
    int flag_alteracao = 0;
    char str_lixo[65];

    for(i = 0; i < n; i++)
    {
        /****** Leitura dos dados *******/

        //Lê o \n anterior
        if(lixo != '\n')
        scanf("%c", &lixo);

        //Lê o nome do campo a partir do qual será feita a busca
        scanf("%s", nomeCampo);

        //Lê espaço
        scanf("%c", &lixo);

        if(strcmp(nomeCampo, "idPessoa") == 0)
        {
            //Realizar uma busca do registro usando idPessoa
            scanf("%d", &pBusca.idPessoa);
        }    
        else if(strcmp(nomeCampo, "nomePessoa") == 0)
        {
            //Realizar uma busca do registro usando nomePessoa
            scan_quote_string(pBusca.nomePessoa, 40);
        }
        else if(strcmp(nomeCampo, "idadePessoa") == 0)
        {
            //Realizar uma busca do registro usando idadePessoa
            scanf("%d", &pBusca.idadePessoa);
        }
        else if(strcmp(nomeCampo, "twitterPessoa") == 0)
        {
            //Realizar uma busca do registro usando twitterPessoa
            scan_quote_string(pBusca.twitterPessoa, 15);
        }

        //Lê espaço
        scanf("%c", &lixo);

        //Lê a quantidade de campos que se deseja alterar
        scanf("%d", &m);

        //Lê espaço
        scanf("%c", &lixo);

        //Inicia a leitura dos campos a serem alterados
        for(j = 0; j < m; j++)
        {
            //Lê o nome do campo que será alterado
            scanf("%s", nomeCampo);

            //Lê espaço
            scanf("%c", &lixo);

            if(strcmp(nomeCampo, "idPessoa") == 0)
            {
                //Alterar o idPessoa
                scanf("%d", &pAltera.idPessoa);
            }
            else if(strcmp(nomeCampo, "nomePessoa") == 0)
            {
                //Alterar o nomePessoa
                scan_quote_string(pAltera.nomePessoa, 40);
                pAltera.nomePessoa[39] = '\0';
            }
            else if(strcmp(nomeCampo, "idadePessoa") == 0)
            {
                //Alterar a idadePessoa
                scanf("%d", &pAltera.idadePessoa);
            }
            else if(strcmp(nomeCampo, "twitterPessoa") == 0)
            {
                //Alterar o twitterPessoa
                scan_quote_string(pAltera.twitterPessoa, 15);
                pAltera.twitterPessoa[14] = '\0';
            }

            scanf("%c", &lixo);
        }//Leitura finalizada

        /************* Busca pelo registro lido ************/
         /*
        Pessoa pBusca: contém os dados referentes à busca
                - Apenas um campo será usado para busca
         
        Pessoa pAltera: contém os dados a serem alterados
                -  De um a todos os campos podem ser alterados 
        */
        //Verifica se a busca será pelo ID
        if(pBusca.idPessoa != -2)
        {
            //A busca será indexada (pelo ID)
            atualiza_pessoas_bin_indexada(pessoas_bin, index, num_pessoas,pBusca.idPessoa, pAltera);
        }
        else
        {
            //A busca não será pelo ID, mas sim por outros campos

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
                
                //Lê o ID no arquivo
                fread(&pAux.idPessoa, sizeof(int), 1, pessoas_bin);

                //Lê o nome no arquivo
                fread(&pAux.nomePessoa, sizeof(char), 40, pessoas_bin);

                //Lê a idade no arquivo
                fread(&pAux.idadePessoa, sizeof(int), 1, pessoas_bin);

                //Lê o twitter no arquivo
                fread(&pAux.twitterPessoa, sizeof(char), 15, pessoas_bin);

                //Verificar se o registro lido é o registro procurado
                //pBusca possui dados inválidos em todos os campos, menos o que está sendo pesquisado. Por isso este 'if' é seguro
                if(pAux.idadePessoa == pBusca.idadePessoa || strcmp(pAux.nomePessoa, pBusca.nomePessoa) == 0 ||
                strcmp(pAux.twitterPessoa, pBusca.twitterPessoa) == 0)
                { 
                    flag_alteracao = 1;

                    //Modificar o registro lido
                    if(pAltera.idPessoa != -2)
                    {
                        //Como vamos alterar o ID, devemos atualizar o Index
                        atualiza_index(index, num_pessoas, pAux.idPessoa, pAltera.idPessoa);
                        pAux.idPessoa = pAltera.idPessoa;
                    }
                    if(strcmp(pAltera.nomePessoa, "$$INVALIDO$$\0") != 0)
                        strcpy(pAux.nomePessoa, pAltera.nomePessoa); //Altera o nome da pessoa

                    if(pAltera.idadePessoa != -2)
                        pAux.idadePessoa = pAltera.idadePessoa; //Altera a idade da pessoa
                    
                    if(strcmp(pAltera.twitterPessoa, "$$INVALIDO$$\0") != 0)
                        strcpy(pAux.twitterPessoa, pAltera.twitterPessoa); //Altera o twitter da pessoa
                }

                //Testar se houve alteração do registro atual
                if(flag_alteracao)
                {
                    flag_alteracao = 0;

                    //Pega a posição atual no arquivo
                    int position = ftell(pessoas_bin);

                    //Voltar 64 bytes para trás e escrever o pAux na memória
                    fseek(pessoas_bin, position - 64, SEEK_SET);

                    //Escreve registro de pAux no disco
                    prepara_structPessoa(&pAux);
                    fwrite(&pAux.removido, sizeof(char), 1, pessoas_bin);
                    fwrite(&pAux.idPessoa, sizeof(int), 1, pessoas_bin);
                    fwrite(&pAux.nomePessoa, sizeof(char), 40, pessoas_bin);
                    fwrite(&pAux.idadePessoa, sizeof(int), 1, pessoas_bin);
                    fwrite(&pAux.twitterPessoa, sizeof(char), 15, pessoas_bin);

                    //Volta o ponteiro para a sua anterior, assim continuamos a busca por mais registros
                    fseek(pessoas_bin, position, SEEK_SET);
                }
            }
        }

        //Zerar as váriáveis
        invalida_pessoa(&pBusca);
        invalida_pessoa(&pAltera);
        invalida_pessoa(&pAux);
        fseek(pessoas_bin, 0, SEEK_SET); //Uma nova busca deve começar do começo
    }

    //Terminada toda leitura e escrita
    //Atualiza o registro de cabeçalho do pessoas_bin
    status = '1';
    fseek(pessoas_bin, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, pessoas_bin);  //Arquivo consistente
}

//Função que realiza a busca e alteração dos registros por meio de uma busca indexada, quando o idPessoa é fornecido
void atualiza_pessoas_bin_indexada(FILE *pessoas_bin, IndexPessoa *index, int num_pessoas, int idPessoa, Pessoa pAltera)
{
    /**** Iniciar a busca indexada ****/
    //Realiza uma busca binária no índice primário
    int RRN = busca_binaria_index(index, num_pessoas, idPessoa, 5);
    if(RRN == -1)
        return;
    
    //Buscar e ler o registro a ser alterado
    Pessoa pAux = busca_RRN_pessoa(pessoas_bin, RRN, 5);

    //Verifica se esta pessoa está removida
    if(pAux.idPessoa == -1)
        return;

    //Modificar o registro lido
    if(pAltera.idPessoa != -2)
    {
        //Como vamos alterar o ID, devemos atualizar o Index
        atualiza_index(index, num_pessoas, pAux.idPessoa, pAltera.idPessoa);
        pAux.idPessoa = pAltera.idPessoa;
    }
    if(strcmp(pAltera.nomePessoa, "$$INVALIDO$$\0") != 0)
        strcpy(pAux.nomePessoa, pAltera.nomePessoa);

    if(pAltera.idadePessoa != -2)
        pAux.idadePessoa = pAltera.idadePessoa;
                
    if(strcmp(pAltera.twitterPessoa, "$$INVALIDO$$\0") != 0)
        strcpy(pAux.twitterPessoa, pAltera.twitterPessoa);    

    /**** Esrever o registro, já com as alterações, em memória *****/
    //Move o ponteiro para o início
    fseek(pessoas_bin, 0, SEEK_SET);

    //Variáveis auxiliares
    char str_lixo[65];

    //Ler o registro de cabeçalho, que é lixo
    fread(str_lixo, sizeof(char), 64, pessoas_bin);

    //Posicionar o ponteiro na posição correta
    fseek(pessoas_bin, RRN*64, SEEK_CUR);

    //Escreve registro de pAux no disco
    prepara_structPessoa(&pAux);
    fwrite(&pAux.removido, sizeof(char), 1, pessoas_bin);
    fwrite(&pAux.idPessoa, sizeof(int), 1, pessoas_bin);
    fwrite(&pAux.nomePessoa, sizeof(char), 40, pessoas_bin);
    fwrite(&pAux.idadePessoa, sizeof(int), 1, pessoas_bin);
    fwrite(&pAux.twitterPessoa, sizeof(char), 15, pessoas_bin);

}

//Função que coloca dados inválidos na Pessoa apontada por p
void invalida_pessoa(Pessoa *p)
{
    //Coloca dados inválidos em todos os campos da Pessoa
    //Com isso, garantimos que APENAS os campos que queremos procurar trarão resultados válidos na busca
    p->idPessoa = -2;    //Nenhuma pessoa tem este ID
    p->idadePessoa = -2; //Nenhuma pessoa tem esta idade
    
    //Nenhuma pessoa tem este nome
    strcpy(p->nomePessoa, "$$INVALIDO$$\0");
    
    //Nenhuma pessoa tem este twitter
    strcpy(p->twitterPessoa, "$$INVALIDO$$\0");

    //Valor assumido do removido, para não termos problemas
    p->removido = 1;
}

//Função que atualiza o index em memória, busca pelo registro com 'idAntigo' e substitiu pelo 'idNovo' 
void atualiza_index(IndexPessoa *index, int num_pessoas, int idAntigo, int idNovo)
{
    int i = 0;

    //Procurar no vetor de Index
    while(i < num_pessoas)
    {
        //Ao encontrar o registro cujo ID será alterado
        if((index[i]).idPessoa == idAntigo)
        {
            //Alterar o ID no index também
            (index[i]).idPessoa = idNovo;
        }
        i++;
    }
}
