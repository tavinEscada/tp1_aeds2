#include "../include/infoDocs.h"

int getNumeroArquivos(InfoBasica *info){
    return info->nArquivos;
}

// Retorna o nome original de um arquivo pelo iddoc
char *getNomeOriginal(InfoBasica *info, int idDoc){
    char *nome = info->nomesOriginais[idDoc-1];
    return nome;
}

