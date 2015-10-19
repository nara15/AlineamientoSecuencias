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

void main() {

  char *sequence1, *sequence2;  /*store sequences returned by loadSequence*/
  int gapInit, gapXtnd;         /*store gap penalty factors*/
  Alignment result;             /*store result obtained from align*/

/*  if(argc != 5) {
    fprintf(stderr, "Invalid arguments specified\n");
    printf("Usage:  NWalign seqfile1 seqfile2 gapInit gapXtnd\n");
    printf("  where seqfile1 and seqfile 2 are files containing alphabetic sequences,\n");
    printf("  gapInit is gap opening penalty, and gapXtnd is gap elongation factor.\n\n");
    printf("Example:  NWalign protein1.seq protein2.seq 0 0\n");
    exit(EXIT_FAILURE);
  }*/

//  sequence1 = loadSequence(argv[1]);
//  sequence2 = loadSequence(argv[2]);
    sequence1 = loadSequence("hola1.seq");
    sequence2 = loadSequence("hola2.seq");

  if(!(sequence1 && sequence2)) { /*error reading sequences*/
    fprintf(stderr, "Error reading sequences\n");
    exit(EXIT_FAILURE);
  }

  gapInit = 0;//atoi(argv[3]);
  gapXtnd = 0;//atoi(argv[4]);

  if(gapInit < 0) {               /*invalid gap opening penalty*/
    fprintf(stderr, "%i is invalid gap opening penalty\n", gapInit);
    exit(EXIT_FAILURE);
  }

  if(gapXtnd < 0) {               /*invalid gap extension factor*/
    fprintf(stderr, "%i is invalid gap elongation factor\n", gapXtnd);
    exit(EXIT_FAILURE);
  }

  result = align(sequence1, sequence2, gapInit, gapXtnd);

  free(sequence1);                /*sequence strings no longer needed*/
  free(sequence2);

  printAlignment(result, 79);     /*print out the alignment*/

  free(result.first);             /*clean up*/
  free(result.second);
}
