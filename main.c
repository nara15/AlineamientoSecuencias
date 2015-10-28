
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
//#include "align.h"


#include "alineamientos/needleman_wunsch.c"

//NEEDLEMAN WUNSCH ALGORITHM

int main() {
    char str1[] = "GCATGCU";
    char str2[] = "GATTACA";

    needleman_wunsch(str1, str2);

    return 0;

/*
    //Tamaños de las hileras (secuencias)
    char str1[] = "ATTGTGATCC";
    char str2[] = "TTGCATCGGC";
    int dimString1 = sizeof(str1)/sizeof(str1[0]);
    int dimString2 = sizeof(str2)/sizeof(str2[0]);
    //Gap penalty, match, mismatch
    int GAP_PENALTY = -2;
    int MATCH = 1;
    int MISMATCH = -1;

    int table[dimString1 + 1][dimString2 + 1], i, j;

    //Iniciar la matriz para las hileras
    for (i = 0; i <= dimString1; i ++)
    {
        table[i][0] = i * GAP_PENALTY;
    }
    for (j = 0; j <= dimString2; j ++)
    {
        table[0][j] = j * GAP_PENALTY;
    }

    //Algoritmo Needleman-Wunsch
    int s,a,b,c;

    for (i = 1; i <= dimString1; i ++)
    {
        for (j = 1; j <= dimString2; j ++)
        {
            if (str1[j - 1] == str2[i - 1])
            {
                s = MATCH;
            }
            else
            {
                s = MISMATCH;
            }

            a = table[i - 1][j - 1] + s;
            b = table[i][j - 1] + GAP_PENALTY;
            c = table[i - 1][j] + GAP_PENALTY;

            table[i][j] = maximum(a, b, c);
        }
    }
    printf("%i", table[10][10]);
*/

    /*
    char *sequence1, *sequence2;  //store sequences returned by loadSequence
    int gapInit, gapXtnd;         //store gap penalty factors
    Alignment result;             //store result obtained from align

    sequence1 = loadSequence("hola1.seq");
    sequence2 = loadSequence("hola2.seq");

    if(!(sequence1 && sequence2))
    {
        fprintf(stderr, "Error reading sequences\n");
        exit(EXIT_FAILURE);
    }

    gapInit = 0;
    gapXtnd = 0;

    if(gapInit < 0)
    {
        fprintf(stderr, "%i is invalid gap opening penalty\n", gapInit);
        exit(EXIT_FAILURE);
    }

    if(gapXtnd < 0)
    {
        fprintf(stderr, "%i is invalid gap elongation factor\n", gapXtnd);
        exit(EXIT_FAILURE);
    }

    result = align(sequence1, sequence2, gapInit, gapXtnd);

    free(sequence1);
    free(sequence2);

    printAlignment(result, 79);

    free(result.first);
    free(result.second);*/
}
