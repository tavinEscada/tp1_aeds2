/**
 * @author Beatriz Queiroz - 5890
 * @author Heitor Porto - 5895
 * @author Pâmela Lúcia - 5898
 * @author Júlio César - 5903
 * @author Otávio Tavares - 5912
 */
#ifndef TP_H
#define TP_H

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

