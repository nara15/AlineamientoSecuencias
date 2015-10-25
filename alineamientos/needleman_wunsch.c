#ifndef NEEDLEMAN_WUNSCH_C_INCLUDED
#define NEEDLEMAN_WUNSCH_C_INCLUDED

#include "needleman_wunsch.h"
/*
*   Función encargada de iniciar la matriz para el alineamiento
*/
int** iniciarMatriz (int pCantFilas, int pCantColumnas)
{
    int **matriz = (int **)malloc(pCantFilas * sizeof(int *));
    int i, j;
    for (i = 0; i < pCantFilas; i ++)
    {
        matriz[i] = (int *)malloc(pCantColumnas * sizeof(int));
    }

    //Inicializar la matriz con los valores iniciales
    for (i = 0; i <= pCantFilas; i ++)
    {
        matriz[i][0] = i * GAP_PENALTY;
    }
    for (j = 0; j <= pCantColumnas; j ++)
    {
        matriz[0][j] = j * GAP_PENALTY;
    }

    return matriz;
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



//Función para el alineamiento global usando NEEDLEMAN_WUNSH
void needleman_wunsch(char *pSeq1, char *pSeq2)
{
    int **matrix = iniciarMatriz(10, 10);

    printf("%i", matrix[0][0]);

    //eliminarMatriz(matrix, 10);

}

#endif // NEEDLEMAN_WUNSCH_C_INCLUDED
