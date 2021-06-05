#include "distance.h"

/*############################## Outils ##############################*/

void Dmin (DISTANCE **D, float *Dmin1, float *oldDmin, int countFile);
int** Malloc2Dint (int sizex, int sizey);

/*############################ Fin outils ############################*/


/*#################### Manipulation des familles #####################*/

typedef struct{
	char *NomFam;
	DISTANCE *d;
	char *seq; // Correspondant à la séquence en commun dans la famille.
	int nbrDist;
	float dist;
}FAMILLE;

FAMILLE *NbrFam (DISTANCE **d, int countFile, int *countFam);
DISTANCE *FoundSeq (DISTANCE **d, int countFile, float dist, int *compt);
FAMILLE SeqCommune (SEQUENCE *s, FAMILLE f, int countFile);
FAMILLE *InitFamille (DISTANCE **d, SEQUENCE *s, int countFile, int *countFam, int *compt);

/*################### Fin manipulation des familles ##################*/


/*###################### Gestion dossier famille #####################*/

void CreatDoss (FAMILLE *f, int countFam, char *DossFam);
void CopieSeqDoss (FAMILLE *f, int countFam, char *DossFam, char *DossSeq);
void DellDoss (FAMILLE *f, int countFam, char *DossFam);

/*################### Fin gestion dossier famille ####################*/


/*############################ Affichage #############################*/
void AffFam(FAMILLE *f, int countFam);
void Aff1Fam(FAMILLE f);
/*########################### Fin affichage ##########################*/

/*########################### Libération #############################*/
void LibereFam (FAMILLE f);
void LibereFamAll (FAMILLE *f, int countFam);
/*########################## Fin libération ##########################*/
