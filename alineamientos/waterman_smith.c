#include <string.h>
#include "waterman_smith.h"

//VARIABLES GLOBALES
int highScore;
int highScorePos[2];

/*
*   Función encargada de iniciar la matriz para el alineamiento
*/
int **iniciarMatrizSW(int dim1, int dim2) {
    int i, j;
    int **array = (int **) malloc(dim1 * sizeof(int *));
    for(i = 0; i < dim1; i++) {
            array[i] = (int *) malloc(dim2 * sizeof(int));
    }
    for (i = 0; i < dim1; i ++)
    {
       array[i][0] = 0;
       //array[i][0] = i * GAP_PENALTY;
    }
    for (j = 0; j < dim2; j ++)
    {
       array[0][j] = 0;
       //array[0][j] = j * GAP_PENALTY;
    }
    return(array);
}
/*
*   Función para liberar la memoria solcitada para la matriz
*/
void eliminarMatrizSW (int **pMatriz, int pDim)
{
    int i;
    for(i = 0; i < pDim; i++)
        free(pMatriz[i]);

    free(pMatriz);
}

int maximumSW(int a, int b, int c)
{
    int max;
    if (a > b && a > c && a > 0)
    {
        max = a;
    }
    else
    {
        if ( b > c && b > 0)
        {
            max = b;
        }
        else
        {
            if (c > 0)
            {
                max = c;
            }
            else
            {
                max = 0;
            }
        }
    }
    return max;
}



void waterman_smith (char *pSeq1, char *pSeq2)
{
    //Inicialización de la matriz
    int dimSeq1 = strlen(pSeq1);
    int dimSeq2 = strlen(pSeq2);
    int **table = iniciarMatrizSW(dimSeq1 + 1, dimSeq2 + 1);

    //Algoritmo Waterman-Smith
    int s, a, b, c;
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

            table[i][j] = maximumSW(a, b, c);
        }
    }
/*
    printf("\n");
    for (i = 0; i < dimSeq1 + 1; i++)
    {
        for (j = 0; j < dimSeq2 + 1; j++)
        {
            printf("%i ", table[i][j]);
        }
        printf("\n");
    }
    printf("\n");
*/
    //Hallando el máximo valor de la matriz
    for (i = 1; i < dimSeq1 + 1; i++)
    {
        for (j = 1; j < dimSeq2 + 1; j++)
        {
            if (table[i][j] > highScore)
            {
                highScore = table[i][j];
                highScorePos[0] = i;
                highScorePos[1] = j;
            }
        }
    }


    //Algoritmo de Traceback
    i = highScorePos[0];
    j = highScorePos[1];

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
            printf("%c", pSeq1[i - 1]);
            printf("%c\n", pSeq2[j - 1]);
            i --;
            j --;
        }
        else {
            if ( (i > 0) && (table[i][j] == table[i - 1][j] + GAP_PENALTY))
            {
                printf("%c", pSeq1[i - 1]);
                printf("%c\n", '*');
                i --;
            }
            else {
                printf("%c", '*');
                printf("%c\n", pSeq2[j - 1]);
                j --;
            }
        }
    }


    //Liberar la memoria de la matriz
    eliminarMatrizSW(table, dimSeq1 + 1);

}
