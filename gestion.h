#include "stdlib.h"
#include "stdio.h"

#include "string.h"

#include "unistd.h" // Pour la fonction getcwd
#include "dirent.h"

#include "sys/stat.h" // Pour les fonctions comme rmdir et mkdir
#include "sys/types.h"

#define LENAME 256 // Pour la taille de nom (de fichier, de dossier, ect).

/*####################### Présentation gestion.h #######################
 * #####        Cette librairie présente toutes les fonctions      #####
 * #####  programmées pour la gestion du projet, tout ce qui n'est #####
 * ##### pas lié directement aux sequences, aux distances, ...     #####
 * ###################################################################*/


/*########################## Gestion dossier #########################*/

DIR *OpenDoss (char *dir);
void CloseDoss (DIR *doss);

/*######################## Fin gestion dossier #######################*/


/*########################## Gestion fichier #########################*/

void CountFic (DIR *doss, int *count);
void LenSequence (FILE *F, int *len); 

/*######################## Fin gestion dossier #######################*/


/*###################### Test sur les pointeurs ######################*/

void TestStrVide (char *s);
int StrEstVide (char *s);
void TestPtrInt (int *ptr);
void TestPtrChar (char *ptr);
void TestPtr (void *ptr);

/*################### Fin de test sur les pointeurs ##################*/
