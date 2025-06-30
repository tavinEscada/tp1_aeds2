/**
 * @author Beatriz Queiroz - 5890
 * @author Heitor Porto - 5895
 * @author Pâmela Lúcia - 5898
 * @author Júlio César - 5903
 * @author Otávio Tavares - 5912
 */
#include "../include/hash.h"

TipoDicionario Tabela;
TipoItemP Elemento;
TipoPesos p;
TipoApontador i;

/**
* @brief  Verifica se a lista está vazia.
* @return Retorna 1 (verdadeiro) se estiver vazia, 0 (falso) caso cheia.
*/
short Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo); }
/**
 * @brief Inicializa uma lista vazia, alocando a célula cabeça.
*/
void FLVazia(TipoLista *Lista){
	Lista->Primeiro = (TipoCelula *)malloc(sizeof(TipoCelula));
  	Lista->Ultimo = Lista->Primeiro; 
    Lista->Primeiro->Prox = NULL;
}

/**
 * @brief Inicializa todas as listas de um dicionário hash.
*/
void Inicializa(TipoDicionario T){
	int i;
  	for (i = 0; i < M; i++) FLVazia(&T[i]);
}

/**
 * @brief Gera valores aleatórios de pesos entre 1 e 10.000
 */
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
/**
 * @brief Calcula o valor de hash para uma palavra usando hashing universal.
 *
 * @param palavra Palavra cujo hash será calculado.
 * @param p Matriz de pesos aleatórios gerados em GeraPesos
 */
TipoIndice h(Tipopalavra palavra, TipoPesos p)
{ int i; unsigned int Soma = 0;
  int comp = strlen(palavra);
  for (i = 0; i < comp; i++) Soma += p[i][(unsigned int)palavra[i]];
  return (Soma % M);
}


//imprimir em ordem alfabética
/**
 * @brief Função de comparação usada para ordenar nós da tabela hash em ordem alfabética, usada no qsort.
 */
int comparar_nos_por_palavra(const void *a, const void *b) {
    // qsort nos dá ponteiros para os elementos do nosso vetor.
    //vetor é de TipoCelula*(TipoApontador), então qsort nos dá um TipoCelula**(TipoApontador *).
    TipoApontador noA = *(const TipoApontador *)a;
    TipoApontador noB = *(const TipoApontador *)b;

    // Compara as palavras
    return strcmp(noA->Item.palavra, noB->Item.palavra);
}


/**
 * @brief Imprime o índice invertido da tabela hash em ordem alfabética das palavras.
 *
 * @param tabela Tabela hash contendo listas de palavras com seus respectivos <qtd,idDoc>.
 *
 * @details A função percorre todos os nós da tabela hash, armazena os ponteiros em um vetor, ordena esse vetor
 * alfabeticamente usando `qsort` e, em seguida, imprime os itens ordenados com base na palavra.
 */
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

/**
 * @brief Busca uma palavra em uma lista encadeada associada a uma posição da tabela hash.
 *
 * @param word Palavra a ser buscada na lista.
 * @param lista Ponteiro para a lista onde a busca será realizada.
 * @param comp_pequisa_hash Ponteiro para um inteiro que contabiliza o número de comparações realizadas.
 *
 * @return Retorna o ponteiro para o item encontrado (TipoItemP*), ou NULL se a palavra não estiver na lista.
 */
TipoItemP* Busca(Tipopalavra word, TipoLista *lista, int *comp_pequisa_hash){


    TipoApontador no_atual = lista->Primeiro->Prox;
    while (no_atual != NULL) {
		(*comp_pequisa_hash)++;
        if (strcmp(word, no_atual->Item.palavra) == 0) {
            //se a palavra for encontrada retorna o endereço do TipoItem
            return &no_atual->Item;
        }
        no_atual = no_atual->Prox;
    }
    return NULL;
}

/**
 * @brief Insere uma palavra na tabela hash, associando-a a um documento.
 *
 * @param word Palavra a ser inserida.
 * @param idDoc Identificador do documento associado à palavra.
 * @param T Tabela hash onde a palavra será inserida.
 * @param p Matriz de pesos usada na função de hash.
 * @param comp_insercao_hash Ponteiro para o contador de comparações realizadas durante a inserção.
 */
void Insere(Tipopalavra word, int idDoc, TipoDicionario T, TipoPesos p,int *comp_insercao_hash)
{ TipoIndice i;
    i = h(word, p);
    TipoLista* atalho = &T[i];
    //busca pra ver se a palavra ja existe
    TipoApontador no_atual = atalho->Primeiro->Prox;
    TipoItemP* item_encontrado = NULL;
    while (no_atual != NULL) {
        (*comp_insercao_hash)++;
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
/**
 * @brief Insere um item no final da lista encadeada.
 *
 * @param x Ponteiro para o item a ser inserido.
 * @param Lista Ponteiro para a lista onde o item será inserido.
 */
void Ins(TipoItemP *x, TipoLista *Lista){
    Lista->Ultimo->Prox = (TipoCelula *)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = *x;
    Lista->Ultimo->Prox = NULL;
}
/**
 * @brief Conta quantos termos distintos ocorrem em um documento dentro da tabela hash.
 *
 * @param tabela Estrutura da tabela hash.
 * @param idDoc Identificador do documento a ser analisado.
 * @param res Ponteiro para o acumulador do número de termos distintos encontrados.
 *
 * @return Retorna o total de termos distintos do documento.
 */
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
/**
 * @brief Realiza a busca de uma palavra na tabela hash.
 *
 * @param palavra Palavra a ser buscada.
 * @param tabela Tabela hash onde será realizada a busca.
 * @param p Matriz de pesos utilizada pela função de hashing.
 * @param comp_pequisa_hash Ponteiro para o contador de comparações realizadas durante a busca.
 *
 * @return Retorna um item contendo a palavra, ou um item vazio se não encontrada.
 */
TipoItemP pesquisa_na_hash(Tipopalavra palavra, TipoDicionario tabela, TipoPesos p, int *comp_pequisa_hash){
    int i = h(palavra,p);

    TipoItemP* item = Busca(palavra, &tabela[i],comp_pequisa_hash);
    
    if(item != NULL){
        TipoItemP aux = *item;
        return aux;
    }else{
        TipoItemP vazio;
        vazio.palavra[0]='\0';
        return vazio;   
    }
    
}