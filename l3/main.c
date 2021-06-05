#include "src/lib/sequence.h"

int main(void) {
    sequence_t* tableauSequence = NULL;
    int8_t tailleTableau = 0;
    tableauSequence = lireFichier("sequence.txt", &tailleTableau);
    afficherSequence(tableauSequence, tailleTableau);
    libereSequence(tableauSequence, tailleTableau);

    return 0;
}