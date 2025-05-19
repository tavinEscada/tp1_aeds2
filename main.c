/*Alunos:
Heitor Porto - 5895
Beatriz Queiroz - 5890
Pâmela Lúcia - 5898
Julio Cesar - 5903
Otávio Tavares - 5912*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void receberArquivo(){
    char nome[100];

    printf("Nome do arquivo:\n");
    scanf("%s", nome);

    FILE *arq = fopen(nome, "r");

    if(arq == NULL){
        printf("Erro ao abrir o arquivo");
        return;
    }
    int nArq = 0;

    fscanf(arq, "%d", &nArq);
    fgetc(arq);

    if(nArq <= 0){
        printf("N de arquivos invalido");
        return;
    }

    for(int i = 0; i < nArq; i++){

        fgets(nome, 256, arq);

        //remover possíveis '\n' no final das palavras e trocar por '\0' (fim da palavra)
        nome[strcspn(nome, "\n")] = '\0';

        FILE *arquivoAtual = fopen(nome, "r");

        if(arquivoAtual == NULL){
            printf("Erro ao abrir o arquivo '%s'\n", nome);
            continue;
        }
        char linha[256];

        //testando o print de cada palavra de cada arquivo
        printf("\nPalavras do arquivo %d:\n", i+1);
        while(fgets(linha, sizeof(linha), arquivoAtual) != NULL){
            //remover possíveis '\n' do final da palavra e trocar por '\0' (fim da palavra)
            linha[strcspn(linha, "\n")] = '\0';
            char *palavra = strtok(linha, " .,:;()-/");

            while(palavra != NULL){
                printf("%s\n", palavra);
                palavra = strtok(NULL, " .,:;()-/");
            }
        }

        fclose(arquivoAtual);

    }

    fclose(arq);
}


int main(){
    int op = -1;

    do{
        printf("--- Menu ---\n 1 - Ler o arquivo com os textos\n 2 - Construir os indices invertidos\n 3 - Escrever os indices invertidos\n 4 - Busca\n 0 - Fechar\n");
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
                return 0;
                break;

            default:
                printf("Entrada invalida.\n");
                break;
        }

    }while(op != 0);
}