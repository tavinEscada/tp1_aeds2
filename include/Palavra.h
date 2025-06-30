/**
 * @author Beatriz Queiroz - 5890
 * @author Heitor Porto - 5895
 * @author Pâmela Lúcia - 5898
 * @author Júlio César - 5903
 * @author Otávio Tavares - 5912
 */
#ifndef PALAVRA_H
#define PALAVRA_H

#include <string.h>
#include<stdlib.h>


typedef struct celula
{
    int idDoc;
    int qtde;
    struct celula * prox;

}Ccelula;

typedef struct TipoItemP
{
    char palavra[50] ;
    Ccelula * primeiro;
    int n_arquivos;
    int total_ocorrencias;

}TipoItemP;

void faz_palavra_vazia(TipoItemP * item, char * palavra);
void imprime_indice_invertido(TipoItemP * item);
void insere_palavra (TipoItemP * item, int idDoc);
int remove_palavra (TipoItemP * item, int idDoc);
int QuantidadeTermosPorDoc(TipoItemP item, int idDoc);


#endif
