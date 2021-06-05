#include "gestion.h"

/*###################### Présentation sequence.h #######################
 * #####        Cette librairie présente toutes les fonctions      #####
 * #####    programmées pour l'initialisation, la manipulation et  #####
 * #####                l'affichage des séquences.                 #####
 * ###################################################################*/

/*#################### Manipulation des sequences ####################*/

typedef struct{
	int num, len; // numéro et taille de la séquence.
	char *seq; // La séquence en elle même.
	
	char *nomFic;
}SEQUENCE;

SEQUENCE *InitSeq (char *dir, int *countFile);
void TrieSeqCroissant(SEQUENCE *s, int countFile);
int TailleMax(SEQUENCE *s, int countFile);
void MemeTaille(SEQUENCE *s, int countFile);

/*################## Fin manipulation des sequences ##################*/


/*############################ Affichage #############################*/
void AffSeq (SEQUENCE *s, int countFile);
/*########################### Fin affichage ##########################*/


/*########################### Libération #############################*/
void LibereSeq (SEQUENCE s);
void LibereSeqAll (SEQUENCE *s, int countFile);
/*########################## Fin libération ##########################*/
