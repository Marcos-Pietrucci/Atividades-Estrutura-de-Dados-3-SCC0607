/* Marcos Vinícius Firmino Pietrucci 10770072 */

#ifndef MAIN_H
#include"main.h"
#endif
#ifndef STDLIB_H
#include<stdlib.h>
#endif

/******** Funções referentes ao grafo *********/
//Função que cria um grafo e retorna um ponteiro para ele
Grafo* cria_grafo(int n);

//Função que libera todo o grafo adequadamente
void libera_grafo(Grafo *gr);

//Função que adiciona a pessoa seguida na sub-lista da pessoa que segue
void adiciona_relacao_entre_vertices(Grafo *gr, char nomePessoaQueSegue[40], char nomePessoaQueESeguida[40]);

//Função que adiciona um vértice no gráfico, uma pessoa no vetor de de pessoas
void adiciona_vertice_ordenado(Grafo *gr, char nome[40]);

//Função que imprime o grafo conforme especificado
void imprime_grafo(Grafo* gr);