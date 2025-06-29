/**
 * @author Beatriz Queiroz - 5890
 * @author Heitor Porto - 5895
 * @author Pâmela Lúcia - 5898
 * @author Júlio César - 5903
 * @author Otávio Tavares - 5912
 */

#include "../include/tp.h"

// Variavies Globais para comparaçao da Hash
unsigned long long int comp_insercao_hash = 0;
unsigned long long int comp_busca_hash = 0;

int main(){
    
    TipoArvore a = NULL;
    InfoBasica info;
    int op = 0;
    int comp_insercao_pat,comp_pesquisa_pat;
    do{
        printf("--- Menu ---\n1 - Ler o arquivo com os textos\n2 - Construir os indices invertidos\n3 - Exibir os indices invertidos\n4 - Busca\n0 - Fechar\n");
        scanf("%d", &op);

        switch(op){
            case 1:
                info = receberArquivo();
                if(info.sucesso != 1){
                    printf("Leitura sem sucesso. Entre com outro arquivo ou o concerte para executar de novo.\n");
                }
                break;

            case 2:
                constroiIndices(&a,&comp_insercao_pat);
                printf("Quantidade de comparacoes na inserção: %d\n", comp_insercao_pat);
                break;

            case 3:
                imprimeIndices(a);
                break;

            case 4:
                pesquisa_geral(info, a, Tabela, p,&comp_pesquisa_pat);
                printf("Quantidade de comparacoes na pesquisa: %d\n", comp_pesquisa_pat);

                break;
            case 0:
                return 0;
                break;

            default:
                printf("Entrada invalida.\n");
                break;
        }
    }while(op != 0);

    return 0;
}
