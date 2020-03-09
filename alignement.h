#include "famille.h"

/*############################## Outils ##############################*/

float Min2float(float a, float b);
char Max4(int A, int C, int G, int T);
SEQUENCE CopieSeq(SEQUENCE new, SEQUENCE old);

/*############################ Fin outils ############################*/


/*################## Manipulation des alignements ####################*/

typedef struct{
	SEQUENCE *S; // Tableau avec les séquences originales.
	char **seq; // Tableau avec juste les séquences modifiées.
	
	int nbrSeq, len;
	char *consensus;
	
	float dist;
} ALIGNEMENT;

/*#################*/
float **CheminCout(char *m1, char *m2);
char *InverseStr(char *s);
char FreqCharMax (ALIGNEMENT a, int posChar);
/*#################*/

ALIGNEMENT Aligne2Seq(SEQUENCE s1, SEQUENCE s2);
ALIGNEMENT AjoutSeq(ALIGNEMENT a, SEQUENCE appened);
ALIGNEMENT FoundConsensus(ALIGNEMENT a);
ALIGNEMENT AligneFam(FAMILLE f);
ALIGNEMENT *AligneAllFam(FAMILLE *f, int nbrFam);

/*################# Fin manipulation des alignements #################*/


/*############################ Affichage #############################*/

void AffTab2D(int **t, int n, int m);

/*###########################*/
void AffAlignDessin(ALIGNEMENT a);
void AffAlignDessinAll (ALIGNEMENT *a, int nbrFam);
/*###########################*/

/*###########################*/
void AffAlign (ALIGNEMENT a);
void AffAlignAll (ALIGNEMENT *a, int nbrFam);
/*###########################*/

/*########################### Fin affichage ##########################*/


/*########################### Libération #############################*/
void LibereAligne (ALIGNEMENT a);
void LibereAligneAll (ALIGNEMENT *a, int countFile);
/*########################## Fin libération ##########################*/
