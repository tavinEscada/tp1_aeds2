#ifndef HASH_H
#define HASH_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "Palavra.h"

#define M 223//tamanho da tabela mudar de acordo com o Tp
#define N 50 // tamanho para a maior palavrea em ingles e portugues
#define TAMALFABETO 256 // num possivel de caracters ASCII

/* typedef unsigned int  TipoPesos[n]; */
typedef char Tipopalavra[N]; //palavra
typedef unsigned TipoPesos[N][TAMALFABETO]; //nao sei pq esta assim
//tipoitem esta na Palavra.h
typedef unsigned int TipoIndice;
typedef struct TipoCelula* TipoApontador;
typedef struct TipoCelula {
    TipoItemP Item; //palavra e outros componentes
    TipoApontador Prox;
} TipoCelula; //lista encadeada
typedef struct TipoLista {
    TipoCelula *Primeiro, *Ultimo;
} TipoLista;
typedef TipoLista TipoDicionario[M];//nossa tabela(vetor de tipolista)
//existe mas foi definida em outro arquivo hash.c
extern TipoDicionario Tabela;
extern TipoItemP Elemento;
extern TipoPesos p;
extern TipoApontador i;


void Inicializa(TipoDicionario T);

void FLVazia(TipoLista *Lista);

void GeraPesos(TipoPesos p);

TipoIndice h(Tipopalavra palavra, TipoPesos p);

int comparar_nos_por_palavra(const void *a, const void *b);

void Imprimir(TipoDicionario tabela);

short Vazia(TipoLista Lista);

void Insere(Tipopalavra word, int idDoc, TipoDicionario T, TipoPesos p,int *comp_insercao_hash);

void Ins(TipoItemP *x, TipoLista *Lista);

TipoItemP* Busca(Tipopalavra word, TipoLista *lista, int *comp_pequisa_hash);

TipoItemP pesquisa_na_hash(Tipopalavra palavra, TipoDicionario tabela, TipoPesos p, int *comp_pequisa_hash);

int termos_distintos_hash(TipoDicionario tabela, int idDoc, int * res);
#endif