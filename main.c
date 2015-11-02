
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>


#include "readFile.c"
#include "alineamientos/needleman_wunsch.c"
#include "alineamientos/waterman_smith.c"

//NEEDLEMAN WUNSCH ALGORITHM

int main() {
/*
    char *sequence1, *sequence2;
    sequence1 = loadSequence("hola1.seq");
    sequence2 = loadSequence("hola2.seq");

    if(!(sequence1 && sequence2)) {
        fprintf(stderr, "Error al leer las secuencias\n");
        exit(EXIT_FAILURE);
    }

    needleman_wunsch(sequence1, sequence2);

    free(sequence1);
    free(sequence2);
*/
    char *sequence1, *sequence2;
    sequence1 = loadSequence("smith1.seq");
    sequence2 = loadSequence("smith2.seq");

    if(!(sequence1 && sequence2)) {
        fprintf(stderr, "Error al leer las secuencias\n");
        exit(EXIT_FAILURE);
    }

    waterman_smith(sequence1, sequence2);

    free(sequence1);
    free(sequence2);
    return 0;

}
