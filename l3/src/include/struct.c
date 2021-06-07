#include "struct.h"

void afficherSequence(const sequence_t* tableauSequence, const u_int8_t taille) {
    printf("Affichage sequence :\n");
    for (size_t position = 0; position < taille; position++) {
        printf("\t%s, taille : %d.\n", tableauSequence[position].chaine, tableauSequence[position].taille);
    }
    printf("Fin sequence.\n");
}

void libereSequence(sequence_t* tableauSequence, const u_int8_t taille) {
    for (size_t position = 0; position < taille; position++) {
        free(tableauSequence[position].chaine);
    }
    free(tableauSequence);
}