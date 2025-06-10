compile: src/hash.c src/Palavra.c src/patricia.c src/main.c
		gcc -o bin/main src/hash.c src/Palavra.c src/patricia.c src/main.c -g -Wall
