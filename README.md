# Trabalho prático de Algoritmos e Estruturas de Dados 2 - Pesquisa em Hash e PATRICIA com índice invertido
O presente projeto consiste em um sistema que recebe *n* documentos, construídos com base nos TCCs do curso de Ciência da Computação da UFV Campus Florestal, obtidos em <https://ccp.caf.ufv.br/tccs/>. Em cada documento da pasta 'pocs', armazenamos o título, o resumo e, em alguns casos, as palavras chave de cada artigo. A partir de tais documentos, suas palavras são inseridas em estruturas do tipo tabela Hash e árvore PATRICIA. Com isso, é possível realizar buscas por termos e, com base nos índices invertidos a serem especificados adiante, o programa retorna o nome dos arquivos lidos por ordem de relevância em relação aos termos pesquisados.
## Compilação e execução
Antes de tudo, é importante certificar-se que se está na pasta do projeto. Com isso em mente, observemos as formas de se compilar:
No terminal do Windows, o projeto pode ser compilado a partir do arquivo Makefile do projeto, com a utilização do utilitário make do MinGW:
```
mingw32-make
```
Ou, ainda, usando diretamente o comando do GCC:
```
gcc src/palavra.c src/hash.c src/patricia.c src/infoDocs.c src/tp.c src/main.c -Wall -Wextra -g -o main
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
Assim, deve-se digitar o nome de um arquivo de texto similar para utilizar o programa. Considerando que foi informado um arquivo válido, (com *n* válido e nomes corretos), é criado (caso seja a primeira execução) um repositório 'arquivosTratados', onde são criados arquivos auxiliares. Cada um dos arquivos auxiliares é criado com o nome 'arquivo*i*.txt', em que *i* (no intervalo de 1 a *n*) é definido como *idDoc*, um identificador para cada arquivo. É importante observar que, caso o usuário faça um teste com x arquivos e execute o programa novamente com um número y < x de arquivos, o(s) x - y arquivo(s) remanescentes da execução anterior é/são excluído(s). Exemplo: ao executar um teste com três arquivos e na próxima execução usar dois, o arquivo 'arquivosTratados/arquivo3.txt' é excluído, enquanto os demais que foram criados na primeira execução são sobrepostos pelas palavras dos novos arquivos. Assim, não são usados documentos que dizem respeito à execução anterior.
a
