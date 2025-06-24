#ifndef PATRICIA_H
#define PATRICIA_H

#include <string.h>
#include<stdlib.h> 
#include <stdio.h>
#include <sys/time.h>
#include "palavra.h"

typedef enum {
  Interno, Externo
} TipoNo;

typedef struct NO_patricia* TipoArvore; 
typedef struct NO_patricia {
  TipoNo tipo_no;
  union {
    struct {
      char caractere;
      int indice;
      TipoArvore esq,dir;
    } NInterno;
    TipoItemP chave; 
  } NO;
} NO_patricia;

TipoArvore Cria_NO_ExternoPat(char* palavra,int idDoc);
TipoArvore Cria_NO_InternoPat(int i, TipoArvore *esq, TipoArvore *dir, char caractere);
TipoArvore InsereEntrePat(char* palavra, int idDoc, TipoArvore *NoAtual, int i, char caractere_interno);
TipoArvore InserePat(char* palavra,int idDoc, TipoArvore *NoRaiz);
TipoItemP PesquisaPat(char* palavra, TipoArvore NoRaiz);
short Eh_ExternoPat(TipoArvore NO);
void ImprimeOrdemPat(TipoArvore t);
int PesquisaTermosDistintos(TipoArvore t, int idDoc, int * res);

#endif