compile: include/palavra.h include/hash.h include/patricia.h include/infoDocs.h include/tp.h src/palavra.c src/hash.c src/patricia.c src/infoDocs.c src/tp.c src/main.c
	gcc include/palavra.h include/hash.h include/patricia.h include/infoDocs.h include/tp.h src/palavra.c src/hash.c src/patricia.c src/infoDocs.c src/tp.c src/main.c -Wall -Wextra -g -o main
