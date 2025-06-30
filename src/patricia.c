/**
 * @author Beatriz Queiroz - 5890
 * @author Heitor Porto - 5895
 * @author Pâmela Lúcia - 5898
 * @author Júlio César - 5903
 * @author Otávio Tavares - 5912
 */

#include "../include/patricia.h"

/**
 * @brief Essa função verifica se o nó é externo ou não.
 * @param NO Ponteiro do nó que será verificado.
 * @return Retorna 1 se for externo, 0 se for interno.
 */
short Eh_ExternoPat(TipoArvore NO){ 
    return (NO->tipo_no == Externo);
}

/**
 * @brief Essa função aloca um nó interno na árvore patricia e o inicializa com valores.
 * @param i Índice do caractere que difere.
 * @param esq Ponteiro para o nó esquerdo.
 * @param dir Ponteiro para o nó direito.
 * @param caractere Caractere que será armazado e usado para comparação.
 * @return Retorna um ponteiro para o nó criado.
 */
TipoArvore Cria_NO_InternoPat(int i, TipoArvore *esq,  TipoArvore *dir, char caractere){ 

    TipoArvore Novo_NO;
    Novo_NO = (TipoArvore)malloc(sizeof(NO_patricia));

    Novo_NO->tipo_no = Interno; 
    Novo_NO->NO.NInterno.esq = *esq;
    Novo_NO->NO.NInterno.dir = *dir;
    Novo_NO->NO.NInterno.indice = i;
    Novo_NO->NO.NInterno.caractere = caractere;

    return Novo_NO;
} 

/**
 * @brief Essa função aloca um nó externo na árvore patricia e o inicializa com valores.
 * @param palavra Se trata da palavra que será armazenada.
 * @param idDoc É o identificador do documento a que a palavra pertence.
 * @return Retorna um ponteiro para o nó criado .
 */
TipoArvore Cria_NO_ExternoPat(char* palavra,int idDoc){ 
    
    TipoArvore Novo_NO;
    Novo_NO = (TipoArvore)malloc(sizeof(NO_patricia));
    Novo_NO->tipo_no = Externo; 

    faz_palavra_vazia(&Novo_NO->NO.chave,palavra);
    insere_palavra(&Novo_NO->NO.chave,idDoc);
    
    return Novo_NO;
}  

/**
 * @brief Essa função busca por uma palavra na árvore patrícia.
 * @param palavra Se trata da palavra que será buscada.
 * @param NoRaiz Inicialmente se trata da raiz da árvore mas é atualizado durante as chamadas recursivas, representando o nó atual de verificação.
 * @param comp_pesquisa_pat Uma varável auxiliar que conta o número de comparações feitas entre a palavra buscada e os caracteres dos nós internos.
 * @return Retorna um TipoItemP que é uma struct com a palavra buscada e informações adicionais, ou um item vazio se a palavra não for encontrada.
 */
TipoItemP PesquisaPat(char* palavra, TipoArvore NoRaiz, int* comp_pesquisa_pat) {

    TipoArvore NoAtual=NoRaiz;

    if (Eh_ExternoPat(NoAtual)) {
        if (strcmp((const char*)palavra, (const char*)NoAtual->NO.chave.palavra) == 0){
            return (NoAtual->NO.chave);
        }
        else{
            //printf("Elemento nao encontrado\n");
            TipoItemP vazio;
            vazio.palavra[0]='\0';
            return vazio;
        }

    }

    if (palavra[NoAtual->NO.NInterno.indice] >= NoAtual->NO.NInterno.caractere){
        (*comp_pesquisa_pat)++;
        return PesquisaPat(palavra, NoAtual->NO.NInterno.dir,comp_pesquisa_pat);
    }
    else{
        (*comp_pesquisa_pat)++;
        return PesquisaPat(palavra, NoAtual->NO.NInterno.esq,comp_pesquisa_pat);
    }
}

/**
 * @brief Essa função insere uma palavra na árvore patrícia, criando nós internos ou externos e distribui as palavras de forma que aquelas com caracteres de comparação maiores ou iguais ao nó interno vão para a direita e menores vão para a esquerda.
 * @param palavra Se trata da palavra que será inserida.
 * @param idDoc É o identificador do documento a que a palavra pertence. 
 * @param NoAtual É um ponteiro para nó da árvore.
 * @param i É o índice do caractere que difere entre a palavra e o nó atual.
 * @param caractere_interno É o cracatere que será guardado no nó interno e usado para comparações.
 * @return Retorna um ponteiro para o nó atualizado após a inserção
 */
TipoArvore InsereEntrePat(char* palavra,int idDoc, TipoArvore *NoAtual, int i, char caractere_interno,int *comp_insercao_pat){
  
    TipoArvore NoExt;
    if (Eh_ExternoPat(*NoAtual) || i < (*NoAtual)->NO.NInterno.indice){
        
        NoExt = Cria_NO_ExternoPat(palavra,idDoc);
    
        if (palavra[i] >= caractere_interno){
            return (Cria_NO_InternoPat(i, NoAtual, &NoExt,caractere_interno)); //nova palavra a direita
        }
        else{
            return (Cria_NO_InternoPat(i, &NoExt, NoAtual,caractere_interno)); //nova palavra a esquerda
        }
    } 
    else{
        //busca local de inserção
        if (palavra[(*NoAtual)->NO.NInterno.indice] >= (*NoAtual)->NO.NInterno.caractere){
            (*comp_insercao_pat)++;
            (*NoAtual)->NO.NInterno.dir = InsereEntrePat(palavra,idDoc,&(*NoAtual)->NO.NInterno.dir,i,caractere_interno,comp_insercao_pat);
        }
        else{
            (*comp_insercao_pat)++;
            (*NoAtual)->NO.NInterno.esq = InsereEntrePat(palavra,idDoc,&(*NoAtual)->NO.NInterno.esq,i,caractere_interno,comp_insercao_pat);
        }
        return (*NoAtual);
    }
}

/**
 * @brief Essa função encontra o local de inserção da palavra na árvore e também decide o caractere que difere caso haja necessidade de um novo nó interno.
 * @param palavra Se trata da palavra que será inserida.
 * @param idDoc É o identificador do documento a que a palavra pertence. 
 * @param NoRaiz É um ponteiro para a raiz da árvore.
 * @param comp_insercao_pat Variável auxiliar para contabilizar a quantidade de comparações necessárias para a inserção.
 * @return Retorna a árvore atualizada após a inserção.
 */
TipoArvore InserePat(char* palavra, int idDoc, TipoArvore *NoRaiz,int* comp_insercao_pat){
  
    TipoArvore NoAtual;
    unsigned int i;
    char caractere_dif;
          
    if (*NoRaiz == NULL){
        return (Cria_NO_ExternoPat(palavra,idDoc)); //Inserção em uma árvore vazia
    }
    else{
     
        NoAtual = *NoRaiz;

        while (!Eh_ExternoPat(NoAtual)){

            (*comp_insercao_pat)++;

            if (palavra[NoAtual->NO.NInterno.indice] >= NoAtual->NO.NInterno.caractere){
                NoAtual = NoAtual->NO.NInterno.dir;
            }
            else{
                NoAtual = NoAtual->NO.NInterno.esq;
            }
        }

        i = 0;
        //Encontra o índice em que a palavra difere do nó atual
        while (i<= strlen((const char*)palavra) && palavra[i] == NoAtual->NO.chave.palavra[i])
            i++;

        if (i > strlen((const char*)palavra)){
            //Se entrar aqui, a palavra já existe na árvore, então só é incrementada a ocorrência
            insere_palavra(&NoAtual->NO.chave,idDoc);
            return (*NoRaiz); 
            
        }
        else{
            caractere_dif=NoAtual->NO.chave.palavra[i];
            //garante que o caractere guardado no nó interno será sempre o maior
            //prefixos irão sempre para a esquerda pois \0 é menor que todos caracteres
            return InsereEntrePat(palavra, idDoc, NoRaiz, i, (palavra[i] > caractere_dif) ? palavra[i] : caractere_dif,comp_insercao_pat);
        }
    }
}


/**
 * @brief Essa função imprime as palavras armazenadas na árvore em ordem alfabética e também o índice invertido de cada uma.
 * @param t Se trata da raiz da árvore que será impressa
 */
void ImprimeOrdemPat(TipoArvore t){
    if (t == NULL) return;

    if (Eh_ExternoPat(t)){
        imprime_indice_invertido(&t->NO.chave);
    
    } 
    else{
        ImprimeOrdemPat(t->NO.NInterno.esq);
        ImprimeOrdemPat(t->NO.NInterno.dir);
    }
}

/**
 * @brief Essa função percorre toda a árvore patrícia e conta quantos termos diferntes existem em um documento específico.
 * @param t Se trata da raiz da árvore.
 * @param idDoc É o identificador do documento que se deseja verificar a quantidade de termos distintos que ele contém.
 * @param res Uma variável auxiliar que contabiliza a quantidade de termos dstintos no doc.
 * @param NoRaiz É um ponteiro para a raiz da árvore.
 * @return Retorna a quantidade de termos distintos no doc.
 */
int PesquisaTermosDistintos(TipoArvore t, int idDoc, int * res){
    if (t == NULL) return 0;

    if (Eh_ExternoPat(t)){
        if(QuantidadeTermosPorDoc(t->NO.chave, idDoc)>0){
            (*res)++;
        }
    
    } 
    else{
        PesquisaTermosDistintos(t->NO.NInterno.esq, idDoc, res);
        PesquisaTermosDistintos(t->NO.NInterno.dir, idDoc, res);
    }
    return *res;
}
