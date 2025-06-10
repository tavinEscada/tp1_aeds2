#include "../include/hash.h"



void FLVazia(TipoLista *Lista){
	Lista->Primeiro = (TipoCelula *)malloc(sizeof(TipoCelula));
  	Lista->Ultimo = Lista->Primeiro; Lista->Primeiro->Prox = NULL;
}
void Inicializa(TipoDicionario T){
	int i;
  	for (i = 0; i < M; i++) FLVazia(&T[i]);
}

void GeraPesos(TipoPesos p)
{ /* Gera valores randomicos entre 1 e 10.000 */
  int i, j;
  struct timeval semente;
  /* Utilizar o tempo como semente para a funcao srand() */
  gettimeofday(&semente, NULL);
  srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
  for (i = 0; i < N; i++)
    for (j = 0; j < TAMALFABETO; j++)
      p[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
}

TipoIndice h(Tipopalavra palavra, TipoPesos p)
{ int i; unsigned int Soma = 0;
  int comp = strlen(palavra);
  for (i = 0; i < comp; i++) Soma += p[i][(unsigned int)palavra[i]];
  return (Soma % M);
}
