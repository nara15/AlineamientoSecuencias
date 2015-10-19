#ifndef ALIGN_H_INCLUDED
#define ALIGN_H_INCLUDED

typedef struct twoStrings Alignment;

struct twoStrings
{
    char *first;
    char *second;
};

Alignment align(char *seq1, char *seq2, int gapInit, int gapXtnd);


#endif // ALIGN_H_INCLUDED
