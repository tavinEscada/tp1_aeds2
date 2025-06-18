#ifndef PAT_INDICE_H
#define PAT_INDICE_H

#include <string.h>
#include<stdlib.h>

typedef struct Celula
{
    int idDoc;
    int qtde;
    struct Celula *prox;

}celula;

typedef struct{

    celula *primeiro;
    celula *ultimo;

} Lista_Indice_Invertido;

typedef struct TipoItem
{
    char word[50] ;
    int n_docs;
    Lista_Indice_Invertido lista;

}TipoItem;


void Inicializa_listaIndice(Lista_Indice_Invertido* lista);
void Atualiza_Ocorrencia(Lista_Indice_Invertido* lista,int idDoc);
void Insere_Ocorrencia(Lista_Indice_Invertido* lista,int idDoc);
void Incrementa_Ocorrencia(celula* celula);
void Imprime_ListaIndice (Lista_Indice_Invertido* lista);
int Contabiliza_Docs(Lista_Indice_Invertido* lista);

#endif
