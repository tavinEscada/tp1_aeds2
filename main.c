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

/**leitura do arquivo de entrada e dos arquivos contidos nele*/
void receberArquivo(){
    char nome[100];

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

        FILE *arquivoAtual = fopen(nome, "r");

        if(arquivoAtual == NULL){
            printf("Erro ao abrir o arquivo '%s'\n", nome);
            continue;
        }
        char linha[256];

        //testando o print de cada palavra de cada arquivo
        printf("Palavras do arquivo %d:\n", i+1);
        while(fgets(linha, sizeof(linha), arquivoAtual) != NULL){
            //remover possíveis '\n' do final da palavra e trocar por '\0' (fim da palavra)
            linha[strcspn(linha, "\n")] = '\0';

            
            char *palavra = strtok(linha, " .,:;()-/?\n");
            

            while(palavra != NULL){
                printf("%s\n", palavra);
                nPalavras++;
                palavra = strtok(NULL, " .,:;()-/?\n");
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