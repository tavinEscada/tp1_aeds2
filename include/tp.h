/**
 * @author Beatriz Queiroz - 5890
 * @author Heitor Porto - 5895
 * @author Pâmela Lúcia - 5898
 * @author Júlio César - 5903
 * @author Otávio Tavares - 5912
 */
#ifndef TP_H
#define TP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#ifdef _WIN32
    #include <direct.h>
    #define mkdir(dir) _mkdir(dir)
    #define sistema 1
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #define mkdir(dir) mkdir(dir, 0755)
    #define sistema 2
#endif

#include "../include/tp.h"
#include "../include/hash.h"
#include "../include/patricia.h"
#include "../include/infoDocs.h"


#define TMAX 1042

void removeAcentos(char *p);
void removeMaiusculas(char *p);
int ehRelevante(char *p);
int ehValida(char *p);
void removerArqs(int nArqAtual);
InfoBasica receberArquivo();
void pesquisa_geral(InfoBasica info, TipoArvore raiz, TipoDicionario Tabela, TipoPesos p,int *comp_pesquisa_pat, int *comp_pesquisa_hash);
void constroiIndices(TipoArvore *patricia,int *comp_insercao_pat,int *comp_insercao_hash);
void imprimeIndices(TipoArvore patricia);
void pesquisa(InfoBasica info, TipoArvore raiz,int *comp_pesquisa_pat);
void menu();
void tfidfpat(TipoArvore raiz, char **input, Relevancias *doc, int nDOCS, int nTermos,int *comp_pesquisa_pat);
float sumPtermoPat(TipoArvore raiz, int nDOCS, char **input, int nTermos, int idDoc,int *comp_pesquisa_pat);
//HASH
void tfidfhash(TipoDicionario Tabela, char **input, Relevancias *doc, int nDOCS, int nTermos, TipoPesos p, int *comp_pequisa_hash);
float sumPtermoHash(TipoDicionario tabela, int nDOCS, char **input, int nTermos, int idDoc, TipoPesos p, int *comp_pequisa_hash);
//float sumPtermo_hash(TipoDicionario Tabela, TipoPesos p, int nDOCS, char **input, int nTermos, int idDoc);
void pesquisa_hash(TipoDicionario Tabela, InfoBasica info, TipoPesos p, int *comp_pequisa_hash);
#endif

