# Trabalho prático de Algoritmos e Estruturas de Dados 2 - Pesquisa em Hash e PATRICIA com índice invertido
Observação: o presente arquivo readme é mais legível no GitHub. Se não estiver nele, é recomendado que o acesse para leitura (<https://github.com/tavinEscada/tp1_aeds2/blob/main/README.md>).

O presente projeto consiste em um sistema que recebe *n* documentos, construídos com base nos [TCCs do curso de Ciência da Computação da UFV Campus Florestal](https://ccp.caf.ufv.br/tccs/), e realiza buscas de termos que possam estar presentes nesses TCCs. Em cada documento da pasta 'pocs', armazenamos o título, o resumo e, em alguns casos, as palavras chave de cada um dos artigos, e suas palavras são inseridas em estruturas do tipo tabela Hash e árvore PATRICIA. Com isso, é possível realizar buscas por termos e, com base nos índices invertidos a serem especificados adiante, o programa retorna o nome dos arquivos lidos por ordem de relevância em relação aos termos pesquisados.
## Compilação e execução
Antes de tudo, é importante certificar-se que se está na pasta do projeto. Com isso em mente, observemos as formas de se compilar:
no terminal do Windows, o projeto pode ser compilado a partir do arquivo Makefile do projeto, com o utilitário make do MinGW:
```
mingw32-make
```
Ou, ainda, usando diretamente o comando do GCC:
```
gcc src/palavra.c src/hash.c src/patricia.c src/infoDocs.c src/tp.c src/main.c -lm -Wall -Wextra -g -o main
```
No Linux, pode ser usado o mesmo comando do GCC acima, ou compilar a partir do Makefile, digitando no terminal:
```
make
```
Após compilar, em ambos os sistemas operacionais podemos executar o projeto com:
```
./main
```
No início da execução, é apresentado o menu:

![image](https://github.com/user-attachments/assets/402d6fb4-00c8-4b64-812f-bc5e2b2db459)

Inicialmente, espera-se que o usuário escolha a primeira opção, digitando 1 para realizar a entrada de dados. A entrada é feita a partir de um arquivo de entrada que tem na primeira linha o número *n* de POCs a serem lidos e em cada uma das *n* linhas seguintes se encontram os nomes dos arquivos:
```
n
arquivo1.txt
arquivo2.txt
...
arquivon.txt
```
Na prática, um exemplo pode ser:
```
3
A hardware accelerator implementation for real-time collision detection.txt
A Genetic Algorithm for Multi-Component Optimization.txt
A otimizacao da distribuicao de pot.txt
```
Assim, deve-se digitar o nome de um arquivo de texto similar ao representado acima para utilizar o programa. Considerando que foi informado um arquivo válido (com *n* válido e nomes corretos), é criado (caso seja a primeira execução) uma pasta 'arquivosTratados', onde são criados arquivos auxiliares. Cada um dos arquivos auxiliares é criado com o nome 'arquivo*i*.txt', em que *i* é definido como *idDoc*, um identificador único no intervalo fechado de 1 a *n*, para cada arquivo. Exemplo da pasta e dos arquivos auxiliares criados para um teste de 3 POCs:

![image](https://github.com/user-attachments/assets/6944d612-4368-4b44-a006-0ab871817668)

Nesses arquivos auxiliares, armazenamos as palavras de cada POC de maneira formatada (sem acentos, cedilha e palavras irrelevantes, como artigos e preposições), uma em cada linha. É importante observar que, caso o usuário faça um teste com x arquivos e execute o programa novamente com um número y < x de arquivos, o(s) x - y arquivo(s) remanescentes da execução anterior é/são excluído(s). Por exemplo, ao executar um teste com 3 arquivos e na próxima execução serem utilizados 2, o arquivo 'arquivosTratados/arquivo3.txt' é excluído, enquanto os demais que foram criados na primeira execução são sobrescritos pelas palavras dos novos arquivos. Assim, não são usados documentos que dizem respeito à execução anterior.

Após a leitura, voltamos ao menu e espera-se que o usuário digite 2 para dar continuidade e inserir as palavras nas estruturas. Tal inserção é feita para cada palavra em cada arquivo, mantendo controle do *idDoc* e da quantidade de vezes que cada palavra aparece em cada documento, de maneira que, se a palavra a ser inserida já estiver presente nas estruturas, apenas a quantidade de vezes que tal palavra aparece no documento atual da iteração é incrementada. Dessa maneira, cada palavra é acompanhada por *m* pares do tipo *<qtde, idDoc>*, sendo *m*, o número de documentos que contém a palavra, ou seja, há um desses pares para cada arquivo *idDoc* que tem a palavra. Logo, se 'arquivo1.txt' tem um certo termo 1 vez, 'arquivo2.txt' tem o mesmo termo 4 vezes, e tal termo não aparece em 'arquivo3.txt', os pares do termo em questão serão *<1, 1>* | *<4, 2>*.

Terminadas as inserções, voltamos ao menu e, ao escolher a opção 3, temos uma representação das estruturas: primeiro a tabela Hash, com as palavras em ordem alfabética e acompanhadas pelos pares e, depois, o mesmo para a PATRICIA, como nos trechos exemplificados abaixo.

![image](https://github.com/user-attachments/assets/00dbd2c8-7202-4cbd-94e0-fc400240505a) ![image](https://github.com/user-attachments/assets/8d0d77c2-6b32-41b9-98a2-45d58744dff5)

Após a impressão, o menu é apresentado novamente, e resta realizar a opção 4, que é a pesquisa. Ao executar tal operação, é necessário que o usuário digite as palavras envolvidas na pesquisa, todas na mesma linha e seraradas por espaço. Note que se a entrada contiver acentos ou letras maiúsculas, eles serão adaptados, uma vez que nas estruturas são inseridas palavras sem acento e com todas as letras minúsculas. Assim, se a entrada for
```
ABóbora martÍrio ôniBUS
```
as palavras serão pesquisadas da seguinte forma:
```
abobora martirio onibus
```
Se algum outro símbolo (além de acentos) for digitado, tal caractere não será reconhecido e tampouco a palavra será encontrada na árvore e na tabela.
Assim, é feito o cálculo proposto do TF-IDF (Term Frequency - Inverse Document Frequency), de forma a listar os arquivos em ordem decrescente de acordo com a relevância em relação às palavras da pesquisa. Um exemplo pode ser observado ao digitar MyMobiConf na pesquisa:

![image](https://github.com/user-attachments/assets/874965ab-4b32-4cd4-8173-a792fe7efd8b)

Note que acima estão apenas os documentos relevantes em relação à pesquisa. Os demais documentos serão impressos abaixo, mas com a relevância nula, pois não contém o termo pesquisado. Note ainda que, para a PATRICIA, temos um resultado igual:

![image](https://github.com/user-attachments/assets/fcbc176e-04b4-49c0-acc8-8798e05e691d)

Em suma, é nisso que consiste o uso do projeto.

## Funções importantes
### Leitura de arquivos


### Tratamento de acentos e cedilha
É usada uma mesma função de remoção de acentos para a entrada de arquivos da primeira opção do menu e para a entrada por terminal do Linux na pesquisa da opção 4 (a diferença para o terminal do Windows é detalhada mais adiante). Tal função recebe um vetor de caracteres e interpreta eles na codificação [UTF-8](https://www.utf8-chartable.de/) em sua representação hexadecimal com caracteres referentes ao bloco Unicode 'Basic Latin'. De acordo com tal tabela, as letras com acento e outros caracteres especiais pouco comuns são representados por dois códigos, um prefixo comum a um grupo de caracteres e o código propriamente dito que difere cada um; no caso das letras com acento (os caracteres que nos interessam) o prefixo é 'C3' para todas, e o que difere para identificar cada letra com cada acento é o byte seguinte. Então, por exemplo, o caractere 'á' é representado como 'C3 A1', e o caractere 'à' é 'C3 A0'. Assim, é feita uma primeira avaliação: se o caractere atual do vetor tem código 'C3', temos de avaliar qual letra substituir com base no próximo byte:

![image](https://github.com/user-attachments/assets/55798322-e329-42f7-8ff1-948a467bcb21)

Assim, temos blocos semelhantes ao abaixo para cada caractere:

![image](https://github.com/user-attachments/assets/58d41461-3735-48f2-ac4b-e34b4a97a822)

Após as verificações para as demais letras, realizamos a substituição:

![image](https://github.com/user-attachments/assets/20a91c69-5b6e-4982-8514-d9f9ee008e49)

Note que, na função, *i* é o índice de leitura dos caracteres e *j* é o de escrita. Assim, se *sub* existe, usamos *j* para fazer a substituição. Ao incrementá-lo, avançamos o índice de escrita, enquanto *i* avança dois bytes, o que era referente a 'C3' e o seguinte.

Caso o caractere atual não seja 'C3', apenas seguimos para o próximo caractere:

![image](https://github.com/user-attachments/assets/a3ee8545-5bfd-4648-9dff-bfbd23dd83b1)

Concluindo o percurso na palavra, apenas inserimos o '\0', de fim de palavra, no lugar certo (índice de escrita *j*).

![image](https://github.com/user-attachments/assets/75c97f87-6357-4ffa-b934-06dfd5e8ac27)

Já para remover acentos pelo terminal do Windows na pesquisa, interpretamos a codificação do terminal em [CP850](https://localizely.com/character-encodings/cp850/), e, portanto, devemos usar uma outra função. Na codificação em questão, cada caractere tem apenas um byte, diferente da outra função e, com isso, temos um processo mais simples:

![image](https://github.com/user-attachments/assets/62a3d488-b3cd-4f81-a493-2d4ae154a4d7)

Atribuimos, então, o byte atual de acordo com a tabela, de maneira semelhante para cada letra. Ao final, realizamos a substituição:

![image](https://github.com/user-attachments/assets/71baa806-0121-4c63-9e06-f55ebfbfe7d0)

Observação: a diferença das codificações abordadas podem ser observadas com prints: ao executar o trecho abaixo, dado um vetor de caracteres, é possível visualizar qual código está sendo usado

![image](https://github.com/user-attachments/assets/440f63e1-e374-4546-becc-44cb8e5560a9)

É possível, também, observar que, ao printar normalmente algum caractere especial, como em um aviso pelo terminal para o usuário, nos deparamos com coisas do tipo:

![image](https://github.com/user-attachments/assets/365926ef-03ce-4aa0-aadc-cfef904f8fae)

Isso se dá porque, ao digitar o caractere 'á' no código, por exemplo, ele é interpretado em UTF-8 como 'C3 A1', mas no terminal ele é interpretado em CP850, e de acordo com tal tabela, 'C3' corresponde ao símbolo '├', e 'A1' corresponde a 'í'.

### TF-IDF

A partir dos textos já indexados, podem ser realizadas pesquisas com base em termos de busca para se calcular a relevância do documento. Para tanto, criou-se dois cálculos TF-IDF (Term frequency – Inverse Document Frequency), um que percorre a estrutura da patrícia e outro que percorre a tabela hash. De modo geral, ambas implementações são semelhantes e seguem uma mesma lógica.

Os principais argumentos da função são: o endereço da origem da estrutura a ser percorrida (raiz da Patrícia ou a tabela), a entrada a ser pesquisada, a quantidade de termos pesquisados e as informações da coleção de documentos onde deseja-se pesquisar. Sendo assim, busca-se iterar sobre cada documento atribuindo um valor numerico referente a sua relevância seguindo os cálculos propostos pela especificação do Trabalho. Segue abaixo a implementação do grupo para esse procedimento.

![image](https://github.com/user-attachments/assets/3fe8785a-a0e6-4662-b72d-c3fa496b4797)


Para efetuar esses cálculos, fez-se necessário percorrer a estrutura (patrícia ou hash) e encontrar, para cada documento i, a quantidade de termos distintos. Posteriormente, calcula-se um somatório denominado "sumPtermo". Esse somatório percorre, para o documento i, cada termo da entrada a ser pesquisada e recupera onde esse termo está armazenado na estrutura (Patricia ou hash), de forma a obter o número de documentos que contém esse termo (dj) e o número de ocorrência desse termo no documento i. Posteriormente, é efetuado cálculos sobre essas informações para cada termo, retornando um valor. Esse valor retornado, será multiplicado pelo inverso da quantidade de termos distindo no dumento i, sendo esse resultado a relevância do documento i para a entrada pesquisada.
