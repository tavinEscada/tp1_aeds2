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

typedef struct TipoItem
{
    char palavra[255] ;
    Ccelula * primeiro;

}TipoItem;

void faz_palavra_vazia( TipoItem * item, char * palavra);
int imprime_indice_invertido( TipoItem * item);
int insere_palavra (TipoItem * item, int idDoc);
int remove_palavra (TipoItem * item, int idDoc);


#endif
