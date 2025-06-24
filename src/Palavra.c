#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Palavra.h"

extern unsigned long long int comp_insercao_hash;
extern unsigned long long int comp_busca_hash;


void faz_palavra_vazia(TipoItemP * item, char * palavra){
    item->primeiro = (Ccelula*)malloc(sizeof(Ccelula));
    item->primeiro->prox = NULL;
    strcpy(item->palavra,palavra);
    item->n_arquivos = 0;
    item->total_ocorrencias = 0;
}

void imprime_indice_invertido(TipoItemP * item){
    printf("%s: ", item->palavra);

    Ccelula * aux;
    aux = item->primeiro;

    while(aux->prox != NULL){
        
        if(aux->prox->prox != NULL){
            printf("<%d , %d> | ", aux->prox->qtde, aux->prox->idDoc);
        }else{
            printf(" <%d , %d> ", aux->prox->qtde, aux->prox->idDoc);
        }

        aux = aux->prox;
    }
    printf("\n");
}

void insere_palavra (TipoItemP * item, int idDoc){

    Ccelula * aux;
    aux = item->primeiro;


    while(aux->prox != NULL){
		comp_insercao_hash++;
        if(aux->prox->idDoc == idDoc){ //se esse documento ja teve essa palavra antes, a quantidade só incrementa
            aux->prox->qtde++;
            item->total_ocorrencias++;
            return;
        }

        aux = aux->prox;

    } // se saiu do while é pq é a primeira vez que essa palavra aparece nesse documento, logo devemos adicioná-lo

    aux->prox = (Ccelula*)malloc(sizeof(Ccelula));
    aux->prox->prox = NULL;
    aux->prox->idDoc = idDoc;
    aux->prox->qtde = 1;
    item->n_arquivos++;
    item->total_ocorrencias++;
    
    return;
    
}

int remove_palavra (TipoItemP * item, int idDoc){

    Ccelula * anterior;
    Ccelula * aux;

    anterior = item->primeiro;
    aux = item->primeiro->prox;

    while(aux != NULL){
        if(aux->idDoc == idDoc){//tenta achar o documento
            
            printf("palavra removida do arquivo %d, ", aux->idDoc);

            if(aux->qtde > 1){
                aux->qtde--;
                item->total_ocorrencias--;
                printf("%d restantes \n", aux->qtde);
            }else{
                anterior->prox = aux->prox;
                free(aux);
                item->n_arquivos--;
                item->total_ocorrencias--;
                printf("0 restantes \n");
            }
            return 1;
        }

        anterior = anterior->prox;
        aux = aux->prox;
    }

    printf("palavra nao esta presente no arquivo\n");
    return 0;
}
QuantidadeTermosPorDoc
int (TipoItemP item, int idDoc){

    Ccelula * aux;
    aux = item->primeiro;


    while(aux->prox != NULL && aux->prox->idDoc <= idDoc){
        if(aux->prox->idDoc == idDoc){
            return aux->prox->qtde;
        }

        aux = aux->prox;

    }
    
    return 0;
    
}