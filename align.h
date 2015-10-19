#ifndef ALIGN_H_INCLUDED
#define ALIGN_H_INCLUDED


/*A string alignment is stored in a structure of two strings. When
  printing this information, one might want to output the second string
  two lines under the first, with the line in between containing a | any
  time that first[i] == second[i]*/

typedef struct twoStrings Alignment;

struct twoStrings {
  char *first;
  char *second;
};

/*align takes two null-terminated strings, a gap initialization penalty,
  and a gap extension penalty.  It returns the Needleman-Wunsch alignment
  of the two strings.*/

Alignment align(char *seq1, char *seq2, int gapInit, int gapXtnd);


#endif // ALIGN_H_INCLUDED
