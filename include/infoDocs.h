/**
 * @author Beatriz Queiroz - 5890
 * @author Heitor Porto - 5895
 * @author Pâmela Lúcia - 5898
 * @author Júlio César - 5903
 * @author Otávio Tavares - 5912
 */
#ifndef INFODOCS_H
#define INFODOCS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    int nArquivos;
    char nomesOriginais[120][256];
    int sucesso;
}InfoBasica;

typedef struct{
    int id;
    float relevancia;
}Relevancias;


int getNumeroArquivos(InfoBasica *info);

// Retorna o nome original de um arquivo pelo iddoc
char *getNomeOriginal(InfoBasica *info, int idDoc);


#endif