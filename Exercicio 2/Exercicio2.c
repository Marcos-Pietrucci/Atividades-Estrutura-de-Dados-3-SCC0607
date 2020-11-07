#include<stdio.h>
#include<string.h>

FILE *arq;

typedef struct{
    int id;
    char nome[50];
    int idade;
}user;

int main()
{ 
    char nm[20];
    user Nodo;

    scanf("%s", nm);
    
    arq = fopen(nm, "rb");

    if(arq == NULL)
    {
        printf("\nErro na abertura do arquivo");
        return 0;
    }

    //Le o ID
    while(fread(&Nodo.id, sizeof(int), 1, arq) != 0)
    {
        fread(Nodo.nome, sizeof(char), 50, arq); //Le o nome

        fread(&Nodo.idade, sizeof(int), 1, arq); //Le a idade
        
        if(Nodo.idade >= 18)
        {
            if(strlen(Nodo.nome) > 0) //Significa que o nome nao é nulo
            {
                printf("O usuario %s eh de maior.\n", Nodo.nome);    
            }
            else
            {
                printf("O usuario de identificacao %d eh de maior.\n", Nodo.id);
            }
            
        }
    }

    fclose(arq);
    return 0;
}