#ifndef NEEDLEMAN_WUNSCH_H_INCLUDED
#define NEEDLEMAN_WUNSCH_H_INCLUDED

typedef aligner_t nw_aligner_t;

//MÉTODOS ABSTRACTOS PARA EL ALINEAMIENTO
nw_aligner_t* needleman_wunsch_new();
void needleman_wunsh_free(nw_aligner *nw);
void needleman_wunsh_align(const char *a, const char *b,
                           const scoring_t *scoring);

#endif // NEEDLEMAN_WUNSCH_H_INCLUDED
