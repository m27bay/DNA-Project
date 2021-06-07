#include "lire.h"

sequence_t* lireFichier(const char* nomFichier, int8_t* tailleTableau) {
    //
    if (!nomFichier) {
        printf("ERREUR : Dans le fichier 'lire.c'. Dans la fonction 'lireFichier'. Pointeur nul.\n");
        exit(EXIT_FAILURE);
    }

    //
    sequence_t* tableauSeq = malloc(TAILLECHAINE * sizeof(sequence_t));
    if (!tableauSeq) {
        printf("ERREUR : Dans le fichier 'lire.c'. Dans la fonction 'lireFichier'. Pointeur nul.\n");
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
        char chaineLu[TAILLECHAINE] = "";
        
        //
        while(fgets(chaineLu, TAILLECHAINE, fichier) != NULL) {
            //
            size_t tailleChaineLu = strlen(chaineLu);
            tableauSeq[positionSeq].taille = tailleChaineLu - 1;
            tableauSeq[positionSeq].chaine = malloc(tableauSeq[positionSeq].taille + 1 * sizeof(char));
            if (!tableauSeq[positionSeq].chaine) {
                printf("ERREUR : Dans le fichier 'lire.c'. Dans la fonction 'lireFichier'. Pointeur nul.\n");
                exit(EXIT_FAILURE);
            }

            strncpy(tableauSeq[positionSeq].chaine, chaineLu, tailleChaineLu - 1);
            tableauSeq[positionSeq].chaine[tableauSeq[positionSeq].taille] = '\0';
            positionSeq++;
        }

        //
        fclose(fichier);
        *tailleTableau = positionSeq;
    } else {
        //
        printf("ERREUR : Dans le fichier 'lire.c'. Dans la fonction 'lireFichier'. Impossible d'ouvrir le fichier.\n");
        exit(EXIT_FAILURE);
    }

    return tableauSeq;
}