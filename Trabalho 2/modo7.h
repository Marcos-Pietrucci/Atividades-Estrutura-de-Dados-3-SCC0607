/* Marcos Vinícus Firmino Pietrucci 10770072 */

/* Header referente ao modo 6 */
#ifndef MAIN_H
#define MAIN_H
#include"main.h"
#endif

//Função que inicia a leitura das entradas e o processamento do modo 6
void modo7();

//Função que lê as entradas do modo 7
void le_entradas_modo7(char *arq_segue_nome, char *nome_arq_ordenado);

//Função que ordena o vetor de "Segue" usando insertionSort
void ordena_vetSegue(Segue *vetSegue, int num_segue);

//Função que comprara dois registros de "Segue" segundo os critérios definidos
int compara_vetSegue(Segue a, Segue b);

