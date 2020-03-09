#include "gestion.h"

/*########################## Gestion dossier #########################*/

DIR *OpenDoss (char *dir){
	// Initialisation //
	TestStrVide(dir);
	DIR *doss=opendir(dir);
	
	// Test erreur //
	if(!doss){
		puts("Erreur 1: Ouverture impossible.");
		exit(1);
	} 
	//~ else puts("\tDossier ouvert.");
	
	return doss; // On retourne le pointeur du dossier pour pouvoir le fermer.
}

void CloseDoss (DIR *doss){	
	// Test erreur //
	if(closedir(doss) == -1){ // closedir ferme le dossier dans cette condition
		puts("Erreur: Fermeture impossible.");
		exit(-1);
	}
	//~ else puts("\tDossier fermé.");
}

/*######################## Fin gestion dossier #######################*/


/*########################## Gestion fichier #########################*/

void CountFic (DIR *doss, int *count){
	// Initialisation //
	struct dirent *fichierLu=NULL;
	*count=0; // On met a zéro la variable pour être sur que l'on parte  bien de zéro.
	
	while((fichierLu=readdir(doss))){		
		if((strcmp(fichierLu->d_name, ".") != 0) && (strcmp(fichierLu->d_name, "..") != 0)) *count+=1;
	}
	rewinddir(doss); // Pour revenir au début du dossier.
}

void LenSequence (FILE *F, int *len){
	// Cette fonction renvoie la taille de la sequence du fichier F.
	
	// Initialisation //
	*len=0;
	
	if(F){
		while(fgetc(F) != EOF) *len+=1; // Si on peut lire un caractère on incrémente len.
	}
	fseek(F, 0, SEEK_SET); // Pour revenir au debut du fichier et le relire par la suite.
}

/*######################## Fin gestion dossier #######################*/


/*###################### Test sur les pointeurs ######################*/

void TestStrVide (char *s){
	if(s && !s[0]) {puts("Erreur 4: Chaîne vide"); exit(4);}
}

int StrEstVide (char *s){
	return (s && !s[0])? 1: 0;
}

void TestPtrInt (int *ptr){
	if(ptr == NULL) {puts("Erreur 5: Pointeur NULL"); exit(5);}
}

void TestPtrChar (char *ptr){
	if(ptr == NULL) {printf("Erreur 5: Pointeur (%s) NULL\n", ptr); exit(5);}
}

void TestPtr (void *ptr){
	if(ptr == NULL) {puts("Erreur 5: Pointeur NULL"); exit(5);}
}
	
/*################### Fin de test sur les pointeurs ##################*/
