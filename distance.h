#include "sequence.h"

/*################### Manipulation des distances 1 ###################*/

// Tableau où sont renseingées les distances.
const static float DistCaract[][5] ={{0, 2, 1, 2, 1.5},
									{2, 0, 2, 1, 1.5},
									{1, 2, 0, 2, 1.5},
									{2, 1, 2, 0, 1.5},
									{1.5, 1.5, 1.5, 1.5, 0}};
								
typedef struct{
	SEQUENCE S1, S2;
	
	float dist; // La distance entre S1 et S2.
} DISTANCE;


float SumD1 (char *s1, char *s2);
DISTANCE **CalculeD1(SEQUENCE *s, int countFile);
DISTANCE **CalculeD2(SEQUENCE *s, int countFile);

/*################# Fin manipulation des distances 1 #################*/


/*################### Manipulation des distances 2 ###################*/

float Min3(float a, float b, float c);
float D2(char *m1, char *m2);

/*################# Fin manipulation des distances 2 #################*/


/*############################## Outils ##############################*/

float** Malloc2Dfloat (int sizex, int sizey);
DISTANCE** Malloc2D (int sizex, int sizey);
int Convert(char c);
float *DellDoublons (float *t, int size, int *pos);
void TrieDistCroissante (float *t, int size);
float *TabDist (DISTANCE **d, int countFile, int *pos);

/*############################ Fin outils ############################*/


/*############################ Affichage #############################*/

void EcrireDistTriang (DISTANCE **d, int countFile);
void AffDistsolo (DISTANCE d);
void AffDistTest (DISTANCE **d, int countFile);
void AffTab2Dfloat(float **t, int n, int m);

/*########################### Fin affichage ##########################*/


/*########################### Libération #############################*/
void LibereDistAll (DISTANCE **d, int countFile);
/*########################## Fin libération ##########################*/
