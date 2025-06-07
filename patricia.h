#ifndef PATRICIA_H
#define PATRICIA_H

#include <string.h>
#include<stdlib.h> 
#include <sys/time.h>
#define DE 8   /* depende de TipoChave */
#define max 50 // mudar para receber como parâmetro o numero de pocs

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
      TipoArvore A,B,C,D,E,F,G,H,I,J,K,L,M,N,o,P,Q,R,S,T,U,V,W,X,Y,Z;
    } NInterno ;
    TipoChave Chave[255];
    par indinv[max];
  } NO;
} TipoPatNo;

#endif