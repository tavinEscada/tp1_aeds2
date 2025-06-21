#include "../include/patricia.h"


short Eh_Externo(TipoArvore NO){ // verifica se NO é um nó externo
    return (NO->tipo_no == Externo);
}

TipoArvore Cria_NO_Interno(int i, TipoArvore *esq,  TipoArvore *dir, char caractere){ //função para inicializar um nó interno

    TipoArvore Novo_NO;
    Novo_NO = (TipoArvore)malloc(sizeof(NO_patricia));

    Novo_NO->tipo_no = Interno; 
    Novo_NO->NO.NInterno.esq = *esq;
    Novo_NO->NO.NInterno.dir = *dir;
    Novo_NO->NO.NInterno.indice = i;
    Novo_NO->NO.NInterno.caractere = caractere;

    return Novo_NO;
} 

TipoArvore Cria_NO_Externo(char* palavra,int idDoc){ //função para inicializar um nó externo
    
    TipoArvore Novo_NO;
    Novo_NO = (TipoArvore)malloc(sizeof(NO_patricia));
    Novo_NO->tipo_no = Externo; 

    // Novo_NO->NO.chave.primeiro = (Ccelula *)malloc(sizeof(Ccelula));
    // Novo_NO->NO.chave.primeiro->prox = NULL;
    faz_palavra_vazia(&Novo_NO->NO.chave,palavra);
    insere_palavra(&Novo_NO->NO.chave,idDoc);
    
    return Novo_NO;
}  

void PesquisaPat(char* palavra, TipoArvore NoRaiz) {

    TipoArvore NoAtual=NoRaiz;

    if (Eh_Externo(NoAtual)) {
        if (strcmp((const char*)palavra, (const char*)NoAtual->NO.chave.palavra) == 0){
            printf("%s aparece em %d docs\n",NoAtual->NO.chave.palavra,NoAtual->NO.chave.n_arquivos);
        }
        else{
            printf("Elemento nao encontrado\n");
        }
        return;
    }

    if (palavra[NoAtual->NO.NInterno.indice] >= NoAtual->NO.NInterno.caractere){
        PesquisaPat(palavra, NoAtual->NO.NInterno.dir);
    }
    else{
        PesquisaPat(palavra, NoAtual->NO.NInterno.esq);
    }
}

TipoArvore InsereEntrePat(char* palavra,int idDoc, TipoArvore *NoAtual, int i, char caractere_interno){
  
    TipoArvore NoExt;
    if (Eh_Externo(*NoAtual) || i < (*NoAtual)->NO.NInterno.indice){
        
        NoExt = Cria_NO_Externo(palavra,idDoc);
        // insere acima
        if (palavra[i] >= caractere_interno){
            return (Cria_NO_Interno(i, NoAtual, &NoExt,caractere_interno)); //nova palavra a direita
        }
        else{
            return (Cria_NO_Interno(i, &NoExt, NoAtual,caractere_interno)); //nova palavra a esquerda
        }
    } 
    else{
        //busca local de inserção
        if (palavra[(*NoAtual)->NO.NInterno.indice] >= (*NoAtual)->NO.NInterno.caractere){
            (*NoAtual)->NO.NInterno.dir = InsereEntrePat(palavra,idDoc,&(*NoAtual)->NO.NInterno.dir,i,caractere_interno);
        }
        else{
            (*NoAtual)->NO.NInterno.esq = InsereEntrePat(palavra,idDoc,&(*NoAtual)->NO.NInterno.esq,i,caractere_interno);
        }
        return (*NoAtual);
    }
}

TipoArvore InserePat(char* palavra, int idDoc, TipoArvore *NoRaiz){
  
    TipoArvore NoAtual;
    int i;
    char caractere_dif;
          
    if (*NoRaiz == NULL){
        return (Cria_NO_Externo(palavra,idDoc));
    }
    else{
     
        NoAtual = *NoRaiz;

        while (!Eh_Externo(NoAtual)){

            if (palavra[NoAtual->NO.NInterno.indice] >= NoAtual->NO.NInterno.caractere)
                NoAtual = NoAtual->NO.NInterno.dir;
            else 
                NoAtual = NoAtual->NO.NInterno.esq;
        }

        i = 0;
        while (i<= strlen((const char*)palavra) && palavra[i] == NoAtual->NO.chave.palavra[i])
            i++;

        if (i > strlen((const char*)palavra)){

            insere_palavra(&NoAtual->NO.chave,idDoc);
            return (*NoRaiz); 
            
        }
        else{
            caractere_dif=NoAtual->NO.chave.palavra[i];
            //garante que o caractere em nó interno será sempre o maior
            //prefixos irão sempre para a esquerda pois \0 é menor que todos caracteres
            return InsereEntrePat(palavra, idDoc, NoRaiz, i, (palavra[i] > caractere_dif) ? palavra[i] : caractere_dif);
        }
    }
}

void ImprimeOrdemPat(TipoArvore t){
    if (t == NULL) return;

    if (Eh_Externo(t)){
        imprime_indice_invertido(&t->NO.chave);
    
    } 
    else{
        ImprimeOrdemPat(t->NO.NInterno.esq);
        ImprimeOrdemPat(t->NO.NInterno.dir);
    }
}


