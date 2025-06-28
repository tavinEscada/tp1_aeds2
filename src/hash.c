#include "../include/hash.h"

TipoDicionario Tabela;
TipoItemP Elemento;
TipoPesos p;
TipoApontador i;
extern unsigned long long int comp_insercao_hash;
extern unsigned long long int comp_busca_hash;

short Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo); }

void FLVazia(TipoLista *Lista){
	Lista->Primeiro = (TipoCelula *)malloc(sizeof(TipoCelula));
  	Lista->Ultimo = Lista->Primeiro; 
    Lista->Primeiro->Prox = NULL;
}
void Inicializa(TipoDicionario T){
	int i;
  	for (i = 0; i < M; i++) FLVazia(&T[i]);
}

void GeraPesos(TipoPesos p)
{ /* Gera valores randomicos entre 1 e 10.000 */
  int i, j;
  struct timeval semente;
  /* Utilizar o tempo como semente para a funcao srand() */
  gettimeofday(&semente, NULL);
  srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
  for (i = 0; i < N; i++)
    for (j = 0; j < TAMALFABETO; j++)
      p[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
}

TipoIndice h(Tipopalavra palavra, TipoPesos p)
{ int i; unsigned int Soma = 0;
  int comp = strlen(palavra);
  for (i = 0; i < comp; i++) Soma += p[i][(unsigned int)palavra[i]];
  return (Soma % M);
}


//imprimir em ordem alfabética

int comparar_nos_por_palavra(const void *a, const void *b) {
    // qsort nos dá ponteiros para os elementos do nosso vetor.
    //vetor é de TipoCelula*(TipoApontador), então qsort nos dá um TipoCelula**(TipoApontador *).
    TipoApontador noA = *(const TipoApontador *)a;
    TipoApontador noB = *(const TipoApontador *)b;

    // Compara as palavras
    return strcmp(noA->Item.palavra, noB->Item.palavra);
}



void Imprimir(TipoDicionario tabela) {
    if (tabela == NULL) {
        printf("Dicionário não inicializado.\n");
        return;
    }

    // contar o numero total de nós na tabela
    int n = 0;
    for (int i = 0; i < M; i++) {
        for (TipoApontador no = tabela[i].Primeiro->Prox; no != NULL; no = no->Prox) {
            n++;
        }
    }

    if (n == 0) {
        printf("Dicionário está vazio.\n");
        return;
    }

    // vetor de ponteiros criado para os nós (TipoCelula*)
	//aqui como eu preciso guarda nao somente uma palavra mas o seu indice tbm
	//eu aloco um vetor de pnteiros que aponta cada tipo celula da tabela
    TipoApontador *vetor_de_nos = malloc(n * sizeof(TipoApontador));
    if (vetor_de_nos == NULL) {
        printf("Erro de alocação de memória!\n");
        return;
    }

    //Preencher o vetor
    int k = 0;
    for (int i = 0; i < M; i++) {
        for (TipoApontador no = tabela[i].Primeiro->Prox; no != NULL; no = no->Prox) {
            vetor_de_nos[k++] = no;
        }
    }

    //de quicksort qsort(vetor a ser ordenado,n de elementos,tam de um elemento do vetor,o comparador)
    qsort(vetor_de_nos, n, sizeof(TipoCelula *), comparar_nos_por_palavra);


    printf("--- Indice Invertido da Hash ---\n");
    for (int i = 0; i < n; i++) {
        // Pega o nó da posição ordenada
        TipoCelula *no_ordenado = vetor_de_nos[i];
        // Chama a função de impressão para o item daquele nó
        imprime_indice_invertido(&no_ordenado->Item);
    }


    free(vetor_de_nos);
}


TipoItemP* Busca(Tipopalavra word, TipoLista *lista){


    TipoApontador no_atual = lista->Primeiro->Prox;
    while (no_atual != NULL) {
		comp_busca_hash++;
        if (strcmp(word, no_atual->Item.palavra) == 0) {
            //se a palavra for encontrada retorna o endereço do TipoItem
            return &no_atual->Item;
        }
        no_atual = no_atual->Prox;
    }
    return NULL;
}


void Insere(Tipopalavra word, int idDoc, TipoDicionario T, TipoPesos p)
{ TipoIndice i;
    i = h(word, p);
    TipoLista* atalho = &T[i];
    //busca pra ver se a palavra ja existe
    TipoApontador no_atual = atalho->Primeiro->Prox;
    TipoItemP* item_encontrado = NULL;
    while (no_atual != NULL) {
        comp_insercao_hash++;
        if (strcmp(word, no_atual->Item.palavra) == 0) {
            item_encontrado = &no_atual->Item;
            break;
        }
        no_atual = no_atual->Prox;
    }
    if (item_encontrado != NULL) {
        insere_palavra(item_encontrado, idDoc);
    }
    else{
        TipoItemP item_inserir;
        faz_palavra_vazia(&item_inserir, word);
        insere_palavra(&item_inserir, idDoc);
        Ins(&item_inserir, atalho);
    }
}
//passa por ponteiro para nao precisar copiar toda a struct
void Ins(TipoItemP *x, TipoLista *Lista){
    Lista->Ultimo->Prox = (TipoCelula *)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = *x;
    Lista->Ultimo->Prox = NULL;
}
void comparacoes(){
	printf("--- Relatorio de Comparacoes ---\n");
    printf("HASH - Comparacoes na Insercao: %llu\n", comp_insercao_hash);
    printf("HASH - Comparacoes na Busca: %llu\n", comp_busca_hash);
    printf("--------------------------------\n");
    // Zere os contadores para a próxima rodada de testes
    comp_insercao_hash = 0;
    comp_busca_hash = 0;
}

int termos_distintos_hash(TipoDicionario tabela, int idDoc, int * res){

    for(int i = 0; i < M; i++){//percorre o vetor da tabela

        for (TipoApontador no = tabela[i].Primeiro->Prox; no != NULL; no = no->Prox) { //percorre a lista encadeada
            
            if(QuantidadeTermosPorDoc(no->Item,idDoc)>0){ //se a palavra ta do documento procurado
                (*res)++;
            }
        }
    }

    return *res;
}

TipoItemP pesquisa_na_hash(Tipopalavra palavra, TipoDicionario tabela, TipoPesos p){
    int i = h(palavra,p);

    TipoItemP* item = Busca(palavra, &tabela[i]);
    
    if(item != NULL){
        TipoItemP aux = *item;
        return aux;
    }else{
        TipoItemP vazio;
        vazio.palavra[0]='\0';
        return vazio;   
    }
    
}