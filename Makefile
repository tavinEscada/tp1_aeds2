compile: src/palavra.c src/hash.c src/patricia.c src/infoDocs.c src/tp.c src/main.c
	gcc src/palavra.c src/hash.c src/patricia.c src/infoDocs.c src/tp.c src/main.c -Wall -Wextra -g -o main
