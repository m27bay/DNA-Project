#include "src/lib/manipulation.h"

int main(void) {
    sequence_t* tableauSequence = NULL;
    int8_t tailleTableau = 0;
    tableauSequence = lireFichier("sequence.txt", &tailleTableau);
    afficherSequence(tableauSequence, tailleTableau);
    libereSequence(tableauSequence, tailleTableau);

    //
    sequence_t s = {"ACGT", 4};
    sequence_t s2 = {"AGA", 3};
    printf("D(%s, %s) = %.2f\n", s.chaine, s2.chaine, calculDistanceEdition(s, s2));

    return 0;
}