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

void PesquisaPat(TipoChave palavra, TipoArvore NoRaiz,int* visitas) {

    TipoArvore NoAtual=NoRaiz;

    if (Eh_Externo(NoAtual)) {
        if (strcmp((const char*)palavra, (const char*)NoAtual->NO.chave) == 0){
            printf("Elemento encontrado\n");
        }
        else{
            printf("Elemento nao encontrado\n");
        }
        return;
    }

    if (palavra[NoAtual->NO.NInterno.indice] >= NoAtual->NO.NInterno.caractere){
        (*visitas)+=1;
        PesquisaPat(palavra, NoAtual->NO.NInterno.dir,visitas);
    }
    else{
        (*visitas)+=1;
        PesquisaPat(palavra, NoAtual->NO.NInterno.esq,visitas);
    }
}

TipoArvore InsereEntrePat(TipoChave palavra, TipoArvore *NoAtual, int i, char caractere_interno){
  
    TipoArvore NoExt;
    if (Eh_Externo(*NoAtual) || i < (*NoAtual)->NO.NInterno.indice){
        
        NoExt = Cria_NO_Externo(palavra);
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
            (*NoAtual)->NO.NInterno.dir = InsereEntrePat(palavra,&(*NoAtual)->NO.NInterno.dir,i,caractere_interno);
        }
        else{
            (*NoAtual)->NO.NInterno.esq = InsereEntrePat(palavra,&(*NoAtual)->NO.NInterno.esq,i,caractere_interno);
        }
        return (*NoAtual);
    }
}

TipoArvore InserePat(TipoChave palavra, TipoArvore *NoRaiz){
  
    TipoArvore NoAtual;
    int i;
    char caractere_dif;
  
    if (*NoRaiz == NULL) 
        return (Cria_NO_Externo(palavra));

     
    NoAtual = *NoRaiz;

    while (!Eh_Externo(NoAtual)){

        if (palavra[NoAtual->NO.NInterno.indice] >= NoAtual->NO.NInterno.caractere)
            NoAtual = NoAtual->NO.NInterno.dir;
        else 
            NoAtual = NoAtual->NO.NInterno.esq;
    }

    i = 0;
    while (i<= strlen((const char*)palavra) && palavra[i] == NoAtual->NO.chave[i])
        i++;

    if (i > strlen((const char*)palavra)){
        printf("Erro: chave ja esta na arvore\n");
        return (*NoRaiz); 
        //incrementar indice invertido aqui
    }
    else{
        caractere_dif=NoAtual->NO.chave[i];
        //garante que o caractere em nó interno será sempre o maior
        //prefixos irão sempre para a esquerda pois \0 é menor que todos caracteres
        return InsereEntrePat(palavra, NoRaiz, i, (palavra[i] > caractere_dif) ? palavra[i] : caractere_dif);
    }
}

void ImprimeOrdemPat(TipoArvore t){
    if (t == NULL) return;

    if (Eh_Externo(t)){
        printf("%s\n", (char *)t->NO.chave);
    } 
    else{
        ImprimeOrdemPat(t->NO.NInterno.esq);
        ImprimeOrdemPat(t->NO.NInterno.dir);
    }
}


// int main() {

//     //main teste
//     TipoArvore x = NULL;
//     int v=0; 
//     char *vetor[] = {
//     "abacate", "abelha", "abismo", "abrir", "absoluto", "academia", "acender", "acordo", "adesivo",
//     "admin", "aeronave", "alface", "algoritmo", "almofada", "amarelo", "amigo", "analisar", "anel",
//     "animal", "ansioso", "anual", "apagar", "apetite", "apito", "aprender", "aquilo", "arquivo", 
//     "arroz", "arte", "arvore", "assunto", "atitude", "atrativo", "aula", "automovel", "azul",

//     "bacia", "bala", "banco", "banana", "barato", "barco", "barra", "batata", "bebida", "beleza",
//     "bicho", "bicicleta", "bola", "bolacha", "boi", "bola", "boliche", "bolada", "bom", "borda",
//     "borracha", "botao", "branco", "bravo", "brincar", "brinquedo", "broto", "bruxa",

//     "cabra", "cacto", "cachorro", "cadeado", "cafe", "caixa", "cama", "camelo", "caminho", "caneta",
//     "canhoto", "capitulo", "caramba", "carinho", "carne", "carro", "casa", "casamento", "casal", 
//     "casco", "cavalo", "caverna", "cebola", "celular", "centro", "cerveja", "chegada", "chiclete",
//     "chuva", "cidade", "cinema", "cinto", "circulo", "claro", "cobra", "cobrir", "coelho", "coisa",
//     "colher", "comando", "comer", "comida", "comprar", "computador", "concha", "coracao", "corredor",
//     "correr", "corrida", "corte", "couro", "cravo", "criar", "criança", "cruzar", "cuidadoso", "cultura",

//     "dado", "dama", "dança", "dedo", "desenho", "deserto", "desligar", "destino", "dia", "diferente",
//     "dificil", "dinheiro", "direcao", "diversao", "doce", "doente", "dormir", "dourado", "dragao", "duelo",

//     "elefante", "elogio", "embaixo", "embalagem", "empate", "empresa", "encontro", "energia", "enfeite",
//     "engraçado", "enorme", "entrada", "enviar", "escola", "escuro", "esfera", "espelho", "espeto",
//     "esquilo", "estrela", "estudo", "etapa", "euforia", "exame", "exemplo", "experto", "exterior",

//     "faca", "fada", "falar", "famoso", "fantasma", "faro", "fatia", "favorito", "feliz", "ferida",
//     "ferro", "festa", "figura", "filho", "filme", "fita", "fogo", "folha", "fonte", "forca", "forma",
//     "forno", "foto", "fraco", "fralda", "frio", "fruta", "fundo", "furar", "futuro",

//     "galo", "garfo", "garganta", "garota", "gasolina", "gato", "gelado", "girassol", "girar", "giz",
//     "goleiro", "gota", "grama", "grande", "gravata", "grelha", "grupo", "guarda", "guerra", "guitarra",

//     "homem", "honesto", "horizonte", "hospital", "hotel", "hora", "horta", "humano", "humilde",

//     "ilha", "imagem", "impressao", "impulso", "incrivel", "indice", "indio", "infantil", "inverno",
//     "irmão", "irritado", "isca", "item", "idade",

//     "jacare", "jantar", "janela", "jardim", "jarra", "jato", "jogo", "joia", "jornal", "jovem", "juiz",
//     "julho", "junho", "jurado", "justo",

//     "lago", "lata", "leao", "leite", "lento", "letra", "livro", "lobo", "lugar", "luz",

//     "macaco", "maca", "magia", "mala", "mamifero", "manga", "manha", "manteiga", "mar", "martelo", "massa",
//     "medo", "melancia", "menina", "mensagem", "mesa", "metro", "mimosa", "milho", "misterio", "mochila",
//     "moda", "molho", "momento", "monstro", "morcego", "moto", "movimento", "mundo", "musica",

//     "navio", "neblina", "negocio", "neve", "noite", "norte", "nublado", "numero", "nutrir",

//     "oceano", "oculos", "oferta", "olhar", "onda", "orelha", "osso", "outono", "ovo",

//     "pato", "paz", "peixe", "pena", "pente", "pernilongo", "peru", "pescoço", "peso", "petala", "piano",
//     "pintura", "pipoca", "piso", "placa", "planeta", "poco", "poesia", "polvo", "porta", "porco", "prato",
//     "preto", "prima", "professor", "pulo", "puxar", "pyruca",

//     "quadro", "qualquer", "quarto", "quente", "quilo", "quinta",

//     "rabo", "raio", "rato", "receita", "rede", "reino", "relogio", "remedio", "resposta", "rima", "rio",
//     "risada", "roda", "rosto", "rua", "ruido",

//     "sabado", "sabor", "sacola", "sala", "salto", "samba", "sanduiche", "sapato", "segredo", "selo",
//     "selva", "sempre", "serpente", "sexta", "silencio", "simbolo", "sino", "sistema", "sol", "soldado",
//     "sonho", "sorriso", "sorte", "susto",

//     "taco", "tarde", "telefone", "tempo", "terra", "texto", "tigre", "tiro", "toalha", "tomate", "touro",
//     "traco", "travesseiro", "trem", "triangulo", "triste", "trombeta", "trovão", "tubo",

//     "urso", "urna", "utensilio", "uva",

//     "vaca", "vagalume", "valente", "valor", "vapor", "vaso", "veia", "vela", "velocidade", "vento", "verao",
//     "verde", "verme", "vestido", "viajar", "vibrar", "vida", "vila", "vinho", "violao", "vivo", "voar", "voce",
//     "voltar", "vontade", "voo", "vulcao",

//     "watt", "web", "wifi",

//     "xadrez", "xadrez", "xale", "xampu", "xarope", "xeque", "xerife", "xicara", "xilofone", "xis", "xuxu",

//     "yate", "yoga", "yogurte", "yasmim",

//     "zangado", "zebra", "zero", "zigue", "zoologico", "zumbi"
// };


//     int n = sizeof(vetor) / sizeof(vetor[0]);

//     for (int i = 0; i < n; i++) {
//         x = InserePat((unsigned char*)vetor[i], &x);
//     }
    
//     ImprimeOrdemPat(x);

//     printf("\n");

//     for (int i = 0; i < n; i++) {
//         printf("pesquisa: %s\n", vetor[i]);
//         PesquisaPat((unsigned char*)vetor[i], x,&v);
//     }
//     printf("visitas =%d",v);

//     return 0;
// }


