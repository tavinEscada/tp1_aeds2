#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/patricia_indice.h"


void Inicializa_listaIndice(Lista_Indice_Invertido* lista){

    lista->primeiro = (celula*) malloc(sizeof(celula));
    lista->ultimo = lista->primeiro;
    lista->primeiro->prox = NULL;

}

void Atualiza_Ocorrencia(Lista_Indice_Invertido* lista,int idDoc){
    celula* cel_atual=lista->primeiro;

    while(cel_atual!=NULL && cel_atual->idDoc!=idDoc){
        cel_atual=cel_atual->prox;
    }

    if (cel_atual==NULL){
        Insere_Ocorrencia(lista,idDoc);
    }
    else{
        Incrementa_Ocorrencia(cel_atual);
    }
    
}

void Insere_Ocorrencia(Lista_Indice_Invertido* lista,int idDoc){

    lista->ultimo->prox = (celula*) malloc(sizeof(celula));
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->idDoc = idDoc;
    lista->ultimo->qtde = 1;
    lista->ultimo->prox = NULL;

}

void Incrementa_Ocorrencia(celula* celula){
    celula->qtde+=1;
}

void Imprime_ListaIndice (Lista_Indice_Invertido* lista){

    celula* aux;
    aux = lista->primeiro->prox;
    while (aux != NULL){
        
        if (aux->prox==NULL)
            printf("< %d , %d >", aux->idDoc,aux->qtde);
        else
            printf("< %d , %d > | ", aux->idDoc,aux->qtde);

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
