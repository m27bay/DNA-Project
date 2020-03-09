#include "sequence.h"

/*#################### Manipulation des sequences ####################*/

SEQUENCE *InitSeq (char *dir, int *countFile){
	TestStrVide(dir); // On vérifie que char *dir n'est pas vide.

	DIR *doss=OpenDoss(dir);
	CountFic(doss, countFile);
	TestPtr(doss);
	
	// Initialisation //
	FILE *F=NULL;
	struct dirent *FichierLu=NULL;
	int val=0; int lenSeq;

	SEQUENCE *s=calloc(*countFile, sizeof(SEQUENCE));
	TestPtr(s);
	
	while((FichierLu=readdir(doss))){ // Si on ne peut plus lire de fichier readdir(doss) vaut NULL donc le while s'arrete.
		
		if((strcmp(FichierLu->d_name, ".") != 0) && (strcmp(FichierLu->d_name, "..") != 0)){
			// Cette condition permet de ne pas lire le dossier de l'executable et le dossier où sont stockés les fichiers.
			
			char *NomDuDoss=malloc(sizeof(char)*LENAME);
			strcpy(NomDuDoss, dir); strcat(NomDuDoss, "/"); strcat(NomDuDoss, FichierLu->d_name);
			 // On renseigne le nom du dossier pour lire les fichiers.
			TestPtr(NomDuDoss);
			
			F=fopen(NomDuDoss, "r");
			
			if(F){
				s[val].num=val+1; // On renseigne le numéro de la séquence.
				
				LenSequence(F, &lenSeq);
				s[val].len=lenSeq; // On renseigne la taille de la séquence dynamiquement.
				
				s[val].seq=calloc(lenSeq+1, sizeof(char));
				TestPtr(s[val].seq);
				fgets(s[val].seq, lenSeq+1, F); // On lit la séquence du fichier et on l'enregistre.
				
				s[val].nomFic=calloc(strlen(FichierLu->d_name)+1, sizeof(char));
				TestPtr(s[val].nomFic);
				strncpy(s[val].nomFic, FichierLu->d_name, (int) strlen(FichierLu->d_name)); // On renseigne le nom du fichier.
				
				val+=1; // On passe à la séquence suivante.
				
				fclose(F);
			}
			else{
				puts("\nErreur: Ouverture du fichier impossible");
				exit(2);
			}
			free(NomDuDoss);
		}
	}
	
	CloseDoss(doss);
	return s;
}

void TrieSeqCroissant(SEQUENCE *s, int countFile){
	// Cette fonction trie de manière croissante les séquences en fonction de leurs noms de fichiers.
	
	// Algo de tri par insertion pour trier les séquences.
	for(int i=0; i<countFile; i++){
		int j=i-1;
		while(j>=0 && (strcmp(s[j].nomFic, s[j+1].nomFic))>0){ // on compare les séquences deux à deux via strcmp
			
			// On interverti les sequences entre elle.
			SEQUENCE tmp=s[j];
			s[j]=s[j+1]; s[j+1]=tmp;
			
			// On met dans les numéros des sequences dans le bon ordre.
			int tmp2=s[j].num;
			s[j].num=s[j+1].num; s[j+1].num=tmp2;
			
			j=j-1;
		}
	}
}

int TailleMax(SEQUENCE *s, int countFile){
	// Cette fonction permet de trouver la plus grande sequence pour
	// adapter toutes les autres sequences en fonction de cette dernière.
	
	// On créer un tableau avec les longueurs des sequences.
	int *copie_len=calloc(countFile, sizeof(int));
	TestPtr(copie_len);
	for(int i=0; i<countFile; i++) copie_len[i] = s[i].len;
	
	// Algo de tri par insertion pour trouver le max.
	for(int i=0; i<countFile; i++){ 
		int j=i-1;
		while(j>=0 && copie_len[j]>copie_len[j+1]){
			
			int tmp=copie_len[j];
			copie_len[j]=copie_len[j+1];
			copie_len[j+1]=tmp;
			
			j=j-1;
		}
	}
	
	int Max=copie_len[countFile-1];
	free(copie_len);
	
	return Max;
}

void MemeTaille(SEQUENCE *s, int countFile){
	// Cette fonction met toutes les séquences sur la même taille en complétant par des tirets.
	
	int Max=TailleMax(s, countFile);
	
	for(int i=0; i<countFile; i++){
		// On ralloue de la mémoire, en fonction de la plus grande séquence.
		if(s[i].len<Max){
			s[i].seq=(char *)realloc(s[i].seq, sizeof(char)*Max+1);
			TestPtr(s[i].seq);
			s[i].seq[Max]='\0';
		}
		
		// On remplie les derniers caractères par des tirets pour adapter les tailles.
		while(s[i].len<Max){
			s[i].seq[s[i].len]='-';
			s[i].len+=1;
		}
	}
}

/*################## Fin manipulation des sequences ##################*/


/*############################ Affichage #############################*/
void AffSeq (SEQUENCE *s, int countFile){
	for(int i=0; i<countFile; i++){
		printf("seq%.2d: %s taille: %d fichier: %s\n", s[i].num, s[i].seq, s[i].len, s[i].nomFic);
	}
}
/*########################### Fin affichage ##########################*/

/*########################### Libération #############################*/

void LibereSeq (SEQUENCE s){
	// On libère ce qui a été alloué dynamiquement c'est à dire 
	// les séquences (char *), et le nom des fichiers (char *).
	
	free(s.seq);
	free(s.nomFic);
}

void LibereSeqAll (SEQUENCE *s, int countFile){
	// Cette fonction permet de libérer toutes les SEQUENCES.
	
	for(int i=0; i<countFile; i++) LibereSeq(s[i]);
	
	// Enfin on libère le tableau de séquence.
	free(s);
}
/*########################## Fin libération ##########################*/
