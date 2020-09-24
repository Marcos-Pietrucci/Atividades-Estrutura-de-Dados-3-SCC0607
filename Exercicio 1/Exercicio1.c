#include<stdio.h>

FILE *arq;

typedef struct{
    int id;
    char nome[20];
    int idade;
}user;

void zeraNome(char *nome)
{
    int i;

    for(i = 0; i < 19; i++)
        nome[i] = 0;

    nome[19] = '\0';

}

int main()
{ 
    int indc = 0;
    char nm[20], lixo;
    user Nodo;

    scanf("%s", nm);
    
    arq = fopen(nm, "r");

    if(arq == NULL)
    {
        printf("\nErro na abertura do arquivo");
        return 0;
    }
    //A primeira linha contem lixo, contem apenas um indicativo
    fscanf(arq, "%s", nm); //Basicamente lê lixo

    //while(fread(&id,sizeof(int) ,1,arq ) == 1) //!Por que não deu certo????
    while(fscanf(arq,"%d",&Nodo.id) != -1)
    {
        //Devo zerar a string Nome para nao termos problemas de terminacao
        zeraNome(Nodo.nome); //Ja que leio caractere por caractere
        indc = 0;

        fread(&lixo, sizeof(char), 1, arq); //Le a virgula divisora

        //Le o nome até encontrar uma proxima virgula
        fscanf(arq, "%c", &lixo);
        if(lixo != ',') //O primeiro caractere nao foi uma virgula, portanto tem nome
        {
            //Lerei o nome char por char até esbarrar na virgula
            Nodo.nome[indc++] = lixo;

            while((lixo = getc(arq)) != ',')
                Nodo.nome[indc++] = lixo;
        }

        fscanf(arq, "%d", &Nodo.idade); 
        
        if(Nodo.idade >= 18)
        {
            
            if(indc != 0) //Significa que não foi acrescentado nenhum char no nome
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