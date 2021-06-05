#include "lire.h"

sequence_t* lireFichier(const char* nomFichier, int8_t* tailleTableau) {
    //
    if (!nomFichier) {
        printf("ERREUR : Dans le fichier 'lire.c'. Dans la fonction 'initialiserSequence'. Pointeur nul.\n");
        exit(EXIT_FAILURE);
    }

    //
    sequence_t* tableauSeq = malloc(TAILLECHAINE * sizeof(sequence_t));
    if (!tableauSeq) {
        printf("ERREUR : Dans le fichier 'lire.c'. Dans la fonction 'initialiserSequence'. Pointeur nul.\n");
        exit(EXIT_FAILURE);
    }

    //
    FILE* fichier = NULL;
    fichier = fopen(nomFichier, "r");
    
    //
    u_int8_t positionSeq = 0;

    //
    if (fichier) {
        //
        char chaineLu[TAILLECHAINE];
        
        //
        while(fgets(chaineLu, TAILLECHAINE, fichier) != NULL) {
            //
            tableauSeq[positionSeq].taille = strlen(chaineLu);
            tableauSeq[positionSeq].chaine = malloc(tableauSeq[positionSeq].taille * sizeof(char));
            chaineLu[strlen(chaineLu) - 1] = '\0';
            strcpy(tableauSeq[positionSeq].chaine, chaineLu);
            positionSeq++;
        }

        //
        fclose(fichier);
        *tailleTableau = positionSeq;
    } else {
        //
        printf("ERREUR : Dans le fichier 'lire.c'. Dans la fonction 'initialiserSequence'. Impossible d'ouvrir le fichier.\n");
        exit(EXIT_FAILURE);
    }

    return tableauSeq;
}