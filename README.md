# Trabalho prático de Algoritmos e Estruturas de Dados 2 - Pesquisa em Hash e PATRICIA com índice invertido
Observações: 
* O presente arquivo readme é mais legível no GitHub. Se não estiver nele, é recomendado que o acesse para leitura (<https://github.com/tavinEscada/tp1_aeds2/blob/main/README.md>).
* Este arquivo apresenta aspectos gerais do projeto; para mais detalhes sobre as estruturas em si, acesse o relatório presente no repositório (****link da doc).

O projeto consiste em um sistema que recebe *n* documentos, construídos com base nos [TCCs do curso de Ciência da Computação da UFV Campus Florestal](https://ccp.caf.ufv.br/tccs/), e realiza buscas de termos que possam estar presentes nesses TCCs. Em cada documento da pasta 'pocs', armazenamos o título, o resumo e, em alguns casos, as palavras chave de cada um dos artigos, e suas palavras são inseridas em estruturas do tipo tabela Hash e árvore PATRICIA. Com isso, é possível realizar buscas por termos e, com base nos índices invertidos a serem especificados adiante, o programa retorna o nome dos arquivos lidos por ordem de relevância em relação aos termos pesquisados.
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
<p align="center">
  <img src="https://github.com/user-attachments/assets/402d6fb4-00c8-4b64-812f-bc5e2b2db459"><br>
  <b>Figura 1 – Menu.</b>
</p>

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
<p align="center">
  <img src="https://github.com/user-attachments/assets/6944d612-4368-4b44-a006-0ab871817668"><br>
  <b>Figura 2 – Pasta de arquivos pré-processados.</b>
</p>

Nesses arquivos auxiliares, armazenamos as palavras de cada POC de maneira formatada (sem acentos, cedilha e palavras irrelevantes, como artigos e preposições), uma em cada linha. É importante observar que, caso o usuário faça um teste com x arquivos e execute o programa novamente com um número y < x de arquivos, o(s) x - y arquivo(s) remanescentes da execução anterior é/são excluído(s). Por exemplo, ao executar um teste com 3 arquivos e na próxima execução serem utilizados 2, o arquivo 'arquivosTratados/arquivo3.txt' é excluído, enquanto os demais que foram criados na primeira execução são sobrescritos pelas palavras dos novos arquivos. Assim, não são usados documentos que dizem respeito à execução anterior.

Após a leitura, voltamos ao menu e espera-se que o usuário digite 2 para dar continuidade e inserir as palavras nas estruturas. Tal inserção é feita para cada palavra em cada arquivo, mantendo controle do *idDoc* e da quantidade de vezes que cada palavra aparece em cada documento, de maneira que, se a palavra a ser inserida já estiver presente nas estruturas, apenas a quantidade de vezes que tal palavra aparece no documento atual da iteração é incrementada. Dessa maneira, cada palavra é acompanhada por *m* pares do tipo *<qtde, idDoc>*, sendo *m*, o número de documentos que contém a palavra, ou seja, há um desses pares para cada arquivo *idDoc* que tem a palavra. Logo, se 'arquivo1.txt' tem um certo termo 1 vez, 'arquivo2.txt' tem o mesmo termo 4 vezes, e tal termo não aparece em 'arquivo3.txt', os pares do termo em questão serão *<1, 1>* | *<4, 2>*.

Terminadas as inserções, voltamos ao menu e, ao escolher a opção 3, temos uma representação das estruturas: primeiro a tabela Hash, com as palavras em ordem alfabética e acompanhadas pelos pares e, depois, o mesmo para a PATRICIA, como nos trechos exemplificados abaixo.

<table align="center">
  <tr>
    <td>
      <img src="https://github.com/user-attachments/assets/00dbd2c8-7202-4cbd-94e0-fc400240505a" width="350"/>
    </td>
    <td>
      <img src="https://github.com/user-attachments/assets/8d0d77c2-6b32-41b9-98a2-45d58744dff5" width="350"/>
    </td>
  </tr>
  <tr>
    <td align="center"><b>Figura 3 - Print do índice na Hash.</b></td>
    <td align="center"><b>Figura 4 - Print do índice na PATRICIA.</b></td>
  </tr>
</table>

Após a impressão, o menu é apresentado novamente, e resta realizar a opção 4, que é a pesquisa. Ao executar tal operação, é necessário que o usuário digite as palavras envolvidas na busca, todas na mesma linha e seraradas por espaço. Note que se a entrada contiver acentos ou letras maiúsculas, eles serão adaptados, uma vez que nas estruturas são inseridas palavras sem acento e com todas as letras minúsculas. Assim, se a entrada for
```
ABóbora martÍrio ôniBUS
```
as palavras serão pesquisadas da seguinte forma:
```
abobora martirio onibus
```
Se algum outro símbolo (além de acentos) for digitado, tal caractere não será reconhecido e tampouco a palavra será encontrada na árvore e na tabela.
Assim, é feito o cálculo proposto do TF-IDF (Term Frequency - Inverse Document Frequency), de forma a listar os arquivos em ordem decrescente de acordo com a relevância em relação às palavras da pesquisa. Um exemplo pode ser observado ao digitar MyMobiConf na pesquisa:

<p align="center">
  <img src="https://github.com/user-attachments/assets/874965ab-4b32-4cd4-8173-a792fe7efd8b"><br>
  <b>Figura 5 – Exemplo de pesquisa na Hash.</b>
</p>

Note que acima estão apenas os documentos relevantes em relação à pesquisa. Os documentos com relevância desprezível não são mostrados. Note ainda que, para a PATRICIA, temos um resultado igual:

<p align="center">
  <img src="https://github.com/user-attachments/assets/fcbc176e-04b4-49c0-acc8-8798e05e691d"><br>
  <b>Figura 6 - Exemplo de pesquisa da PATRICIA.</b>
</p>

Em suma, é nisso que consiste o uso do projeto.

## Funções importantes
### Tratamento de acentos e cedilha
É usada uma mesma função de remoção de acentos para a entrada de arquivos da primeira opção do menu e para a entrada por terminal do Linux na pesquisa da opção 4 (a diferença para o terminal do Windows é detalhada mais adiante). Tal função recebe um vetor de caracteres e interpreta eles na codificação [UTF-8](https://www.utf8-chartable.de/) em sua representação hexadecimal com caracteres referentes ao bloco Unicode 'Basic Latin'. De acordo com tal tabela, as letras com acento e outros caracteres especiais pouco comuns são representados por dois códigos, um prefixo comum a um grupo de caracteres e o código propriamente dito que difere cada um; no caso das letras com acento (os caracteres que nos interessam) o prefixo é 'C3' para todas, e o que difere para identificar cada letra com cada acento é o byte seguinte. Então, por exemplo, o caractere 'á' é representado como 'C3 A1', e o caractere 'à' é 'C3 A0'. Assim, é feita uma primeira avaliação: se o caractere atual do vetor tem código 'C3', temos de avaliar qual letra substituir com base no próximo byte:

<p align="center">
  <img src="https://github.com/user-attachments/assets/55798322-e329-42f7-8ff1-948a467bcb21"><br>
  <b>Figura 7 - Avaliação de caractere especial em UTF-8.</b>
</p>

Assim, temos blocos semelhantes ao abaixo para cada caractere:

<p align="center">
  <img src="https://github.com/user-attachments/assets/58d41461-3735-48f2-ac4b-e34b4a97a822"><br>
  <b>Figura 8 - Caracteres que devem ser substituidos por 'a'.</b>
</p>

Após as verificações para as demais letras, realizamos a substituição:

<p align="center">
  <img src="https://github.com/user-attachments/assets/20a91c69-5b6e-4982-8514-d9f9ee008e49"><br>
  <b>Figura 9 - Substituição do caractere.</b>
</p>

Note que, na função, *i* é o índice de leitura dos caracteres e *j* é o de escrita. Assim, se *sub* existe, usamos *j* para fazer a substituição. Ao incrementá-lo, avançamos o índice de escrita, enquanto *i* avança dois bytes, o que era referente a 'C3' e o seguinte.

Caso o caractere atual não seja 'C3', apenas seguimos para o próximo caractere:

<p align="center">
  <img src="https://github.com/user-attachments/assets/a3ee8545-5bfd-4648-9dff-bfbd23dd83b1"><br>
  <b>Figura 10 - Avançando os índices.</b>
</p>

Concluindo o percurso na palavra, apenas inserimos o '\0', de fim de palavra, no lugar certo (índice de escrita *j*).

<p align="center">
  <img src="https://github.com/user-attachments/assets/75c97f87-6357-4ffa-b934-06dfd5e8ac27"><br>
  <b>Figura 11 - Inserção do '\0'.</b>
</p>

Já para remover acentos pelo terminal do Windows na pesquisa, interpretamos a codificação do terminal em [CP850](https://localizely.com/character-encodings/cp850/), e, portanto, devemos usar uma outra função. Na codificação em questão, cada caractere tem apenas um byte, diferente da outra função e, com isso, temos um processo mais simples:

<p align="center">
  <img src="https://github.com/user-attachments/assets/62a3d488-b3cd-4f81-a493-2d4ae154a4d7"><br>
  <b>Figura 12 - Verificação de caractere em CP850.</b>
</p>

Atribuimos, então, o byte atual de acordo com a tabela, de maneira semelhante para cada letra. Ao final, realizamos a substituição:

<p align="center">
  <img src="https://github.com/user-attachments/assets/71baa806-0121-4c63-9e06-f55ebfbfe7d0"><br>
  <b>Figura 13 - Substituição do caractere.</b>
</p>

Assim, usamos a primeira função tanto na leitura dos arquivos de entrada quanto na leitura da pesquisa por terminal no Linux, enquanto a segunda é usada na leitura por terminal no Windows.
Observação: a diferença das codificações abordadas podem ser observadas com prints: ao executar o trecho abaixo, dado um vetor de caracteres, é possível visualizar qual código está sendo usado

<p align="center">
  <img src="https://github.com/user-attachments/assets/440f63e1-e374-4546-becc-44cb8e5560a9"><br>
  <b>Figura 14 - Print do código dos caracteres.</b>
</p>

É possível, também, observar que, ao printar normalmente algum caractere especial, como em um aviso pelo terminal do Windows para o usuário, nos deparamos com coisas do tipo:

<p align="center">
  <img src="https://github.com/user-attachments/assets/365926ef-03ce-4aa0-aadc-cfef904f8fae"><br>
  <b>Figura 15 - Resultado de printf com acento.</b>
</p>

Isso se dá porque, ao digitar o caractere 'á' no código, por exemplo, ele é interpretado em UTF-8 como 'C3 A1', mas no terminal ele é interpretado em CP850, e de acordo com tal tabela, 'C3' corresponde ao símbolo '├', e 'A1' corresponde a 'í'.

### Leitura de arquivos
Na leitura, temos alguns pontos principais.
O arquivo de entrada especificado anteriormente deve estar na pasta do projeto; uma vez que o abrimos, verificamos o número de documentos informado na primeira linha, e se for um número válido, já é criado o diretório 'arquivosTratados', usando o comando 'mkdir', adaptado para que o repositório seja criado tanto em execuções no Windows quanto no Linux:

<p align="center">
  <img src="https://github.com/user-attachments/assets/7cb8383b-7cd5-41ee-a101-5866c17682c9"><br>
  <b>Figura 16 – Diferenciação dos sistemas.</b>
</p>

Vale citar ainda que o bloco de código da imagem acima define também a variável *sistema*, que será importante para adaptar a leitura dos termos de pesquisa, a ser especificada posteriormente.
Na leitura dos arquivos, as palavras são separadas por alguns marcadores:
<p align="center">
  <img src="https://github.com/user-attachments/assets/27772e6a-9008-4475-b461-fcb44661b865"><br>
  <b>Figura 17 - Separadores de palavra.</b>
</p>
Além disso, só são inseridas palavras que se considera válidas; após retirar os acentos e minúsculas, conferimos também se a palavra em questão não está na lista de palavras consideradas irrelevantes (como 'the', 'como', 'de', etc). Então, escrevemos as palavras válidas nos arquivos auxiliares. Note também que o endereço dos arquivos auxiliares é construído com a concatenação de strings:
<p align="center">
  <img src="https://github.com/user-attachments/assets/6cbc5f2b-c3d6-4b0b-9146-b0f9ce68750b"><br>
  <b>Figura 18 - Endereço dos arquivos auxiliares.</b>
</p>
Isso é feito para cada um dos arquivos, no padrão já citado (arquivo*i*.txt). Depois de ler, então, cada arquivo (considerando que não haja erro nos nomes, no número de documentos, etc), o arquivo de entrada é fechado, e os possíveis documentos remanescentes são excluídos, com o uso da função:
<p align="center">
  <img src="https://github.com/user-attachments/assets/32d5ce57-6abe-44ee-98b7-644152849daf"><br>
  <b>Figura 19 - Exclusão dos arquivos remanescentes.</b>
</p>
Na função de leitura, a função acima é usada tendo como parâmetro justamente o *n*, número de arquivos da execução atual; dessa forma, se existem arquivos *idDoc* > *n*, eles são excluídos.
Outros pontos que valem ser citados sobre a leitura: armazenamos os nomes de cada POC na execuçao em uma matriz, pois precisamos deles no print da pesquisa:

<p align="center">
  <img src="https://github.com/user-attachments/assets/6c62b14e-1fec-4fd8-aebe-4c0e006312b5"><br>
  <b>Figura 20 - Preenchendo a matriz dos nomes.</b>
</p>

Uma vez que a inserção se dá a partir dos arquivos auxiliares, temos que recuperar esses nomes originais de alguma forma. Assim, retornamos a estrutura InfoDocs, com o número de arquivos envolvido na execução, a matriz com os nomes originais e, novamente, considerando que a leitura tenha sido bem-sucedida, *sucesso* é igual a 1.

### Construção dos índices
Como já temos os arquivos pré-processados após a leitura, precisamos apenas abrir cada um e inserir as palavras nas estruturas. Assim, pegamos, a partir do 'arquivo1.txt', as palavras de cada um:
<p align="center">
  <img src="https://github.com/user-attachments/assets/4ccb935d-84b7-4839-8835-e9fa77445d13"><br>
  <b>Figura 21 - Momento da inserção.</b>
</p>

### Exibição dos índices
Para exibir tanto os índices da Hash quanto os da PATRICIA, é usada a função abaixo, que, para cada termo, percorre a lista encadeada em que cada posição tem um par *<qtde, idDoc>*, como foi citado anteriormente.
<p align="center">
  <img src="https://github.com/user-attachments/assets/2cbbd473-4c59-4263-9749-820a87ad841f"><br>
  <b>Figura 22 - Impressão dos índices.</b>
</p>
As funções são, então, acionadas separadamente para cada estrutura.
<p align="center">
  <img src="https://github.com/user-attachments/assets/7e9114ae-4e66-4213-b48a-0e5599c6dc04"><br>
  <b>Figura 23 - Função que imprime os índices de cada estrutura.</b>
</p>

### TF-IDF
A partir dos textos já indexados, podem ser realizadas pesquisas com base em termos de busca para se calcular a relevância do documento. Para tanto, são feitos os cálculos do TF-IDF (Term frequency – Inverse Document Frequency), um que percorre a estrutura da patrícia e outro que percorre a tabela hash. De modo geral, ambas implementações são semelhantes e seguem uma mesma lógica.

Os principais argumentos da função são: o endereço da origem da estrutura a ser percorrida (raiz da Patrícia ou a tabela), a entrada a ser pesquisada, a quantidade de termos pesquisados e as informações da coleção de documentos onde deseja-se pesquisar. Sendo assim, busca-se iterar sobre cada documento atribuindo um valor numérico referente à sua relevância seguindo os cálculos propostos pela especificação do trabalho. Segue abaixo a implementação do TF-IDF para a Patrícia e em sequência a explicação dos principais tópicos.

<p align="center">
  <img src="https://github.com/user-attachments/assets/3fe8785a-a0e6-4662-b72d-c3fa496b4797"><br>
  <b>Figura 24 - Funções TF-IDF.</b>
</p>

Para efetuar esses cálculos, fez-se necessário percorrer a estrutura (patrícia ou hash) e encontrar, para cada documento *i*, a quantidade de termos distintos. Posteriormente, calcula-se um somatório denominado "sumPtermo". Esse somatório percorre, para o documento *i*, cada termo da entrada a ser pesquisado e recupera onde esse termo está armazenado na estrutura (Patricia ou hash), de forma a obter o número de documentos que contém esse termo (*dj*) e o número de ocorrências desse termo no documento *i* (*ocorrenciaT*). Assim, são feitos cálculos com essas informações para cada termo, retornando o resultado desse somatório. Esse valor retornado será multiplicado pelo inverso da quantidade de termos distintos no documento *i*, sendo esse resultado a relevância do documento *i* para a entrada pesquisada.

### Pesquisa
Aqui, temos uma função de pesquisa para a PATRICIA e uma para a Hash e ambas se comportam de maneira semelhante. Lemos a entrada do usuário pelo terminal e retiramos os acentos de acordo com o sistema operacional, a partir da definição citada na Figura 16 anteriormente:
<p align="center">
  <img src="https://github.com/user-attachments/assets/112f6e4c-9daf-4569-90eb-cb8f49250a08"><br>
  <b>Figura 25 - Escolhendo a função de tratamento de acentos.</b>
</p>

Após isso, criamos um vetor dinâmico do tipo relevâncias, para armazenar as relevâncias que serão calculadas e relacioná-las com os *idDoc*; inicialmente as relevâncias são nulas.

<p align="center">
  <img src="https://github.com/user-attachments/assets/a522a023-f482-47a9-a567-50d6627e184a"><br>
  <b>Figura 26 - Endereço dos arquivos auxiliares.</b>
</p>
Depois, calculamos o TF-IDF de cada arquivo, ordenamos usando o 'qsort', e podemos então printar os resultados da pesquisa. Note que apenas printamos os documentos com relevância não desprezível e, caso nenhum arquivo tenha tal característica, escrevemos que nenhum documento atende aos termos digitados.
<p align="center">
  <img src="https://github.com/user-attachments/assets/9ceb222e-1d24-428d-8211-cb2cae19aa4f"><br>
  <b>Figura 27 - Printando o resultado da pesquisa.</b>
</p>

## Comentários
A construção desse documento foi baseada nos [tutoriais de HTML da W3Schools](https://www.w3schools.com/html/default.asp) e no [tutorial de Markdown do Git](https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax).
