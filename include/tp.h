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

#ifdef _WIN32
    #include <direct.h>
    #define mkdir(dir) _mkdir(dir)
    #define getcwd _getcwd
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #define mkdir(dir) mkdir(dir, 0755)
#endif

#include "../include/tp.h"
#include "../include/hash.h"

#define TMAX 1042

void removeAcentos(char *p);
void removeMaiusculas(char *p);
void formataPalavra(char *p);
int ehRelevante(char *p);
int ehValida(char *p);
void removerArqs(int nArqAtual);
void receberArquivo();
void constroiIndices();
void imprimeIndices();
void pesquisa();
void menu();

#endif

