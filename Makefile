compile: src/Palavra.c src/hash.c src/patricia.c src/infoDocs.c src/tp.c src/main.c
	gcc src/Palavra.c src/hash.c src/patricia.c src/infoDocs.c src/tp.c src/main.c -lm -Wall -Wextra -g -o main
