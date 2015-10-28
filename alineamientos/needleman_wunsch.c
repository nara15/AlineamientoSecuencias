#ifndef NEEDLEMAN_WUNSCH_C_INCLUDED
#define NEEDLEMAN_WUNSCH_C_INCLUDED

#include <string.h>
#include "needleman_wunsch.h"

/*
*   Función encargada de iniciar la matriz para el alineamiento
*/
int **iniciarMatriz(int dim1, int dim2) {
    int i, j;
    int **array = (int **) malloc(dim1 * sizeof(int *));
    for(i = 0; i < dim1; i++) {
            array[i] = (int *) malloc(dim2 * sizeof(int));
    }
    for (i = 0; i < dim1; i ++)
    {
        array[i][0] = i * GAP_PENALTY;
    }
    for (j = 0; j < dim2; j ++)
    {
        array[0][j] = j * GAP_PENALTY;
    }
    return(array);
}

/*
*   Función para liberar la memoria solcitada para la matriz
*/
void eliminarMatriz (int **pMatriz, int pDim)
{
    int i;
    for(i = 0; i < pDim; i++)
        free(pMatriz[i]);

    free(pMatriz);
}

int maximum(int a, int b, int c)
{
    int max;
    if (a > b && a > c)
    {
        max = a;
    }
    else
    {
        if ( b > c)
        {
            max = b;
        }
        else
        {
            max = c;
        }
    }
    return max;
}


/*
*   Función para el alineamiento global usando NEEDLEMAN_WUNSH
*/
void needleman_wunsch(char *pSeq1, char *pSeq2)
{
    //Inicialización de la matriz
    int dimSeq1 = strlen(pSeq1);
    int dimSeq2 = strlen(pSeq2);
    int **table = iniciarMatriz(dimSeq1 + 1, dimSeq2 + 1);

    //Algoritmo Needleman-Wunsch
    int s,a,b,c;
    int i, j;
    for (i = 1; i <= dimSeq1; i ++)
    {
        for (j = 1; j <= dimSeq2; j ++)
        {
            if (pSeq1[j - 1] == pSeq2[i - 1])
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
    /*
    *   Algoritmo de Traceback
    */

    int  stringSize;
    Alignment alineamiento;

    if (dimSeq1 > dimSeq2)
    {
        stringSize = dimSeq1 + 1;
    }else{
        stringSize = dimSeq2 + 1;
    }

    i = dimSeq1;
    j = dimSeq2;
    s = 0;
    int k = 0;

    while (i > 0 | j > 0)
    {
        if (pSeq1[j - 1] == pSeq2[i - 1])
        {
            s = MATCH;
        }
        else
        {
            s = MISMATCH;
        }

        //Inicio oficial del algoritmo
        if ( (i > 0) && (j > 0) && (table[i][j] == table[i - 1][j - 1] + s))
        {
            //printf("%i\t", table[i][j]);
            printf("%c", pSeq1[i - 1]);
            printf("%c\n", pSeq2[j - 1]);
            i --;
            j --;
        }
        else {
            if ( (i > 0) && (table[i][j] == table[i - 1][j] + GAP_PENALTY))
            {
                //printf("%i, %i\n", table[i][j], table[i - 1][j] + GAP_PENALTY);
                printf("%c", pSeq1[i - 1]);
                printf("%c\n", '*');
                i --;
            }
            else {
                //printf("%i, %i\n", table[i][j], table[j][j - 1] + GAP_PENALTY);
                printf("%c", '*');
                printf("%c\n", pSeq2[j - 1]);
                j --;
            }
        }
    }

    printf("%i", table[dimSeq1][dimSeq2]);


    //Liberar la memoria de la matriz
    eliminarMatriz(table, dimSeq1 + 1);
}

#endif // NEEDLEMAN_WUNSCH_C_INCLUDED
