#include<stdio.h>
#include<string.h>
#include<stdlib.h>

FILE *arq;

typedef struct{
    int id;
    char nome[50];
    int idade;
}user;

void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}

int main()
{ 
    int nl, i;
    char nome[20];
    user Nodo;
    Nodo.nome[0] = 'a'; //Para tirar o warning

    scanf("%s", nome);
    
    arq = fopen(nome, "wb");

    if(arq == NULL)
    {
        printf("\nErro na abertura do arquivo");
        return 0;
    }

    //Le a quantidade de linhas
    scanf("%d", &nl);
    
    for(i = 0; i < nl; i++)
    {
        scanf("%d %s %d", &Nodo.id, Nodo.nome, &Nodo.idade);    //Leitura das entradas

        strcat(Nodo.nome, "\0");    //Adicionar o \0 no final

        fwrite(&Nodo.id,sizeof(int), 1, arq);   //Escrever o id
        fwrite(Nodo.nome,sizeof(char),strlen(Nodo.nome), arq);  //Escrever o nome
        fwrite(&Nodo.idade, sizeof(int), 1, arq);   //Escrever a idade

    }
    fclose(arq);
    binarioNaTela(nome);
    return 0;
}