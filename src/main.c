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

void formataPalavra(char *p){
    int j = 0;
    
    for(int i = 0; p[i];){

        unsigned char proxC = (unsigned char)p[i+1];
        char sub = 0;

        //UTF-8 pra acentos e tal no alfabeto latino (basic latin)
        //com 0xC3 sendo prefixo para elementos fora dos ascii normais 
        //(C3 + A1 -> 'á', por exemplo, com 0x na frente para indicar hex)
        if((unsigned char)p[i] == 0xC3){
                
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

            if(sub != 0){
                //o caractere deve ser alterado
                p[j] = sub;
                j++;
            }else{
                //manter a string pq nao precisa mudar os caracteres, e avançar para os proximos
                j += 2;
            }
            //pular os 2 bytes do trem ai, o atual e o verificado acima
            i += 2;
        }else{
            //ascii normal, alterando as maiusculas
            switch(p[i]){
            case 0x41:
                sub = 'a';
                break;

            case 0x42:
                sub = 'b';
                break;

            case 0x43:
                sub = 'c';
                break;

            case 0x44:
                sub = 'd';
                break;

            case 0x45:
                sub = 'e';
                break;

            case 0x46:
                sub = 'f';
                break;

            case 0x47:
                sub = 'g';
                break;
            
            case 0x48:
                sub = 'h';
                break;
                
            case 0x49:
                sub = 'i';
                break;

            case 0x4A:
                sub = 'j';
                break;

            case 0x4B:
                sub = 'k';
                break;

            case 0x4C:
                sub = 'l';
                break;

            case 0x4D:
                sub = 'm';
                break;

            case 0x4E:
                sub = 'n';
                break;

            case 0x4F:
                sub = 'o';
                break;

            case 0x50:
                sub = 'p';
                break;

            case 0x51:
                sub = 'q';
                break;

            case 0x52:
                sub = 'r';
                break;

            case 0x53:
                sub = 's';
                break;

            case 0x54:
                sub = 't';
                break;

            case 0x55:
                sub = 'u';
                break;

            case 0x56:
                sub = 'v';
                break;

            case 0x57:
                sub = 'w';
                break;

            case 0x58:
                sub = 'x';
                break;

            case 0x59:
                sub = 'y';
                break;

            case 0x5A:
                sub = 'z';
                break;

            default:
                break;
            }
            if(sub != 0){
                p[j] = sub;
            }else{
                p[j] = p[i];
            }
            i++;
            j++;
            
        }
    }
    //acabou a palavra com o fim do for
    p[j] = '\0';
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

    for(int i = 0; i < nArq; i++){

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
        printf("Palavras do arquivo %d:\n", i+1);
        while(fgets(linha, sizeof(linha), arquivoAtual) != NULL){
            //tokenizando cada linha
            linha[strcspn(linha, "\n")] = '\0';

            //pegando a primeira palavra da linha
            char *palavra = strtok(linha, " .,:;()\"'-/?\n+");

            while(palavra != NULL){

                formataPalavra(palavra);
                
                printf("%s\n", palavra);
                nPalavras++;

                //passando para a próxima palavra da linha
                palavra = strtok(NULL, " .,:;()\"'-/?\n+");
            }
            
        }
        printf("\nO arquivo %d tem %d palavras.\n\n", i+1, nPalavras);

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


int main(){
    
    menu();
    return 0;

}