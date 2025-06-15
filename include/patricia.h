#ifndef PATRICIA_H
#define PATRICIA_H

#include <string.h>
#include<stdlib.h> 
#include <stdio.h>
#include <sys/time.h>

typedef unsigned char* TipoChave; 

typedef struct{
    int qtde;
    int iddoc;
}par;

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
    } NInterno ;
    TipoChave chave; 
    par indinv[20]; //colocar como lista encdeada
  } NO;
} NO_patricia;

TipoArvore Cria_NO_Externo(TipoChave palavra);
TipoArvore Cria_NO_Interno(int i, TipoArvore *esq, TipoArvore *dir, char caractere);
TipoArvore InsereEntre(TipoChave palavra, TipoArvore *NoAtual, int i, char caractere_interno);
TipoArvore Insere(TipoChave palavra, TipoArvore *t);
void Pesquisa(TipoChave palavra, TipoArvore NoRaiz);
short Eh_Externo(TipoArvore p);

#endif