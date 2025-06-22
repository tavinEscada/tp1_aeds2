#ifndef INFODOCS_H
#define INFODOCS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int nArquivos;
    char nomesOriginais[200][256];
    int sucesso;
} InfoBasica;


int getNumeroArquivos(InfoBasica *info);

// Retorna o nome original de um arquivo pelo iddoc
char *getNomeOriginal(InfoBasica *info, int idDoc);


#endif