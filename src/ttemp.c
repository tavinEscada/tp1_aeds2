#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#define M 7 //tamanho da tabela
#define N 7 //tamanho da palavra
#define TAMALFABETO 256 // ?

/* typedef unsigned int  TipoPesos[n]; */
typedef char TipoChave[N]; //palavra
typedef unsigned TipoPesos[N][TAMALFABETO]; //nao sei pq esta assim
typedef struct TipoItem {
  /* outros componentes */
  TipoChave Chave;
} TipoItem; // pesquisar
typedef unsigned int TipoIndice;
typedef struct TipoCelula* TipoApontador;
typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;
typedef struct TipoLista {
  TipoCelula *Primeiro, *Ultimo;
} TipoLista;
typedef TipoLista TipoDicionario[M];
TipoDicionario Tabela;
TipoItem Elemento;
TipoPesos p;
TipoApontador i;


short Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo); }

void Ins(TipoItem x, TipoLista *Lista)
{ Lista->Ultimo->Prox = (TipoCelula *)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Ultimo->Prox; Lista->Ultimo->Item = x;
  Lista->Ultimo->Prox = NULL;
}

void Ret(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{  /* -- Obs.: o item a ser retirado o seguinte ao apontado por p -- */
  TipoApontador q;
  if (Vazia(*Lista) || p == NULL || p->Prox == NULL)
  { printf(" Erro Lista vazia ou posicao nao existe\n");
    return;
  }
  q = p->Prox; *Item = q->Item; p->Prox = q->Prox;
  if (p->Prox == NULL)
  Lista->Ultimo = p;
  free(q);
}


TipoApontador Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T)
{ /* Obs.: TipoApontador de retorno aponta para o item anterior da lista */
  TipoIndice i;
  TipoApontador Ap;
  i = h(Ch, p);
  if (Vazia(T[i])) return NULL;  /* Pesquisa sem sucesso */
  else
  { Ap = T[i].Primeiro;
    while (Ap->Prox->Prox != NULL &&
        strncmp(Ch, Ap->Prox->Item.Chave, sizeof(TipoChave)))
      Ap = Ap->Prox;
    if (!strncmp(Ch, Ap->Prox->Item.Chave, sizeof(TipoChave)))
    return Ap;
    else return NULL;  /* Pesquisa sem sucesso */
  }
}
//fazer uma funçao de conferir se essa palavra ja foi inserida (como?) se sim fazer chama para add + 1 no indice do texto que ela esta se nao cria um indice daquele texto
//como vou conferir em qual texto esta
void Insere(TipoItem x, TipoPesos p, TipoDicionario T)
{ if (Pesquisa(x.Chave, p, T) == NULL)
  Ins(x, &T[h(x.Chave, p)]);
  else printf(" Registro ja  esta  presente\n");
}

void Retira(TipoItem x, TipoPesos p, TipoDicionario T)
{ TipoApontador Ap; Ap = Pesquisa(x.Chave, p, T);
  if (Ap == NULL)
  printf(" Registro nao esta  presente\n");
  else Ret(Ap, &T[h(x.Chave, p)], &x);
}
//imprime
void Imp(TipoLista Lista)
{ TipoApontador Aux;
  Aux = Lista.Primeiro->Prox;
  while (Aux != NULL)
    { printf("%.*s ", N, Aux->Item.Chave);
      Aux = Aux->Prox;
    }
}

void Imprime(TipoDicionario Tabela)
{ int i;
  for (i = 0; i < M; i++)
    { printf("%d: ", i);
      if (!Vazia(Tabela[i]))
      Imp(Tabela[i]);
      putchar('\n');
    }
}


