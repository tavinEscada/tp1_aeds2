#ifndef HASH_H
#define HASH_H

#include <string.h>
#include<stdlib.h>
#include<stdio.h>
#include <sys/time.h>
#include "Palavras.h"

#define M 7 //tamanho da tabela mudar de acordo com o Tp
#define N 50 // tamanho para a maior palavrea em ingles e portugues
#define TAMALFABETO 256 // num possivel de caracters ASCII

/* typedef unsigned int  TipoPesos[n]; */
typedef char Tipopalavra[N]; //palavra
typedef unsigned TipoPesos[N][TAMALFABETO]; //nao sei pq esta assim
typedef struct TipoItem {
    Tipopalavra palavra;
	Ccelula *indice;
]} TipoItem; // pesquisar
typedef unsigned int TipoIndice;
typedef struct TipoCelula* TipoApontador;
typedef struct TipoCelula {
    TipoItem Item; //palavra e outros componentes
    TipoApontador Prox;
} TipoCelula; //lista encadeada
typedef struct TipoLista {
    TipoCelula *Primeiro, *Ultimo;
} TipoLista;
typedef TipoLista TipoDicionario[M];//nossa tabela(vetor de tipolista)
TipoDicionario Tabela;
TipoItem Elemento;
TipoPesos p;
TipoApontador i;


void Inicializa(TipoDicionario T);

void FLVazia(TipoLista *Lista);

void GeraPesos(TipoPesos p);

TipoIndice h(Tipopalavra palavra, TipoPesos p);
#endif