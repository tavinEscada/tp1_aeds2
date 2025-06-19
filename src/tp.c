/**
 * @author Beatriz Queiroz - 5890
 * @author Heitor Porto - 5895
 * @author Pâmela Lúcia - 5898
 * @author Júlio César - 5903
 * @author Otávio Tavares - 5912
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/tp.h"

/**
 * Dada uma palavra, substitui 
 * caracteres especiais (letras com acentos e cedilha) 
 * por minúsculas sem acento
 * 
 * @param p vetor de caracteres com a palavra que será adaptada
 * 
 */
void removeAcentos(char *p){
    int j = 0;
    
    for(int i = 0; p[i];){

        char sub = 0;

        //UTF-8 pra acentos e tal no alfabeto latino (basic latin)
        //com 0xC3 sendo prefixo para elementos fora dos ascii normais 
        //(C3 + A1 -> 'á', por exemplo, com 0x na frente para indicar hex)
        if((unsigned char)p[i] == 0xC3){
              
            unsigned char proxC = (unsigned char)p[i+1];

            //á à ã â, o mesmo pro maiusculo com acentos
            if(proxC == 0xA1 || proxC == 0xA0 || proxC == 0xA3 || proxC == 0xA2 
                || proxC == 0x81 || proxC == 0x80 || proxC == 0x83 || proxC == 0x82){
                sub = 'a';
            }

            //é ê, o mesmo pros maiusculos
            if(proxC == 0xA9 || proxC == 0xAA || proxC == 0x89 || proxC == 0x8A){
                sub = 'e';
            }

            //í Í
            if(proxC == 0xAD || proxC == 0x8D){
                sub = 'i';
            }

            //ó ò ô õ, o mesmo pros maísculos
            if(proxC == 0xB3 || proxC == 0xB2 || proxC == 0xB4 || proxC == 0xB5 
                || proxC == 0x93 || proxC == 0x92 || proxC == 0x94 || proxC == 0x95){
                sub = 'o';
            }

            //ú ù û, o mesmo para maiúsculo
            if(proxC == 0xBA || proxC == 0xB9 || proxC == 0xBB || proxC == 0x9A 
                || proxC == 0x99 || proxC == 0x9B){
                sub = 'u';
            }

            //ç Ç
            if(proxC == 0xA7 || proxC == 0x87){
                sub = 'c';
            }

            if(sub){
                //alterando o caractere
                p[j] = sub;
                j++;
            }
            
            
            //pular os 2 bytes do trem ai, o atual e o verificado acima
            i += 2;
        }else{
            
            p[j] = p[i];
            
            i++;
            j++;
            
        }
    }
    //acabou a palavra com o fim do for
    p[j] = '\0';
}

/**
 * Dada uma palavra, substitui letras maiúsculas por minúsculas
 * 
 * @param p vetor de caracteres com a palavra que será adaptada
 * 
 */
void removeMaiusculas(char *p){
    for(int i = 0; p[i]; i++){
        char sub = 0;
        switch(p[i]){
                
            case 'A':
                sub = 'a';
                break;
            case 'B':
                sub = 'b';
                break;
            case 'C':
                sub = 'c';
                break;
            case 'D':
                sub = 'd';
                break;
            case 'E':
                sub = 'e';
                break;
            case 'F':
                sub = 'f';
                break;
            case 'G':
                sub = 'g';
                break;
            case 'H':
                sub = 'h';
                break;
            case 'I':
                sub = 'i';
                break;
            case 'J':
                sub = 'j';
                break;
            case 'K':
                sub = 'k';
                break;
            case 'L':
                sub = 'l';
                break;
            case 'M':
                sub = 'm';
                break;
            case 'N':
                sub = 'n';
                break;
            case 'O':
                sub = 'o';
                break;
            case 'P':
                sub = 'p';
                break;
            case 'Q':
                sub = 'q';
                break;
            case 'R':
                sub = 'r';
                break;
            case 'S':
                sub = 's';
                break;
            case 'T':
                sub = 't';
                break;
            case 'U':
                sub = 'u';
                break;
            case 'V':
                sub = 'v';
                break;
            case 'W':
                sub = 'w';
                break;
            case 'X':
                sub = 'x';
                break;
            case 'Y':
                sub = 'y';
                break;
            case 'Z':
                sub = 'z';
                break;

            default:
                break;
                
        }
        if(sub){
            p[i] = sub;
        }
    }
}


/**leitura do arquivo de entrada e dos arquivos contidos nele*/
void receberArquivo(){
    char nome[256];
    char pasta[8] = "./pocs/";

    printf("Nome do arquivo:\n");
    scanf("%s", nome);

    FILE *arq = fopen(nome, "r");

    if(arq == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    int nArq = 0;

    fscanf(arq, "%d", &nArq);
    fgetc(arq);

    if(nArq <= 0){
        printf("N de arquivos invalido\n");
        return;
    }

    for(int i = 1; i <= nArq; i++){

        int nPalavras = 0;

        fgets(nome, 256, arq);

        //remover possíveis '\n' no final das palavras e trocar por '\0' (fim da palavra)
        nome[strcspn(nome, "\n")] = '\0';

        char caminho[256];

        //juntando o prefixo do endereço dos arquivos ('.\pocs') com o nome de cada arquivo
        snprintf(caminho, 256, "%s%s", pasta, nome);

        FILE *arquivoAtual = fopen(caminho, "r");

        if(arquivoAtual == NULL){
            printf("Erro ao abrir o arquivo '%s'\n", nome);
            //conferir pra ver se vamos continuar lendo o resto mesmo ou para tudo!!!
            continue;
        }
        char linha[256];

        //testando o print de cada palavra de cada arquivo
        printf("Palavras do arquivo %d ('%s'):\n", i, nome);
        while(fgets(linha, sizeof(linha), arquivoAtual) != NULL){
            //tokenizando cada linha
            linha[strcspn(linha, "\n")] = '\0';

            //pegando a primeira palavra da linha
            char *palavra = strtok(linha, " .,:;()\"'-/?\n");

            while(palavra != NULL){

                removeAcentos(palavra);
                
                //si pa é bom passar para uma funcao
                int ehPalavra = 1;

                unsigned int tPalavra = strlen(palavra);

                //verificando a existência de caracteres especiais que possam ter sobrado
                for(unsigned int j = 0; j < tPalavra; j++){
                    if(!isalpha(palavra[j])){
                        ehPalavra = 0;
                        break;
                    }
                }

                //removendo palavras de duas letras ou menos que não sejam siglas
                if(tPalavra <= 2 && ehPalavra){
                    for(unsigned int j = 0; j < tPalavra; j++){
                        if(islower(palavra[j]) || tPalavra < 2){
                            ehPalavra = 0;
                            break;
                        }
                    }
                }

                //depois das verificações, pegando apenas as palavra válidas
                if(ehPalavra){
                    removeMaiusculas(palavra);
                    printf("%s\n", palavra);
                    nPalavras++;
                }
                
                //passando para a próxima palavra da linha
                palavra = strtok(NULL, " .,:;()\"'-/?\n");
            }
            
        }
        printf("\nO arquivo %d ('%s') tem %d palavras.\n\n", i, nome, nPalavras);

        fclose(arquivoAtual);

    }

    fclose(arq);
}

/**função que faz o loop do menu até que o usuário digite 0*/
void menu(){
    
    int op = 0;
    do{
        printf("--- Menu ---\n1 - Ler o arquivo com os textos\n2 - Construir os indices invertidos\n3 - Escrever os indices invertidos\n4 - Busca\n0 - Fechar\n");
        scanf("%d", &op);

        switch(op){
            case 1:
                receberArquivo();
                break;
            case 2:
                //construcao dos indices

                break;

            case 3:
                //exibir os indices construidos

                break;

            case 4:
                //realizar busca

                break;
            case 0:
                return;
                break;

            default:
                printf("Entrada invalida.\n");
                break;
        }
    }while(op != 0);
}