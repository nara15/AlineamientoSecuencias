#ifndef NEEDLEMAN_WUNSCH_H_INCLUDED
#define NEEDLEMAN_WUNSCH_H_INCLUDED

#define GAP_PENALTY -2
#define MATCH 1
#define MISMATCH -1

/*
* Estructura que contiene las dos hileras alineadas
*/
typedef struct dosHileras Alignment;
struct dosHileras
{
    char *primera;
    char *segunda;
};

/*
* Declaración de la función para hacer el alineamiento global
*/
void needleman_wunsh(char *pSeq1, char *pSeq2);


#endif // NEEDLEMAN_WUNSCH_H_INCLUDED
