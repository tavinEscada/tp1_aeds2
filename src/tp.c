/**
 * @author Beatriz Queiroz - 5890
 * @author Heitor Porto - 5895
 * @author Pâmela Lúcia - 5898
 * @author Júlio César - 5903
 * @author Otávio Tavares - 5912
 */

#include "../include/tp.h"
/**
 * Dada uma palavra, substitui 
 * caracteres especiais (letras com acentos e cedilha) 
 * por minúsculas sem acento (especificamente para utf-8 - 
 * leitura dos arquivos e terminal linux)
 * 
 * @param p vetor de caracteres com a palavra que será adaptada
 * 
 */
void removeAcentos(char *p){
    int j = 0;
    
    for(int i = 0; p[i];){

        char sub = 0;

        //UTF-8 pra acentos e tal no alfabeto latino (basic latin)
        //com 0xC3 sendo prefixo para elementos fora dos ascii normais 
        //(C3 + A1 -> 'á', por exemplo, com 0x na frente para indicar hex)
        if((unsigned char)p[i] == 0xC3){
              
            unsigned char proxC = (unsigned char)p[i+1];

            //á à ã â ä , o mesmo pro maiusculo com acentos
            if(proxC == 0xA1 || proxC == 0xA0 || proxC == 0xA3 || proxC == 0xA2 
                || proxC == 0x81 || proxC == 0x80 || proxC == 0x83 || proxC == 0x82
                || proxC == 0x84 || proxC == 0xA4){
                sub = 'a';
            }

            //é ê è ë, o mesmo pros maiusculos
            if(proxC == 0xA9 || proxC == 0xAA || proxC == 0x89 || proxC == 0x8A
                || proxC == 0x88 || proxC == 0x8B || proxC == 0xA8 || proxC == 0xAB){
                sub = 'e';
            }

            //í Í ì î ï...
            if(proxC == 0xAD || proxC == 0x8D || proxC == 0xAE 
                || proxC == 0xAF || proxC == 0xAC || proxC == 0x8C 
                || proxC == 0x8E || proxC == 0x8F){
                sub = 'i';
            }

            //ó ò ô õ Ö...
            if(proxC == 0xB3 || proxC == 0xB2 || proxC == 0xB4 || proxC == 0xB5 
                || proxC == 0x93 || proxC == 0x92 || proxC == 0x94 || proxC == 0x95
                || proxC == 0xB6 || proxC == 0x96){
                sub = 'o';
            }

            //ú ù û...
            if(proxC == 0xBA || proxC == 0xB9 || proxC == 0xBB || proxC == 0x9A 
                || proxC == 0x99 || proxC == 0x9B || proxC == 0x9C || proxC == 0xBC){
                sub = 'u';
            }

            //ç Ç
            if(proxC == 0xA7 || proxC == 0x87){
                sub = 'c';
            }

            if(proxC == 0x91 || proxC == 0xB1){
                sub = 'n';
            }

            if(sub){
                //alterando o caractere
                p[j] = sub;
                j++;
            }
            
            
            //pular os 2 bytes do trem ai, o atual e o verificado acima
            i += 2;
        }else{
            
            p[j] = p[i];
            
            i++;
            j++;
            
        }
    }
    //acabou a palavra com o fim do for
    p[j] = '\0';
}

/**
 * Dada uma palavra, substitui 
 * caracteres especiais (letras com acentos e cedilha) 
 * por minúsculas sem acento (especificamente para CP850 - terminal windows)
 * 
 * @param p vetor de caracteres com a palavra que será adaptada
 * 
 */
void removeAcentosTerminal(char *p){
    for(int i = 0; p[i]; i++){
        char sub = 0;
        unsigned char c = (unsigned char)p[i];
        if(c == 0xA0 || c == 0x85 || c == 0x83 || c == 0xC6 || //á à â ã
            c == 0xB5 || c == 0xB7 || c == 0xB6 || c == 0xC7 //Á À Â Ã
            || c == 0x84 || c == 0x8E){ 
            sub = 'a';
            
        }
        if(c == 0x82 || c == 0x88 || c == 0x90 || c == 0xD2 //é ê É Ê
            || c == 0x89 || c == 0x8A || c == 0xD4 || c == 0xD3){
            sub = 'e';
        }
        if(c == 0xA1 || c == 0xD6 || c == 0xD7 || c == 0xD8 
            || c == 0xDE || c == 0x8B || c == 0x8C){ //í Í
            sub = 'i';
        }
        if(c == 0xA2 || c == 0x93 || c == 0x94 || c == 0x99 || c == 0xE4 
            || c == 0xE0 || c == 0xE5 || c == 0xE2){ // ó ô õ Ó Õ Ô
            sub = 'o';
        }
        if(c == 0xA6 || c == 0xA7 || c == 0xA8 || c == 0xE9 || c == 0xEB 
            || c == 0xEA || c == 0x96 || c == 0x9A || c == 0x97 || c == 0xEA 
            || c == 0xEB){ // ú ù û Ú Ù Û
            sub = 'u';
        }
        if(c == 0x87 || c == 0x80){ //ç e Ç
            sub = 'c';
        }
        if(c == 0xA5 || c == 0xA4){
            sub = 'n';
        }
        
        if(sub){
            p[i] = sub;
        }
    }

}

/**
 * Dada uma palavra, substitui letras maiúsculas por minúsculas
 * 
 * @param p vetor de caracteres com a palavra que será adaptada
 * 
 */
void removeMaiusculas(char *p){
    for(int i = 0; p[i]; i++){
        char sub = 0;
        switch(p[i]){
            
            case 'A':
                sub = 'a';
                break;
            case 'B':
                sub = 'b';
                break;
            case 'C':
                sub = 'c';
                break;
            case 'D':
                sub = 'd';
                break;
            case 'E':
                sub = 'e';
                break;
            case 'F':
                sub = 'f';
                break;
            case 'G':
                sub = 'g';
                break;
            case 'H':
                sub = 'h';
                break;
            case 'I':
                sub = 'i';
                break;
            case 'J':
                sub = 'j';
                break;
            case 'K':
                sub = 'k';
                break;
            case 'L':
                sub = 'l';
                break;
            case 'M':
                sub = 'm';
                break;
            case 'N':
                sub = 'n';
                break;
            case 'O':
                sub = 'o';
                break;
            case 'P':
                sub = 'p';
                break;
            case 'Q':
                sub = 'q';
                break;
            case 'R':
                sub = 'r';
                break;
            case 'S':
                sub = 's';
                break;
            case 'T':
                sub = 't';
                break;
            case 'U':
                sub = 'u';
                break;
            case 'V':
                sub = 'v';
                break;
            case 'W':
                sub = 'w';
                break;
            case 'X':
                sub = 'x';
                break;
            case 'Y':
                sub = 'y';
                break;
            case 'Z':
                sub = 'z';
                break;

            default:
                break;
                
        }
        if(sub){
            p[i] = sub;
        }
    }
}

/**
 * Dada uma palavra, confere se ela é relevante; tiramos algumas que não precisam ser levadas em conta
 * 
 * @param p vetor de caracteres com a palavra que será analisada
 * 
 */
int ehRelevante(char *p){
    char *irrelevantes[] = {"isso", "uma", "com", "por", "the", "sua", "elas", "that", "not",
        "seu", "como", "nao", "que", "para", "dos", "ela", "ele", "nem", "eles", "this", "are",
        "das", "mas", "desse", "dessa", "esta", "esse", "essa", "desta", "tem", "for", "and",
        "with", "such", "but"
    };

    int n = sizeof(irrelevantes)/sizeof(irrelevantes[0]);

    for(int i = 0; i < n; i++){
        if(strcmp(p, irrelevantes[i]) == 0){
            return 0;
        }
    }
    return 1;

}

/**
 * Analisando palavras que talvez não devam ser levadas em conta (palavras de uma letra só,
 * palavras de duas letras que não sejam siglas, palavras com caracteres especiais...)
 * 
 * @param p vetor de caracteres com a palavra que será adaptada
 * @return 0 se não é valida, 1 se é
 */
int ehValida(char *p){

    removeAcentos(p);

    int t = strlen(p);

    //caracteres especiais que possam ter sobrado (como '20%')
    for(int j = 0; j < t; j++){
        if(!isalpha(p[j])){
            return 0;
        }
    }

    if(t < 3){

        //uma letra só
        if(t == 1){
            return 0;
        }

        //duas letras, mas não é sigla
        for(int i = 0; i < t; i++){
            if(islower(p[i])){
                return 0;
            }
        }
    }

    removeMaiusculas(p);

    if(!ehRelevante(p)){
        return 0;
    }

    return 1;
    
}

/**
 * Removendo arquivos que possam ter sobrado da execução anterior e que nao devem
 * ser considerados nessa
 * 
 * @param nArqAtual ultimo id obtido na execução; a partir dele, removeremos os remanescentes
 * 
 */
void removerArqs(int nArqAtual) {
    char nomeArquivo[TMAX];
    
    //começa do próximo arquivo após o último lido
    for(int i = nArqAtual + 1; ; i++){
        //monta o nome do arquivo a ser removido
        snprintf(nomeArquivo, sizeof(nomeArquivo), "./arquivosTratados/arquivo%d.txt", i);
        
        //testa se o arquivo existe
        FILE *teste = fopen(nomeArquivo, "r");
        if(teste == NULL){
            //não existe
            break;
        }
        
        fclose(teste);
        
        if(remove(nomeArquivo) == 0){
            //printf("Arquivo remanescente removido: arquivo%d.txt\n", i);
        }else{
            printf("Erro ao remover arquivo%d.txt\n", i);
        }
    }
}

/**
 * Dada uma palavra, substitui 
 * caracteres especiais (letras com acentos e cedilha) 
 * por minúsculas sem acento (especificamente para utf-8)
 * 
 * @param p vetor de caracteres com a palavra que será adaptada
 * @return informações básicas da execução, como numero de arquivos, 
 * matriz com o nome original dos arquivos e int sucesso: 1 se a leitura 
 * for feita corretamente, 0 se algo der errado (ao abrir algum arquivo, por ex)
 */
InfoBasica receberArquivo(){
    InfoBasica info = {0};
    char nome[256];
    int nArq = 0;

    printf("Nome do arquivo:\n");
    scanf("%s", nome);

    FILE *arq = fopen(nome, "r");

    if(arq == NULL){
        printf("Erro ao abrir o arquivo\n");
        info.sucesso = 0;
        return info;
    }

    fscanf(arq, "%d", &nArq);
    fgets(nome, sizeof(nome), arq);

    if(nArq <= 0){
        printf("N de arquivos invalido\n");
        info.sucesso = 0;
        return info;
    }
    
    //numero de arquivos da execucao
    info.nArquivos = nArq;

    //criando a pasta que armazenará os arquivos com as palavras já separadas e formatadas
    mkdir("./arquivosTratados");

    //prefixos; caminho dos pocs da entrada e dos arquivos auxiliares a serem criados
    char cEntrada[8] = "./pocs/";
    char cSaida[21] = "./arquivosTratados/";


    for(int i = 1; i <= nArq; i++){

        fgets(nome, 256, arq);

        //remover possíveis '\r' (do linux) e '\n' no final das palavras e trocar por '\0' (fim da palavra)
        nome[strcspn(nome, "\r\n")] = '\0';

        char entrada[TMAX];
        char saida[TMAX];

        //juntando o prefixo do endereço dos arquivos ('.\pocs') com o nome de cada arquivo
        snprintf(entrada, TMAX, "%s%s", cEntrada, nome);

        //juntando o prefixo do endereco da saida ('./arquivosTratados')
        snprintf(saida, TMAX, "%sarquivo%d.txt", cSaida, i);

        FILE *arquivoAtual = fopen(entrada, "r");
        
        if(arquivoAtual == NULL){
            printf("Erro ao abrir o poc '%s'. Confira o nome dos pocs da entrada.\n", nome);
            info.sucesso = 0;
            return info;
        }

        //a cada arquivo lido, preenchemos uma linha da matriz de nomes
        strcpy(info.nomesOriginais[i-1], nome);
        
        FILE *saidaAtual = fopen(saida, "w");
        if(saidaAtual == NULL){
            printf("erro ao criar o arquivo de saida %d\n\n", i);
            continue;
        }

        char linha[256];

        while(fgets(linha, sizeof(linha), arquivoAtual) != NULL){
            //tokenizando cada linha
            linha[strcspn(linha, "\n")] = '\0';

            //pegando a primeira palavra da linha
            char *palavra = strtok(linha, " .,:;()\"'-/?\r\n");

            while(palavra != NULL){

                //depois das verificações, pegando apenas as palavra válidas
                if(ehValida(palavra)){

                    //escrevendo cada palavra em cada arquivo auxiliar
                    fprintf(saidaAtual, "%s\n", palavra);
                }
                
                //passando para a próxima palavra da linha
                palavra = strtok(NULL, " .,:;()\"'-/?\r\n");
            }
            
        }
        
        fclose(arquivoAtual);
        fclose(saidaAtual);

    }
    //removendo arquivos que possam ter sobrado da última execução
    removerArqs(nArq);

    fclose(arq);

    //deu tudo certo na leitura
    info.sucesso = 1;
    return info;
}

/**
 * Juntando a pesquisa da hash e da patricia para serem executadas em sequencia
 * 
 */
void pesquisa_geral(InfoBasica info, TipoArvore raiz, TipoDicionario tabela, TipoPesos p,int* comp_pesquisa_pat, int *comp_pequisa_hash){

    printf("\n----------- Hash -------------\n");
    pesquisa_hash(tabela, info, p, comp_pequisa_hash);
    printf("\n--------- Patricia -----------\n");
    pesquisa(info, raiz,comp_pesquisa_pat);
    
    
}

/**
 * Construindo os índices invertidos das estruturas a partir dos arquivos auxiliares
 * 
 * @param patricia árvore para inserção
 * @param comp_insercao_pat variavel de controle do n de comparações ao constuir a patricia
 * @param comp_insercao_hash variavel de controle do n de comparacoes ao construir a hash
 * 
 */
void constroiIndices(TipoArvore *patricia, int* comp_insercao_pat,int *comp_insercao_hash){
    char enderecoTextos[50] = "./arquivosTratados/";
    char nomeCompleto[TMAX];

    //abrindo os arquivos auxiliares para inserir as palavras
    snprintf(nomeCompleto, TMAX, "%s%s%d%s", enderecoTextos, "arquivo", 1, ".txt");
    FILE *arqAtual = fopen(nomeCompleto, "r");

    char palavra[200];

    Inicializa(Tabela);
    GeraPesos(p);   
    
    for(int i = 1; arqAtual;){
        char nNome[40];
        while(fgets(palavra, sizeof(palavra), arqAtual) != NULL){

            //obtendo e inserindo palavra por palavra nas estruturas

            palavra[strcspn(palavra, "\n")] = '\0';
            Insere(palavra, i, Tabela, p, comp_insercao_hash);


            (*patricia) = InserePat(palavra, i, patricia, comp_insercao_pat);
            
        }
        i++;
        //partindo para o próximo arquivo, caso exista
        snprintf(nNome, TMAX, "%s%s%d%s", enderecoTextos, "arquivo", i, ".txt");
        arqAtual = fopen(nNome, "r");

    }
}


void imprimeIndices(TipoArvore patricia){
    
    Imprimir(Tabela);

    printf("\n--- Indice Invertido da Patricia ---\n");
    ImprimeOrdemPat(patricia);

}

//função a ser usada no qsort das relevâncias da pesquisa
int comparaRel(const void *a, const void *b) {
    
    Relevancias noA = *(const Relevancias *)a;
    Relevancias noB = *(const Relevancias *)b;

    // Compara as relevancias
    if(noA.relevancia < noB.relevancia){
        return 1;
    }
    if(noA.relevancia > noB.relevancia){
        return -1;
    }
    return 0;
}

/**
 * @brief Essa função calcula a relevância dos documentos para a pesquisa a partir da patricia.
 * @param TipoArvore raiz ponteiro para raiz da árvore Patrícia.
 * @param char **input termos a serem pesquisados.
 * @param Relevancias *doc informações sobre a coleção de documentos.
 * @param int nDOCS quantidade de documentos.
 * @param int nTermos quantidade de termos a serem pesquisados.
 * @param int* comp_pesquisa_pat ponteiro para o número de comparções.
 */
void tfidfpat(TipoArvore raiz, char **input, Relevancias *doc, int nDOCS, int nTermos,int* comp_pesquisa_pat){

    for(int i = 0; i < nDOCS; i++){
        int total = 0;
        int termosDistintos = PesquisaTermosDistintos(raiz, doc[i].id, &total);
        
        //laço para o documento e outro para as palavras????
        doc[i].relevancia = (1.0/termosDistintos) * sumPtermoPat(raiz, nDOCS, input, nTermos, doc[i].id,comp_pesquisa_pat);
        
    }

}

/**
 * @brief Calcula a relevância TF-IDF de cada documento com base nos termos da pesquisa na Patrícia.
 * @param TipoArvore raiz ponteiro para raiz da árvore Patrícia.
 * @param int nDOCS quantidade de documentos.
 * @param char **input termos a serem pesquisados.
 * @param int nTermos quantidade de termos a serem pesquisados.
 * @param int idDoc identificador do documento i.
 * @param int* comp_pesquisa_pat ponteiro para o número de comparções.
 * @return Retorna a somatória do peso de cada termo para o documento i.
 */
float sumPtermoPat(TipoArvore raiz, int nDOCS, char **input, int nTermos, int idDoc,int* comp_pesquisa_pat){
    float res = 0;
    
    for (int i = 0; i < nTermos; i++){
        
        TipoItemP item = PesquisaPat(input[i], raiz,comp_pesquisa_pat);
        if (strcmp(item.palavra,"\0") != 0){
        
            int dj = item.n_arquivos;
            int ocorrenciaT = QuantidadeTermosPorDoc(item, idDoc);
            if(ocorrenciaT > 0 && dj > 0){
                res += ocorrenciaT * ((log(nDOCS) / log(2.0))/dj);
            }
        }

    }
    return res;
}

/**
 * pesquisa da patricia
 * 
 * @param info informacoes necessarias (matriz com os nomes originais dos arquivos)
 * @param raiz raiz da patricia a ser percorrida
 * @param comp_pesquisa_pat controle de comparações usadas na pesquisa da patricia
 */
void pesquisa(InfoBasica info, TipoArvore raiz, int*comp_pesquisa_pat){
    //linha de entrada
    char entrada[900];
    
    //variavel que armazenará palavra por palavra
    char *palavra;
    
    printf("Palavras da pesquisa:\n");
    char **strings;
    strings = (char**)malloc(300 * sizeof(char*));

    //numero de palavras da pesquisa
    int nTermos = 0;
    
    if(fgets(entrada, sizeof(entrada), stdin) != NULL){
        //remove \n do final
        entrada[strcspn(entrada, "\n\r")] = '\0';

        if(strlen(entrada) > 0){
            palavra = strtok(entrada, " ");
            int a = 0;
            while(palavra != NULL){

                //terminal do windows
                if(sistema == 1){
                    //tirar acentos para o terminal do vscode
                    removeAcentosTerminal(palavra);
                }else{
                    //tirar os acentos pra rodar no terminal do linux
                    removeAcentos(palavra);
                }
                
                removeMaiusculas(palavra);
                
                //adicionando as palavras da pesquisa a um vetor
                strings[a] = (char*)malloc((strlen(palavra)+1) * sizeof(char));
                strcpy(strings[a], palavra);

                //numero de termos da pesquisa
                nTermos++;

                //proxima posicao para insercao no vetor
                a++;

                //pegando a proxima palavra
                palavra = strtok(NULL, " ");
            }
        }
    }

    int nArquivos = getNumeroArquivos(&info);

    //vetor dinamico para armazenar as relevancias; o indice do vetor é id-1
    Relevancias *vet = malloc(nArquivos * sizeof(Relevancias));

    //inicializando os documentos no vetor
    for(int i = 1; i <= nArquivos; i++){
        vet[i-1].id = i;
        vet[i-1].relevancia = 0.0;
    }
    
    tfidfpat(raiz, strings, vet, nArquivos, nTermos, comp_pesquisa_pat);

    //ordenação do vetor a partir da relevancia para printar na ordem
    qsort(vet, nArquivos, sizeof(Relevancias), comparaRel);

    int nResult = 0;
    for(int i = 1; i <= nArquivos; i++){
        if(vet[i-1].relevancia > 0.0000){
            printf("'%s' (arquivo%d.txt): relev.: %.3f\n", getNomeOriginal(&info, vet[i-1].id), vet[i-1].id, vet[i-1].relevancia);
            nResult++;
        }else{
            break;
        }
        
    }
    if(nResult == 0){
        printf("Nenhum documento corresponde a pesquisa\n");
    }

    for(int i = 0; i < nTermos; i++){
        free(strings[i]);
    }

    free(vet);
    free(strings);
}
//////////////HASH/////////////////////

/**
 * @brief Calcula a relevância TF-IDF de cada documento com base nos termos da pesquisa na Hash.
 *
 * @param tabela Tabela hash contendo os termos indexados.
 * @param input Vetor de strings contendo as palavras da pesquisa.
 * @param doc Vetor de estruturas que armazenam a relevância e o ID dos documentos.
 * @param nDOCS Número total de documentos.
 * @param nTermos Número de termos inseridos na pesquisa.
 * @param p Matriz de pesos para hashing.
 * @param comp_pequisa_hash Ponteiro para o contador de comparações realizadas nas buscas.
 */
void tfidfhash(TipoDicionario tabela, char **input, Relevancias *doc, int nDOCS, int nTermos, TipoPesos p, int *comp_pequisa_hash){

    for(int i = 0; i < nDOCS; i++){

        int total = 0;
        int termosDistintos = termos_distintos_hash(tabela,doc[i].id, &total); 
        
        doc[i].relevancia = (1.0/termosDistintos) * sumPtermoHash(tabela, nDOCS, input, nTermos, doc[i].id,p, comp_pequisa_hash);

    }

}
/**
 * @brief Calcula a soma ponderada TF-IDF dos termos da pesquisa em um documento específico.
 *
 * @param tabela Tabela hash contendo os termos.
 * @param nDOCS Número total de documentos.
 * @param input Vetor com as palavras da pesquisa.
 * @param nTermos Quantidade de termos na pesquisa.
 * @param idDoc ID do documento para o qual a soma será calculada.
 * @param p Matriz de pesos para hashing.
 * @param comp_pequisa_hash Ponteiro para o contador de comparações realizadas nas buscas.
 *
 * @return Soma TF-IDF dos termos presentes no documento.
 */
float sumPtermoHash(TipoDicionario tabela, int nDOCS, char **input, int nTermos, int idDoc, TipoPesos p, int *comp_pequisa_hash){
    float res = 0;
    for (int i = 0; i < nTermos; i++){
        TipoItemP item = pesquisa_na_hash(input[i], tabela, p, comp_pequisa_hash); //PesquisaPat(input[i], raiz);
        
        if (strcmp(item.palavra,"\0") != 0){
         
            int dj = item.n_arquivos;
            int ocorrenciaT = QuantidadeTermosPorDoc(item, idDoc);
            if(ocorrenciaT > 0 && dj > 0){

                res += ocorrenciaT * ((log(nDOCS) / log(2.0))/dj);
            }
        }   


    }
    return res;
}

/**
 * @brief Processa a entrada do usuário, calcula a relevância TF-IDF de cada documento e imprime os resultados ordenados.
 *
 * @param tabela Tabela hash com o índice invertido.
 * @param info Estrutura com informações básicas sobre os documentos.
 * @param p Matriz de pesos usada para calcular os hashes.
 * @param comp_pequisa_hash Ponteiro para o contador de comparações realizadas nas buscas.
 */
void pesquisa_hash(TipoDicionario tabela, InfoBasica info, TipoPesos p, int *comp_pequisa_hash){
    //linha de entrada
    char entrada[900];

    //variavel que armazenará palavra por palavra
    char *palavra;

    printf("Palavras da pesquisa:\n");

    getchar();

    //lista encadeada de palavras
    char **strings;
    strings = (char**)malloc(300 * sizeof(char*));

    //numero de palavras da pesquisa
    int nTermos = 0;

    if(fgets(entrada, sizeof(entrada), stdin) != NULL){
        //remove \n do final
        entrada[strcspn(entrada, "\n\r")] = '\0';

        if(strlen(entrada) > 0){
            palavra = strtok(entrada, " ");
            int a = 0;
            while(palavra != NULL){

                //terminal do windows
                if(sistema == 1){
                    //tirar acentos para o terminal do vscode
                    removeAcentosTerminal(palavra);
                }else{
                    //tirar os acentos pra rodar no terminal do linux
                    removeAcentos(palavra);
                }

                //teste para saber qual codificação dos caracteres
                /*for(int i = 0; palavra[i]; i++){
                    printf("%02X ", (unsigned char)palavra[i]);
                }
                printf("\n");
                */

                removeMaiusculas(palavra);

                strings[a] = (char*)malloc((strlen(palavra)+1) * sizeof(char));
                strcpy(strings[a], palavra);

                nTermos++;
                a++;

                palavra = strtok(NULL, " ");
            }
        }
    }

    int nArquivos = getNumeroArquivos(&info);

    //vetor dinamico para armazenar as relevancias; o indice do vetor é id-1
    Relevancias *vet = malloc(nArquivos * sizeof(Relevancias));

    for(int i = 1; i <= nArquivos; i++){
        vet[i-1].id = i;
        vet[i-1].relevancia = 0.0;
    }

    tfidfhash(tabela, strings, vet, nArquivos, nTermos, p, comp_pequisa_hash);

    //ordenação do vetor a partir da relevancia para printar na ordem
    qsort(vet, nArquivos, sizeof(Relevancias), comparaRel);

    int nResult = 0;
    for(int i = 1; i <= nArquivos; i++){
        if(vet[i-1].relevancia > 0.0000){
            printf("'%s' (arquivo%d.txt): relev.: %.3f\n", getNomeOriginal(&info, vet[i-1].id), vet[i-1].id, vet[i-1].relevancia);
            nResult++;
        }else{
            break;
        }
    }
    if(nResult == 0){
        printf("Nenhum documento corresponde a pesquisa\n");
    }

    for(int i = 0; i < nTermos; i++){
        free(strings[i]);
    }

    free(vet);
    free(strings);
}

