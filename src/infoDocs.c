/**
 * @author Beatriz Queiroz - 5890
 * @author Heitor Porto - 5895
 * @author Pâmela Lúcia - 5898
 * @author Júlio César - 5903
 * @author Otávio Tavares - 5912
 */
#include "../include/infoDocs.h"

/**
 * retorna o numero de arquivos em uma execução
 * 
 * @param info a estrutura InfoBasica referente à presente execução
 * @return numero de arquivos lidos na entrada
 * 
 */
int getNumeroArquivos(InfoBasica *info){
    return info->nArquivos;
}

/**
 * retorna o nome original de um arquivo a partir do idDoc
 * 
 * @param info a estrutura InfoBasica referente à presente execução
 * @return numero de arquivos lidos na entrada
 * 
 */
char *getNomeOriginal(InfoBasica *info, int idDoc){
    char *nome = info->nomesOriginais[idDoc-1];
    return nome;
}

