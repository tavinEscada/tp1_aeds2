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
    char word[50];
    int n_arquivos;
    Lista_Indice_Invertido lista;

}TipoItem;


void Inicializa_listaIndice(TipoItem* no_palavra);
void Atualiza_Ocorrencia(TipoItem* no_palavra,int idDoc);
void Insere_Ocorrencia(TipoItem* no_palavra,int idDoc);
void Incrementa_Ocorrencia(celula* celula);
void Imprime_ListaIndice (Lista_Indice_Invertido lista);
int Contabiliza_Docs(Lista_Indice_Invertido* lista);

#endif
