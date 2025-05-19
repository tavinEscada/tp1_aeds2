#include <stdio.h>
#include <stdlib.h>

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
                printf("Entrada invalida.");
                break;
        }

    }while(op!=0);
}