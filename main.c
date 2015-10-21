/*#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Hello world!\n");
    return 0;
}*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "align.h"


char *loadSequence(char *filename) {
  FILE *seqFile;
  char *seqString;
  int i = 0;
  int fileLength;
  int c;

  if(!(seqFile = fopen(filename, "r"))) {
    fprintf(stderr, "Cannot open file: %s\n", filename);
    return(NULL);
  }

  fseek(seqFile, 0, SEEK_END);
  fileLength = (int) ftell(seqFile);
  if(!fileLength) {
    fclose(seqFile);
    fprintf(stderr, "File %s contains no data\n", filename);
    return(NULL);
  }

  if(fileLength == INT_MAX) {
    fclose(seqFile);
    fprintf(stderr, "Sequence in %s is too long for this program!\n", filename);
    return(NULL);
  }

  seqString = (char *) malloc((fileLength + 1) * sizeof(char));
  rewind(seqFile);

  while((c = fgetc(seqFile)) != EOF)
    if(isalpha(c))
      seqString[i++] = (char) toupper(c);

  fclose(seqFile);

  seqString[i] = '\0';
  return(seqString);
}


/*printAlignment takes an Alignment and the number of columns on the output
  display; it prints out the alignment in three line format, wrapping as
  necessary, to stdout.  For example:
  ABCNY-
  | | |
  AYC-YN
  */

void printAlignment(Alignment result, int cols) {
  int Length;
  int i;
  char *matches;
  char *oneLine;

  if(cols < 1) {
    fprintf(stderr, "%i is an invalid number of output columns.", cols);
    return;
  }

  if(!(result.first && result.second)) {
    fprintf(stderr, "Invalid alignment specified to printAlignment.");
    return;
  }

  Length = strlen(result.first);

  if(!Length) {
    fprintf(stderr, "Empty alignment specified to printAlignment.");
    return;
  }

  matches = (char *) malloc((Length + 1) * sizeof(char));
  for(i = 0; i < Length; i++) {
    if(result.first[i] == result.second[i])
      matches[i] = '|';
    else
      matches[i] = ' ';
  }
  matches[Length] = '\0';

  oneLine = (char *) malloc((cols + 1) * sizeof(char));

  for(i = 0; i < Length; i += cols) {
    strncpy(oneLine, &(result.first[i]), cols);
    oneLine[cols] = '\0';
    printf("%s\n", oneLine);
    strncpy(oneLine, &(matches[i]), cols);
    oneLine[cols] = '\0';
    printf("%s\n", oneLine);
    strncpy(oneLine, &(result.second[i]), cols);
    oneLine[cols] = '\0';
    printf("%s\n\n", oneLine);
  }

  free(matches);
  free(oneLine);
}


/*NWalign takes four arguments: gap initiation penalty, gap extension penalty,
  sequence 1 filename, and sequence 2 filename.  Note that the length of
  an input sequence must fit within an int for the architecture on which this
  is compiled; otherwise the program will reject the file and quit.  In addition
  the gap penalty parameters must be integers, which makes them rather useless*/


//NEEDLEMAN WUNSCH ALGORITHM

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



void main() {

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
