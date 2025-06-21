#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/patricia_indice.h"


void Inicializa_listaIndice(TipoItem* no_palavra){

    no_palavra->lista.primeiro = (celula*) malloc(sizeof(celula));
    no_palavra->lista.ultimo = no_palavra->lista.primeiro;
    no_palavra->lista.primeiro->prox = NULL;

}

void Atualiza_Ocorrencia(TipoItem* no_palavra,int idDoc){
    celula* cel_atual=no_palavra->lista.primeiro->prox;

    while(cel_atual!=NULL && cel_atual->idDoc!=idDoc){
        cel_atual=cel_atual->prox;
    }

    if (cel_atual==NULL){
        Insere_Ocorrencia(no_palavra,idDoc);
    }
    else{
        Incrementa_Ocorrencia(cel_atual);
    }
    
}

void Insere_Ocorrencia(TipoItem* no_palavra,int idDoc){

    no_palavra->lista.ultimo->prox = (celula*) malloc(sizeof(celula));
    no_palavra->lista.ultimo = no_palavra->lista.ultimo->prox;
    no_palavra->lista.ultimo->idDoc = idDoc;
    no_palavra->lista.ultimo->qtde = 1;
    no_palavra->n_arquivos+=1;
    no_palavra->lista.ultimo->prox = NULL;

}

void Incrementa_Ocorrencia(celula* celula){
    celula->qtde+=1;
}

void Imprime_ListaIndice (Lista_Indice_Invertido lista){

    celula* aux;
    aux = lista.primeiro->prox;
    while (aux != NULL){
        
        if (aux->prox==NULL)
            printf("< %d, %d >", aux->qtde, aux->idDoc);
        else
            printf("< %d, %d > | ", aux->qtde, aux->idDoc);

    aux = aux->prox; 
    }

}

int Contabiliza_Docs(Lista_Indice_Invertido* lista){

    celula* aux=NULL;
    aux=lista->primeiro->prox;
    int count=0;

    while(aux!=NULL){

        count+=1;
        aux=aux->prox;

    }

    return count;

}
