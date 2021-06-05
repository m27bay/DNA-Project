#include "sequence.h"

void afficherSequence(const sequence_t* tableauSequence, const int8_t taille) {
    //
    if (!tableauSequence) {
        printf("ERREUR : Dans le fichier 'sequence.c'. Dans la fonction 'afficherSequence'. Pointeur nul.\n");
        exit(EXIT_FAILURE);
    }

    //
    printf("Affichage sequence :\n");
    for (int8_t position = 0; position < taille; position++) {
        printf("\t%s.\n", tableauSequence[position].chaine);
    }
    printf("Fin sequence.\n");
}

void libereSequence(sequence_t* tableauSequence, const int8_t taille) {
    //
    if (!tableauSequence) {
        printf("ERREUR : Dans le fichier 'sequence.c'. Dans la fonction 'libereSequence'. Pointeur nul.\n");
        exit(EXIT_FAILURE);
    }

    //
    for (int8_t position = 0; position < taille; position++) {
        free(tableauSequence[position].chaine);
    }

    //
    free(tableauSequence);
}

u_int8_t calculDistanceEdition(const sequence_t s, const sequence_t s2) {

}