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
void constroiIndices(TipoArvore *patricia);
void imprimeIndices(TipoArvore patricia);
void pesquisa(InfoBasica info, TipoArvore raiz);
void menu();
void tfidfpat(TipoArvore raiz, char **input, Relevancias * doc, int nDOCS);
float sumPtermo(TipoArvore raiz, int nDOCS, char *input, int idDoc);

#endif

