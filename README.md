# Trabalho prático de Algoritmos e Estruturas de Dados 2 - Pesquisa em Hash e PATRICIA com índice invertido
Observação: o presente arquivo readme é notavelmente mais legível no GitHub. Se não estiver nele, é recomendado que acesse (<https://github.com/tavinEscada/tp1_aeds2/blob/main/README.md>).

O presente projeto consiste em um sistema que recebe *n* documentos, construídos com base nos TCCs do curso de Ciência da Computação da UFV Campus Florestal, obtidos em <https://ccp.caf.ufv.br/tccs/> e realiza buscas de termos que possam estar presentes nesses TCCs. Em cada documento da pasta 'pocs', armazenamos o título, o resumo e, em alguns casos, as palavras chave de cada um dos artigos, e suas palavras são inseridas em estruturas do tipo tabela Hash e árvore PATRICIA. Com isso, é possível realizar buscas por termos e, com base nos índices invertidos a serem especificados adiante, o programa retorna o nome dos arquivos lidos por ordem de relevância em relação aos termos pesquisados.
## Compilação e execução
Antes de tudo, é importante certificar-se que se está na pasta do projeto. Com isso em mente, observemos as formas de se compilar:
No terminal do Windows, o projeto pode ser compilado a partir do arquivo Makefile do projeto, com o utilitário make do MinGW:
```
mingw32-make
```
Ou, ainda, usando diretamente o comando do GCC:
```
gcc src/palavra.c src/hash.c src/patricia.c src/infoDocs.c src/tp.c src/main.c -lm -Wall -Wextra -g -o main
```
No Linux, pode ser usado o mesmo comando acima, ou compilar a partir do Makefile, digitando no terminal:
```
make
```
Após compilar, em ambos os sistemas operacionais podemos executar o projeto com:
```
./main
```
No início da execução, é apresentado o menu:

![image](https://github.com/user-attachments/assets/c83bfd7d-3c06-4887-ac5f-dd0bd809e635)

Inicialmente, espera-se que o usuário escolha a primeira opção, digitando 1 para realizar a entrada de dados. A entrada é feita a partir de um arquivo de entrada que tem na primeira linha o número *n* de POCs a serem lidos e em cada uma das *n* linhas seguintes se encontram o nome de cada arquivo:
```
n
arquivo1.txt
arquivo2.txt
...
arquivon.txt
```
Na prática, um exemplo que temos presente no repositório é o 'teste.txt':
```
3
A hardware accelerator implementation for real-time collision detection.txt
A Genetic Algorithm for Multi-Component Optimization.txt
A otimizacao da distribuicao de pot.txt
```
Assim, deve-se digitar o nome de um arquivo de texto similar para utilizar o programa. Considerando que foi informado um arquivo válido, (com *n* válido e nomes corretos), é criado (caso seja a primeira execução) uma pasta 'arquivosTratados', onde são criados arquivos auxiliares. Cada um dos arquivos auxiliares é criado com o nome 'arquivo*i*.txt', em que *i* (valor único no intervalo fechado de 1 a *n*) é definido como *idDoc*, um identificador para cada arquivo. Exemplo da pasta e dos arquivos auxiliares criados para um teste de 3 POCs:

![image](https://github.com/user-attachments/assets/6944d612-4368-4b44-a006-0ab871817668)

Nesses arquivos auxiliares, armazenamos as palavras de cada POC de maneira formatada (sem acentos, cedilha e palavras irrelevantes, como artigos e preposições), uma em cada linha. É importante observar que, caso o usuário faça um teste com x arquivos e execute o programa novamente com um número y < x de arquivos, o(s) x - y arquivo(s) remanescentes da execução anterior é/são excluído(s). Exemplo: ao executar um teste com 3 arquivos e na próxima execução utilizar 2, o arquivo 'arquivosTratados/arquivo3.txt' é excluído, enquanto os demais que foram criados na primeira execução são sobrepostos pelas palavras dos novos arquivos. Assim, não são usados documentos que dizem respeito à execução anterior.
Após a leitura, voltamos ao menu e espera-se que o usuário digite 2 para dar continuidade e inserir as palavras nas estruturas. Tal inserção é feita para cada palavra em cada arquivo, mantendo controle do *idDoc* e da quantidade de vezes que cada palavra aparece em cada documento, de maneira que, se a palavra a ser inserida já estiver presente nas estruturas, apenas a quantidade de vezes que tal palavra aparece no documento atual da iteração é incrementada. Dessa maneira, cada palavra é acompanhada por *m* pares do tipo *<qtde, idDoc>*, em que *m* é o número de documentos que contém a palavra, ou seja, um desses pares para cada arquivo *idDoc* que tem a palavra. Logo, se 'arquivo1.txt' tem um termo 1 vez e 'arquivo2.txt' tem o mesmo termo 4 vezes, os pares do termo em questão serão *<1, 1>* | *<4, 2>*.
Terminadas as inserções, voltamos ao menu, e ao escolher a opção 3, temos uma representação das estruturas: primeiro a tabela Hash, com as palavras em ordem alfabética e acompanhadas pelos pares e, depois, o mesmo para a PATRICIA, como nos trechos exemplificados abaixo.

![image](https://github.com/user-attachments/assets/00dbd2c8-7202-4cbd-94e0-fc400240505a) ![image](https://github.com/user-attachments/assets/8d0d77c2-6b32-41b9-98a2-45d58744dff5)

Após a impressão, o menu é apresentado novamente, e resta realizar a opção 4, que é a pesquisa. Ao executar tal operação, é necessário que o usuário digite as palavras envolvidas na pesquisa, na mesma linha e seraradas por espaço. Note que se a entrada contiver acentos e letras maiúsculas, eles serão adaptados, uma vez que nas estruturas são inseridas palavras sem acento e com todas as letras minúsculas. Assim, se a entrada for
```
ABóbora martÍrio ôniBUS
```
as palavras serão separadas, para serem pesquisadas da seguinte forma
```
abobora martirio onibus
```
