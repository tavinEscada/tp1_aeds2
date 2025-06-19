/**
 * @author Beatriz Queiroz - 5890
 * @author Heitor Porto - 5895
 * @author Pâmela Lúcia - 5898
 * @author Júlio César - 5903
 * @author Otávio Tavares - 5912
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#include "../include/tp.h"

// Variavies Globais para comparaçao da Hash
unsigned long long int comp_insercao_hash = 0;
unsigned long long int comp_busca_hash = 0;

int main(){
    setlocale(LC_ALL, "C.UTF-8");
    menu();
    return 0;

}
