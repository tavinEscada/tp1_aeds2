#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include <sys/time.h>

typedef unsigned char TipoChave[255]; 

typedef struct{
    int qtde;
    int iddoc;
}par;

typedef enum{
  Interno, Externo
} TipoNo;

typedef struct NO_patricia* TipoArvore; 
typedef struct NO_patricia{
  TipoNo tipo_no;
  union{
    struct{
      char caractere;
      int indice;
      TipoArvore esq, dir;
    }NInterno;
    struct{
      TipoChave chave;
      par indinv[20]; 
      int qtdDocs;
    }NExterno;
  }NO;
}NO_patricia;

short Eh_Externo(TipoArvore NO){ 
    return (NO->tipo_no == Externo);
}

TipoArvore Cria_NO_Interno(int i, TipoArvore *esq,  TipoArvore *dir, char caractere){
    TipoArvore Novo_NO;
    Novo_NO = (TipoArvore)malloc(sizeof(NO_patricia));

    Novo_NO->tipo_no = Interno; 
    Novo_NO->NO.NInterno.esq = *esq;
    Novo_NO->NO.NInterno.dir = *dir;
    Novo_NO->NO.NInterno.indice = i;
    Novo_NO->NO.NInterno.caractere = caractere;

    return Novo_NO;
} 

TipoArvore Cria_NO_Externo(TipoChave palavra, int idDoc){
    TipoArvore Novo_NO;
    Novo_NO = (TipoArvore)malloc(sizeof(NO_patricia));
    Novo_NO->tipo_no = Externo; 

    strcpy((char *)Novo_NO->NO.NExterno.chave, (char *)palavra); 

    Novo_NO->NO.NExterno.indinv[0].iddoc = idDoc;
    Novo_NO->NO.NExterno.indinv[0].qtde = 1;
    Novo_NO->NO.NExterno.qtdDocs = 1;

    return Novo_NO;
}  

void AdicionarDocumento(TipoArvore no, int iddoc){
    if(!Eh_Externo(no)) return;
    
    //procura se o documento já existe
    for(int i = 0; i < no->NO.NExterno.qtdDocs; i++){
        if(no->NO.NExterno.indinv[i].iddoc == iddoc){
            no->NO.NExterno.indinv[i].qtde++;
            return;
        }
    }
    
    //add novo documento
    //adaptar para lista encadeada
    if(no->NO.NExterno.qtdDocs < 20){
        no->NO.NExterno.indinv[no->NO.NExterno.qtdDocs].iddoc = iddoc;
        no->NO.NExterno.indinv[no->NO.NExterno.qtdDocs].qtde = 1;
        no->NO.NExterno.qtdDocs++;
    }else{
        printf("Limite atingido para a palavra %s\n", no->NO.NExterno.chave);
    }
}

void PesquisaComIndice(TipoChave palavra, TipoArvore NoRaiz){
    TipoArvore NoAtual = NoRaiz;

    if(NoRaiz == NULL){
        printf("Palavra '%s' não encontrada (árvore vazia)\n", palavra);
        return;
    }

    //chegar no nó externo
    while(!Eh_Externo(NoAtual)){

        int len_palavra = strlen((const char*)palavra);
        char char_palavra = (NoAtual->NO.NInterno.indice < len_palavra) ? palavra[NoAtual->NO.NInterno.indice] : '\0';
        
        if(char_palavra >= NoAtual->NO.NInterno.caractere){
            NoAtual = NoAtual->NO.NInterno.dir;
        }else{
            NoAtual = NoAtual->NO.NInterno.esq;
        }
    }

    //ver se a palavra foi encontrada
    if(strcmp((const char*)palavra, (const char*)NoAtual->NO.NExterno.chave) == 0){
        printf("Palavra '%s' encontrada nos documentos:\n", palavra);
        for(int i = 0; i < NoAtual->NO.NExterno.qtdDocs; i++){
            printf("doc %d: %d vezes\n", NoAtual->NO.NExterno.indinv[i].iddoc, NoAtual->NO.NExterno.indinv[i].qtde);
        }
    }else{
        printf("palavra %s nao encontrada\n",palavra);
    }
}

TipoArvore InsereEntrePat(TipoChave palavra, TipoArvore *NoAtual, int i, char caractere_interno, int idDoc){
    TipoArvore NoExt;
    
    if (Eh_Externo(*NoAtual) || i < (*NoAtual)->NO.NInterno.indice){
        NoExt = Cria_NO_Externo(palavra, idDoc);

        int len_palavra = strlen((const char*)palavra);
        char char_palavra = (i < len_palavra) ? palavra[i] : '\0';
        
        if (char_palavra >= caractere_interno){
            return (Cria_NO_Interno(i, NoAtual, &NoExt, caractere_interno));
        }
        else{
            return (Cria_NO_Interno(i, &NoExt, NoAtual, caractere_interno));
        }
    } 
    else{
        int len_palavra = strlen((const char*)palavra);
        char char_palavra = ((*NoAtual)->NO.NInterno.indice < len_palavra) ? 
                           palavra[(*NoAtual)->NO.NInterno.indice] : '\0';
        
        if (char_palavra >= (*NoAtual)->NO.NInterno.caractere){
            (*NoAtual)->NO.NInterno.dir = InsereEntrePat(palavra, &(*NoAtual)->NO.NInterno.dir, i, caractere_interno, idDoc);
        }
        else{
            (*NoAtual)->NO.NInterno.esq = InsereEntrePat(palavra, &(*NoAtual)->NO.NInterno.esq, i, caractere_interno, idDoc);
        }
        return (*NoAtual);
    }
}

TipoArvore InserePat(TipoChave palavra, TipoArvore *NoRaiz, int id){
    TipoArvore NoAtual;
    unsigned int i;
    char caractere_dif;
  
    if (*NoRaiz == NULL) 
        return (Cria_NO_Externo(palavra, id));

    NoAtual = *NoRaiz;

    while (!Eh_Externo(NoAtual)){
        if (palavra[NoAtual->NO.NInterno.indice] >= NoAtual->NO.NInterno.caractere)
            NoAtual = NoAtual->NO.NInterno.dir;
        else 
            NoAtual = NoAtual->NO.NInterno.esq;
    }

    i = 0;
    
    int len_palavra = strlen((const char*)palavra);
    int len_chave = strlen((const char*)NoAtual->NO.NExterno.chave);
    
    while (i < len_palavra && i < len_chave && palavra[i] == NoAtual->NO.NExterno.chave[i])
        i++;

    if (i == len_palavra && i == len_chave){
        AdicionarDocumento(NoAtual, id);
        return (*NoRaiz);
    }
    else{
        
        caractere_dif = (i < len_chave) ? NoAtual->NO.NExterno.chave[i] : '\0';
        //garante que o caractere em nó interno será sempre o maior
        //prefixos irão sempre para a esquerda pois \0 é menor que todos caracteres
        return InsereEntrePat(palavra, NoRaiz, i, caractere_dif, id);
    }
}

void ImprimeOrdemPat(TipoArvore t){
    if (t == NULL) return;

    if (Eh_Externo(t)){
        printf("Palavra: %s\n", (char *)t->NO.NExterno.chave);
        printf("Aparece em %d documentos:\n", t->NO.NExterno.qtdDocs);

        for (int i = 0; i < t->NO.NExterno.qtdDocs; i++) {
            printf("Doc %d: %d vezes\n", 
                   t->NO.NExterno.indinv[i].iddoc,
                   t->NO.NExterno.indinv[i].qtde);
        }
        printf("\n");
    } 
    else{
        ImprimeOrdemPat(t->NO.NInterno.esq);
        ImprimeOrdemPat(t->NO.NInterno.dir);
    }
}

int main(){
    TipoArvore x = NULL;
    
    char *doc1[] = {
        "abacate", "abelha", "abismo", "abrir", "absoluto", "academia", "acender", "acordo", "adesivo"};
    char *doc2[] = {
        "abacate", "fodase", "desgraca", "caralho"};
    
    printf("Inserindo palavras do doc 1:\n");
    for(int i = 0; i < 9; i++){
        printf("%s\n", doc1[i]);
        x = InserePat((unsigned char*)doc1[i], &x, 1);
    }

    printf("\nInserindo palavras do doc 2:\n");
    for(int i = 0; i < 4; i++){
        printf("%s\n", doc2[i]);
        x = InserePat((unsigned char*)doc2[i], &x, 2);
    }

    printf("\nindice Invertido Completo\n");
    ImprimeOrdemPat(x);
    
    printf("pesquisando...\n");
    PesquisaComIndice((unsigned char*)"abacate", x);
    printf("\n");
    PesquisaComIndice((unsigned char*)"abelha", x);
    printf("\n");
    PesquisaComIndice((unsigned char*)"paia", x);

    return 0;
}