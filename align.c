#ifndef ALIGN_C_INCLUDED
#define ALIGN_C_INCLUDED

/*Align.c
  by Cyrus Wilson
  Simple Implementation of Needleman-Wunsch algorithm for aligning sequences*/

/*Note that to keep this at least somewhat understandable this implementation
  leaves error-checking up to the program using it!*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "align.h"


/*pointers to locations in the matrix will not be stored as absolute memory
  locations but instead as array indices in case one needs to resize the array
  in which case it might be moved in memory*/

typedef struct pair Point;

struct pair {
  int x;
  int y;
};

/*functions called by align to do dirty work*/


/*matrixInit allocates a two-dimensional array for the similarity/sum matrix
  and sets values to zero*/

int **matrixInit(int dim1, int dim2) {
  int i, j; /*iterators*/
  int **array = (int **) malloc(dim1 * sizeof(int *));

  for(i = 0; i < dim1; i++) {
    array[i] = (int *) malloc(dim2 * sizeof(int));

    for(j = 0; j < dim2; j++)
      array[i][j] = 0;  /*init to zero*/
  }

  return(array);
}


/*For educational purposes only, printMatrix prints the contents of matrix
  of dimensions dim1 and dim2 to stdout. It is only useful for small matrices
  of small numbers.*/

void printMatrix(int **matrix, int dim1, int dim2) {
  int i, j; /*iterators*/

  printf("%i x %i\n", dim1, dim2);

  for(i = 0; i < dim1; i++) {
    for(j = 0; j < dim2; j++)
      printf("%i ", matrix[i][j]);
    printf("\n");
  }
}


/*ptrMatrixInit just makes the empty 2D array for pointers corresponding to
  optimal alignments in the sum matrix*/

Point **ptrMatrixInit(int dim1, int dim2) {
  int i; /*iterator*/
  Point **ptrArray = (Point **) malloc(dim1 * sizeof(Point *));

  for(i = 0; i < dim1; i++)
    ptrArray[i] = (Point *) malloc(dim2 * sizeof(Point));

  return(ptrArray);
}


/*deleteMatrix takes an array of pointers to blocks (in essence a 2D array) and
  the length of the array of pointers.  It frees the blocks referred to by the
  pointers and then frees the array of pointers.*/

void deleteMatrix(void **matrix, int length) {
  int i;  /*iterator*/

  for(i = 0; i < length; i++)
    free(matrix[i]);

  free(matrix);
}

/*similarity takes an empty matrix, the sequences, and their lengths, and
  sets values in the matrix corresponding to matches to 1.
  Note that this is archaic; a modern version of this function would take a
  substitution matrix and assign values to amino acid substitutions based on
  the substitution matrix.
  Also note that it would be more efficient in this case to combine calculation
  of similarity and sum matrix to reduce iterations through the array, but this
  implementation is more for understanding; it follows the conceptual
  construction of the dot matrix*/

void similarity(int **matrix, char *seq1, int len1, char *seq2, int len2) {
  int i, j; /*iterators*/

  for(i = 0; i < len1; i++)
    for(j = 0; j < len2; j++)
      if(seq1[i] == seq2[j])
        matrix[i][j] = 1;
}


/*prevMax is used by sumMatrix to look through the sumMatrix as it is being
  created to find the optimal alignment up to the location specified by loc1
  and loc2.  Note that prevMax does NOT take gap penalties into account when
  finding the best previous alignment, which causes problems if gap penalties
  are too large, such as when the factors are integers (like in this
  implementation!)*/

Point prevMax(int **matrix, int dim1, int dim2, int ind1, int ind2) {
  Point maxPoint; /*to store candidate for optimal alignment*/
  int i, j;       /*iterators*/

  maxPoint.x = ind1 + 1;  /*start with down+right candidate*/
  maxPoint.y = ind2 + 1;

  i = ind1 + 1;
  for(j = dim2 - 1; j > ind2; j--) {
    if(matrix[i][j] > matrix[maxPoint.x][maxPoint.y]) {
      maxPoint.x = i;
      maxPoint.y = j;
    }
  }

  j = ind2 + 1;
  for(i = dim1 - 1; i > ind1; i--) {
    if(matrix[i][j] > matrix[maxPoint.x][maxPoint.y]) {
      maxPoint.x = i;
      maxPoint.y = j;
    }
  }

  return(maxPoint);
}


/*gapPenalty calculates the gap penalty between the amino acid pair specified
  by x and y and that specified by pair2 using the linear function
  penalty = g+lx where init is g, the penalty for opening a gap; xtnd is l,
  the factor for elongating the gap; and x is the gap length. Note that
  parameters are limited to integers.*/

int gapPenalty(int init, int xtnd, int x, int y, Point pair2) {
  int gapLength;                  /*store gapLength*/
  int penalty;                    /*store penalty*/

  gapLength = pair2.x - (x + 1);  /*if pair2.x is x+1 then no gap*/
  gapLength += pair2.y - (y + 1); /*gap is only in one sequence, so either this
                                    or the previous statement adds 0 to length*/
  penalty = gapLength * xtnd;
  penalty += init;
  return(penalty);
}


/*sumMatrix takes a similarity matrix, the dimensions, gap init penalty, and gap
  extend penalty, and an empty Point matrix. It returns a Point referring
  to the element in the sum matrix with the maximum score.
  Note that the sum matrix itself instead of just being an int matrix could have
  structs that would also contain the "pointers" to previous optimal alignments,
  but instead I store them in a separate matrix with the same dimensions.*/

Point sumMatrix(int **matrix, int dim1, int dim2, int gapInit, int gapXtnd, Point **ptrs) {
  int i, j, k;    /*iterators*/
  int maxDim;     /*stores bigger dimension*/

  if(dim2 > dim1) /*could use the max macro/template (depending on C compiler)*/
    maxDim = dim2;/*but what if yours doesn't have a max?!*/
  else
    maxDim = dim1;

  for(k = 0; k < maxDim; k++) {
    i = dim1 - (k + 1);
    for(j = dim2 - 1; (j > (dim2 - (k + 1))) && (j >= 0) && (i >= 0); j--) {
      if((i + 1 < dim1) && (j + 1 < dim2)) {  /*value of edge elements doesn't change*/
        ptrs[i][j] = prevMax(matrix, dim1, dim2, i, j); /*point to old optimal*/
        matrix[i][j] += matrix[ptrs[i][j].x][ptrs[i][j].y]; /*add to old max*/
        matrix[i][j] -= gapPenalty(gapInit, gapXtnd, i, j, ptrs[i][j]);
      } else {    /*if an edge, set max pointer to (0,0) so traceback knows
                    when to stop*/
        ptrs[i][j].x = ptrs[i][j].y = 0;
      }
    }

    j = dim2 - (k + 1); /*do same thing vertically as did horizontally*/
    for(i = dim1 - 1; (i >= (dim1 - (k + 1))) && (i >= 0) && (j >= 0); i--) {
      if((i + 1 < dim1) && (j + 1 < dim2)) {  /*value of edge elements doesn't change*/
        ptrs[i][j] = prevMax(matrix, dim1, dim2, i, j); /*point to old optimal*/
        matrix[i][j] += matrix[ptrs[i][j].x][ptrs[i][j].y]; /*add to old max*/
        matrix[i][j] -= gapPenalty(gapInit, gapXtnd, i, j, ptrs[i][j]);
      } else {    /*if an edge, set max pointer to (0,0) so traceback knows
                    when to stop*/
        ptrs[i][j].x = ptrs[i][j].y = 0;
      }
    }
  }

  return(prevMax(matrix, dim1, dim2, -1, -1));  /*return pointer to end of best
                                                  alignment*/
}


/*traceBack takes a sumMatrix's dimensions, the strings representing the
  sequences (for constructing the alignment), the pointers from each element
  to best previous alignments, and a start pointer pointing to the end of the
  best alignment. It traces back along the optimum path beginning at start and
  returns the optimum alignment.*/

Alignment traceBack(int dim1, int dim2, char *seq1, char *seq2, Point **ptrMatrix, Point start) {
  int strSize;          /*keep track of size of alignment strings*/
  Alignment alignStrs;  /*store alignment as it is constructed*/
  Point nextPos;        /*store next position in the matrix*/
  int i, j, k;          /*iterators*/

  if(dim2 > dim1)       /*enough room for longer sequence plus '\0'*/
    strSize = dim2 + 1;
  else
    strSize = dim1 + 1;

  i = start.x;          /*set position to start of best alignment*/
  j = start.y;
  k = 0;                /*k keeps track of position within strings*/

  alignStrs.first = (char *) malloc(strSize * sizeof(char));
  alignStrs.second = (char *) malloc(strSize * sizeof(char));


  if(i > 0) {           /*initial gap on second sequence*/
    strSize += i;       /*make more than enough space to include gap*/
    alignStrs.first = realloc(alignStrs.first, strSize * sizeof(char));
    alignStrs.second = realloc(alignStrs.second, strSize * sizeof(char));

    i = 0;
    while(i < start.x) {
      alignStrs.first[k] = seq1[i++];
      alignStrs.second[k++] = '-';
    }
  } else if(j > 0) {    /*initial gap on first sequence*/
    strSize += j;
    alignStrs.first = realloc(alignStrs.first, strSize * sizeof(char));
    alignStrs.second = realloc(alignStrs.second, strSize * sizeof(char));

    j = 0;
    while(j < start.y) {
      alignStrs.second[k] = seq2[j++];
      alignStrs.first[k++] = '-';
    }
  }

  while(i < dim1 && j < dim2) {/*trace through matrix until edge*/

    nextPos = ptrMatrix[i][j];    /*get pointer to next position in matrix*/

    alignStrs.first[k] = seq1[i++]; /*set each position to proper residue*/
    alignStrs.second[k++] = seq2[j++];

    while(i < nextPos.x) {        /*if gap in second sequence, fill in*/
      alignStrs.first[k] = seq1[i++];
      alignStrs.second[k++] = '-';
    }

    while(j < nextPos.y) {        /*if gap in first sequence, fill in*/
      alignStrs.second[k] = seq2[j++];
      alignStrs.first[k++] = '-';
    }
  }

  if(i < dim1) {                  /*terminal gap on second sequence*/
    strSize += dim1 - i;          /*need enough space to contain terminal gap*/
    alignStrs.first = realloc(alignStrs.first, strSize * sizeof(char));
    alignStrs.second = realloc(alignStrs.second, strSize * sizeof(char));

    while(i < dim1) {
      alignStrs.first[k] = seq1[i++];
      alignStrs.second[k++] = '-';
    }

  } else if(j < dim2) {           /*terminal gap on first sequence*/
    strSize += dim2 - j;          /*need enough space to contain terminal gap*/
    alignStrs.first = realloc(alignStrs.first, strSize * sizeof(char));
    alignStrs.second = realloc(alignStrs.second, strSize * sizeof(char));

    while(j < dim2) {
      alignStrs.second[k] = seq2[j++];
      alignStrs.first[k++] = '-';
    }
  }

  alignStrs.first[k] = alignStrs.second[k] = '\0';  /*null-terminate strings*/

  return(alignStrs);
}


/*align takes two null-terminated strings, a gap initialization penalty,
  and a gap extension penalty.  It returns the Needleman-Wunsch alignment
  of the two strings.*/

Alignment align(char *seq1, char *seq2, int gapInit, int gapXtnd) {
  int **matrix; 				/*to point to similarity/sum matrix*/
                        /*might want to use char instead to save memory, but
                          I use int here because by definition it is supposed to
                          be the fastest & also allows larger scores for larger
                          sequences*/
  Point **ptrMatrix;    /*to store pointers to previous optimal alignments*/
  Point bestAlignment;  /*store pointer to end of optimal alignment*/
  int length1, length2; /*store sequence lengths so don't have to recalc*/
  Alignment result;     /*store the alignment returned by traceBack*/

  length1 = strlen(seq1);
  length2 = strlen(seq2);

  matrix = matrixInit(length1, length2);  /*make empty matrix for sequences*/
  ptrMatrix = ptrMatrixInit(length1, length2);  /*make empty pointer matrix*/
  similarity(matrix, seq1, length1, seq2, length2);/*construct similarity matrix*/
  /*printf("\nSimilarity Matrix:\n");
    printMatrix(matrix, length1, length2);*/
  bestAlignment = sumMatrix(matrix, length1, length2, gapInit, gapXtnd, ptrMatrix);
  /*printf("\nSum Matrix:\n");
    printMatrix(matrix, length1, length2);
    printf("\nAlignment:\n");*/
  result = traceBack(length1, length2, seq1, seq2, ptrMatrix, bestAlignment);

  deleteMatrix((void **) matrix, length1);          /*clean up*/
  deleteMatrix((void **) ptrMatrix, length1);

  return(result);                         /*return the alignment*/
}
#endif // ALIGN_C_INCLUDED
