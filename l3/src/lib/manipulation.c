/**
 * @file manipulation.c
 * @author Le Denmat Mickael
 * @brief Fichier contenant toutes les fonctions principales.
 * @date 2021-06-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "manipulation.h"

/**
 * @brief Tableau des couts.
 * 
 */
float tableauDistance[5][5] = 
    { {0, 2, 1, 2, 1.5},
      {2, 0, 2, 1, 1.5},
      {1, 2, 0, 2, 1.5},
      {2, 1, 2, 0, 1.5},
      {1.5, 1.5, 1.5, 1.5, 0} };

/**
 * @brief Converti un nucleotide en position dans le tableau des couts.
 * 
 * @param nucleotide a convertir.
 * @return u_int8_t la position dans la tableau.
 */
u_int8_t nucleotideEnCase(const char nucleotide) {
    switch (nucleotide) {
        case 'A':
            return 0;
        case 'C':
            return 1;
        case 'G':
            return 2;   
        case 'T':
            return 3;
        case '_':
            return 4;
        default:
            printf("ERREUR : Dans le fichier 'sequence.c'.\n Dans le fonction 'nucleotideEnCase'.\n Nucleotide |%c| inconnu.\n", nucleotide);
            exit(EXIT_FAILURE);
    }
}

/**
 * @brief Affiche le tableau de toutes les distances possibles.
 * 
 * @param matrice des distances.
 * @param tailleX taille de la premiere chaine.
 * @param tailleY taille de la deuxieme chaine.
 */
void afficherMatriceDistance(float** matrice, const u_int8_t tailleX, const u_int8_t tailleY) {
    for (u_int8_t x = 0; x < (tailleX + 1); x++) {
        for (u_int8_t y = 0; y < (tailleY + 1); y++) {
            printf("%.2f ", matrice[x][y]);
        }
        printf("\n");
    } 
}

/**
 * @brief Renvoie le plus petit element parmis trois floattants.
 * 
 * @param a premier floattant.
 * @param b deuxieme floattant.
 * @param c troisieme floattant.
 * @return float le plus petit.
 */
float min(const float a, const float b, const float c) {
    if (a <= b && a <= c) {
        return a;
    } else if (b <= a && b <= c) {
        return b;
    } else {
        return c;
    }
}

/**
 * @brief Initialise la matrice des distances en remplissant la premiere ligne et la premiere colonne, le reste est a zero.
 * 
 * @param matriceDistance a remplir.
 * @param tailleX taille de la premiere chaine.
 * @param tailleY taille de la deuxieme chaine
 */
void initialisationMatriceDistance(float** matriceDistance, const u_int8_t tailleX, const u_int8_t tailleY) {
    // Initialisation.
    for (u_int8_t x = 0; x < (tailleX + 1); x++) {
        for (u_int8_t y = 0; y < (tailleY + 1); y++) {        
            if (x == 0) {
                if (y == 0) {
                    matriceDistance[x][y] = 0;
                } else {
                    matriceDistance[x][y] =  matriceDistance[0][y - 1] + 1.5;
                }
            } else if (y == 0) {
                matriceDistance[x][y] = matriceDistance[x - 1][0] + 1.5;
            } else {
                matriceDistance[x][y] = 0;
            }
        }
    }
}

/**
 * @brief Calcule toutes les distances possibles entre les deux chaines.
 * 
 * @param s la premiere chaine de nucleotide.
 * @param s2 la deuxieme chaine de nucleotide.
 * @return float** le tableau des distances remplis.
 */
float** calculMatriceDistance(const sequence_t s, const sequence_t s2) {
    // Creation de la matrice de distance.
    float** matriceDistance = malloc((s.taille + 1) * sizeof(float*));    
    if (!matriceDistance) {
        printf("ERREUR : Dans le fichier 'sequence.c'. Dans la fonction 'calculMatriceDistance'. Pointeur nul.\n");
        exit(EXIT_FAILURE);
    }

    for (u_int8_t position = 0; position < (s.taille + 1); position++) {        
        matriceDistance[position] = malloc((s2.taille + 1) * sizeof(float));
        if (!matriceDistance[position]) {
            printf("ERREUR : Dans le fichier 'sequence.c'. Dans la fonction 'calculMatriceDistance'. Pointeur nul.\n");
            exit(EXIT_FAILURE);
        }
    }

    // En X s2, en Y s.
    initialisationMatriceDistance(matriceDistance, s.taille, s2.taille);

    // Remplissage des distances.
    for (u_int8_t x = 1; x < (s.taille + 1); x++) {
        for (u_int8_t y = 1; y < (s2.taille + 1); y++) {
            //
            matriceDistance[x][y] = min(
                matriceDistance[x - 1][y - 1] + tableauDistance[nucleotideEnCase(s.chaine[x - 1])][nucleotideEnCase(s2.chaine[y - 1])],
                matriceDistance[x][y-1] + 1.5,
                matriceDistance[x - 1][y] + 1.5
            );
        }
    }

    return matriceDistance;
}

/**
 * @brief Renvoie la distance entre les deux chaines.
 * 
 * @param s la premiere chaine de nucleotide.
 * @param s2 la deuxieme chaine de nucleotide.
 * @return float la distance d edition.
 */
float calculDistanceEdition(const sequence_t s, const sequence_t s2) {
    //
    float** matriceDistance = calculMatriceDistance(s,s2);
    
    //
    afficherMatriceDistance(matriceDistance, s.taille, s2.taille);
    float dist = matriceDistance[s.taille][s2.taille];

    // Liberation du tableau des distances.
    for (u_int8_t position = 0; position < (s.taille + 1); position++) {
        free(matriceDistance[position]);
    }
    free(matriceDistance);

    //
    return dist;
}