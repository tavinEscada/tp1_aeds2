#ifndef PATRICIA_H
#define PATRICIA_H

#include <string.h>
#include<stdlib.h> 
#include <sys/time.h>
#define DE 8   /* depende de TipoChave */

typedef unsigned char TipoChave; /* a definir, dependendo da aplicacao */
typedef unsigned char TipoIndexAmp;
typedef unsigned char TipoDib;

typedef struct{
    int qtde;
    int iddoc;
}par;

typedef enum {
  Interno, Externo
} TipoNo;

typedef struct TipoPatNo* TipoArvore; 
typedef struct TipoPatNo {
  TipoNo nt;
  union {
    struct {
      TipoChave caractere;
      TipoIndexAmp Index;
      TipoArvore Esq,Dir;
    } NInterno ;
    TipoChave Chave[255];
    par indinv[20]; //colocar como lista encdeada
  } NO;
} TipoPatNo;

#endif