/* Marcos Vinícus Firmino Pietrucci 10770072 */

/* Header referente ao modo 6 */
#ifndef MAIN_H
#define MAIN_H
#include"header/main.h"
#endif

void modo6();

void le_entradas_modo6(char *nome_arq_csv, char *nome_arq_bin);

//Função que lê o arquivo CSV "Segue" e retorna um vetor com todos os dados
Segue* le_dados_arqSegue_CSV(FILE *arq_csv, int *num_Seg);
