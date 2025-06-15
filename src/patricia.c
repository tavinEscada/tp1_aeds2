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

TipoArvore Cria_NO_Externo(TipoChave palavra){ //função para inicializar um nó externo
    
    TipoArvore Novo_NO;
    Novo_NO = (TipoArvore)malloc(sizeof(NO_patricia));
    Novo_NO->tipo_no = Externo; 

    strcpy((char *)Novo_NO->NO.chave, (char *)palavra); 

    //inserir o indice invertido
    return Novo_NO;
}  

void Pesquisa(TipoChave palavra, TipoArvore NoRaiz) {

    if (Eh_Externo(NoRaiz)) {
        if (strcmp((const char*)palavra, (const char*)NoRaiz->NO.chave) == 0){
            printf("Elemento encontrado\n");
        }
        else{
            printf("Elemento nao encontrado\n");
        }
        return;
    }

    if (palavra[NoRaiz->NO.NInterno.indice] >= NoRaiz->NO.NInterno.caractere){
        Pesquisa(palavra, NoRaiz->NO.NInterno.dir);
    }
    else{
        Pesquisa(palavra, NoRaiz->NO.NInterno.esq);
    }
}

TipoArvore InsereEntre(TipoChave palavra, TipoArvore *NoAtual, int i, char caractere_interno){
  
    TipoArvore NoExt;
    if (Eh_Externo(*NoAtual) || i < (*NoAtual)->NO.NInterno.indice){
        
        NoExt = Cria_NO_Externo(palavra);
        // insere acima
        if (palavra[i] >= caractere_interno){
            return (Cria_NO_Interno(i, NoAtual, &NoExt,palavra[i])); //nova palavra a direita
        }
        else{
            return (Cria_NO_Interno(i, &NoExt, NoAtual,caractere_interno)); //nova palavra a esquerda
        }
    } 
    else{
        //busca local de inserção
        if (palavra[(*NoAtual)->NO.NInterno.indice] >= (*NoAtual)->NO.NInterno.caractere){
            (*NoAtual)->NO.NInterno.dir = InsereEntre(palavra,&(*NoAtual)->NO.NInterno.dir,i,caractere_interno);
        }
        else{
            (*NoAtual)->NO.NInterno.esq = InsereEntre(palavra,&(*NoAtual)->NO.NInterno.esq,i,caractere_interno);
        }
        return (*NoAtual);
    }
}

TipoArvore Insere(TipoChave palavra, TipoArvore *NoAtual){
  
    TipoArvore NoAux;
    int i;
    char caractere_dif;
  
    if (*NoAtual == NULL) 
        return (Cria_NO_Externo(palavra));

    else{ 
        NoAux = *NoAtual;

        while (!Eh_Externo(NoAux)){

            if (palavra[NoAux->NO.NInterno.indice] >= NoAux->NO.NInterno.caractere)
                NoAux = NoAux->NO.NInterno.dir;
            else 
                NoAux = NoAux->NO.NInterno.esq;
        }
   
        i = 0;
        while (i<= strlen((const char*)palavra) && palavra[i] == NoAux->NO.chave[i])
            i++;
    
        if (i > strlen((const char*)palavra)){
            printf("Erro: chave ja esta na arvore\n");
            return (*NoAtual); 
            //incrementar indice invertido aqui
        }
        else{
            caractere_dif=NoAux->NO.chave[i];
            //garante que o caractere em nó interno será sempre o maior
            //prefixos irão sempre para a esquerda pois \0 é menor que todos caracteres
            return InsereEntre(palavra, NoAtual, i, (palavra[i] > caractere_dif) ? palavra[i] : caractere_dif);
        }
    }
}

void ImprimeOrdem(TipoArvore t){
    if (t == NULL) return;

    if (Eh_Externo(t)){
        printf("%s\n", (char *)t->NO.chave);
    } 
    else{
        ImprimeOrdem(t->NO.NInterno.esq);
        ImprimeOrdem(t->NO.NInterno.dir);
    }
}


// int main() {

//     //main teste
//     TipoArvore x = NULL;

//     char *vetor[] = {"arvore","anel", "zoe","casamento", "casa", "ca", "casal", "cachorro", "cacto", "carro", "cavalo", "casario"};
//     int n = sizeof(vetor) / sizeof(vetor[0]);

//     for (int i = 0; i < n; i++) {
//         x = Insere((unsigned char*)vetor[i], &x);
//     }

//     ImprimeOrdem(x);
//     printf("\n");

//     for (int i = 0; i < n; i++) {
//         printf("pesquisa: %s\n", vetor[i]);
//         Pesquisa((unsigned char*)vetor[i], x);
//     }

//     return 0;
// }


