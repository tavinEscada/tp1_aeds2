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

/**trata tanto acentos quanto maiusculas*/
void formataPalavra(char *p){
    removeAcentos(p);
    removeMaiusculas(p);
}

//há palavras de mais de 2 caracteres que não precisam ser levadas em conta
int ehRelevante(char *p){
    char *irrelevantes[] = {"isso", "uma", "com", "por", "the", "sua", "elas", "that", "not",
        "seu", "como", "nao", "que", "para", "dos", "ela", "ele", "nem", "eles", "this", "are",
        "das", "mas", "desse", "dessa", "esta", "esse", "essa", "desta", "tem", "for", "and"};

    int n = sizeof(irrelevantes)/sizeof(irrelevantes[0]);

    for(int i = 0; i < n; i++){
        if(strcmp(p, irrelevantes[i]) == 0){
            return 0;
        }
    }
    return 1;

}

int ehValida(char *p){

    removeAcentos(p);

    int t = strlen(p);

    //caracteres especiais que possam ter sobrado (como '20%')
    for(int j = 0; j < t; j++){
        if(!isalpha(p[j])){
            return 0;
        }
    }

    if(t < 3){

        //uma letra só
        if(t == 1){
            return 0;
        }

        //duas letras, mas não é sigla
        for(int i = 0; i < t; i++){
            if(islower(p[i])){
                return 0;
            }
        }
    }

    removeMaiusculas(p);

    if(!ehRelevante(p)){
        return 0;
    }

    return 1;
    
}

void removerArqs(int nArqAtual) {
    char nomeArquivo[TMAX];
    
    //começa do próximo arquivo após o último lido
    for(int i = nArqAtual + 1; ; i++){
        //monta o nome do arquivo a ser removido
        snprintf(nomeArquivo, sizeof(nomeArquivo), "./arquivosTratados/arquivo%d.txt", i);
        
        //testa se o arquivo existe
        FILE *teste = fopen(nomeArquivo, "r");
        if(teste == NULL){
            //não existe
            break;
        }
        
        fclose(teste);
        
        if(remove(nomeArquivo) == 0){
            printf("Arquivo remanescente removido: arquivo%d.txt\n", i);
        }else{
            printf("Erro ao remover arquivo%d.txt\n", i);
        }
    }
}

/**leitura do arquivo de entrada e dos arquivos contidos nele*/
void receberArquivo(){
    
    char nome[256];
    int nArq = 0;

    printf("Nome do arquivo:\n");
    scanf("%s", nome);

    FILE *arq = fopen(nome, "r");

    if(arq == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    fscanf(arq, "%d", &nArq);
    fgets(nome, sizeof(nome), arq);

    if(nArq <= 0){
        printf("N de arquivos invalido\n");
        return;
    }

    //nenhum problema na leitura (arquivo valido, qtd valida, etc)

    //criando a pasta que armazenará os arquivos com as palavras já separadas e formatadas
    mkdir("./arquivosTratados");

    char cEntrada[8] = "./pocs/";
    char cSaida[21] = "./arquivosTratados/";


    for(int i = 1; i <= nArq; i++){

        int nPalavras = 0;

        fgets(nome, 256, arq);

        //remover possíveis '\r' (do linux) e '\n' no final das palavras e trocar por '\0' (fim da palavra)
        nome[strcspn(nome, "\r\n")] = '\0';

        char entrada[TMAX];
        char saida[TMAX];

        //juntando o prefixo do endereço dos arquivos ('.\pocs') com o nome de cada arquivo
        snprintf(entrada, TMAX, "%s%s", cEntrada, nome);


        snprintf(saida, TMAX, "%sarquivo%d.txt", cSaida, i);

        FILE *arquivoAtual = fopen(entrada, "r");
        FILE *saidaAtual = fopen(saida, "w");

        if(arquivoAtual == NULL){
            printf("Erro ao abrir o arquivo '%s'\n", nome);
            //conferir pra ver se vamos continuar lendo o resto mesmo ou para tudo!!!
            continue;
        }
        if(saidaAtual == NULL){
            printf("erro ao criar o arquivo de saida %d\n\n", i);
            //conferir tbm se continua
            continue;
        }

        char linha[256];

        //testando o print de cada palavra de cada arquivo
        //printf("Palavras do arquivo %d ('%s'):\n", i, nome);
        while(fgets(linha, sizeof(linha), arquivoAtual) != NULL){
            //tokenizando cada linha
            linha[strcspn(linha, "\n")] = '\0';

            //pegando a primeira palavra da linha
            char *palavra = strtok(linha, " .,:;()\"'-/?\r\n");

            while(palavra != NULL){

                //depois das verificações, pegando apenas as palavra válidas
                if(ehValida(palavra)){

                    fprintf(saidaAtual, "%s\n", palavra);

                    //printf("%s\n", palavra);
                    nPalavras++;
                }
                
                //passando para a próxima palavra da linha
                palavra = strtok(NULL, " .,:;()\"'-/?\r\n");
            }
            
        }
        //printf("\nO arquivo %d ('%s') tem %d palavras.\n\n", i, nome, nPalavras);

        fclose(arquivoAtual);
        fclose(saidaAtual);

    }
    //removendo arquivos que possam ter sobrado da última execução
    removerArqs(nArq);

    fclose(arq);
}

void constroiIndices(){
    char enderecoTextos[50] = "./arquivosTratados/";
    char nomeCompleto[TMAX];

    snprintf(nomeCompleto, TMAX, "%s%s%d%s", enderecoTextos, "arquivo", 1, ".txt");
    FILE *arqAtual = fopen(nomeCompleto, "r");

    char palavra[200];

    Inicializa(Tabela);
    GeraPesos(p);   
    
    for(int i = 1; arqAtual;){
        char nNome[40];
        while(fgets(palavra, sizeof(palavra), arqAtual) != NULL){
            //ADICIONAR NA ARVORE E NA TABELA aqui!!! (idDoc pode ser o 'i')
            palavra[strcspn(palavra, "\n")] = '\0';
            Insere(palavra,i,Tabela,p);


            //printf("%s", palavra);
            
        }
        i++;
        snprintf(nNome, TMAX, "%s%s%d%s", enderecoTextos, "arquivo", i, ".txt");
        arqAtual = fopen(nNome, "r");

    }
}

void imprimeIndices(){

}

//usar a funcao formataPalavra!!!
void pesquisa(){
    
}

/**função que faz o loop do menu até que o usuário digite 0*/
void menu(){
    
    int op = 0;
    do{
        printf("--- Menu ---\n1 - Ler o arquivo com os textos\n2 - Construir os indices invertidos\n3 - Exibir os indices invertidos\n4 - Busca\n0 - Fechar\n");
        scanf("%d", &op);

        switch(op){
            case 1:
                receberArquivo();
                break;
            case 2:
                constroiIndices();
                break;

            case 3:
                //exibir os indices construidos
                Imprimir(Tabela);
                imprimeIndices();
                break;

            case 4:
                pesquisa();
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
