#include "famille.h"

/*############################## Outils ##############################*/

void Dmin (DISTANCE **D, float *Dmin1, float *oldDmin, int countFile){
	// Cette fonction permet d'avoir la distance minimum qui n'a pas déja été trouvé.
	// On utilise une troisième variable, olDmin, pour être sûr d'obtenir les différents minimums sans prendre.
	// en compte un minimum déja trouvé.
		
	*Dmin1=100; // On donne une valeur assez haute pour pouvoir comparer avec les autres distances.
	
	for(int i=0; i<countFile; i++){
		for(int j=i; j<countFile; j++){
			if(D[i][j].dist<*Dmin1 && D[i][j].dist>0 && D[i][j].dist>*oldDmin) *Dmin1=D[i][j].dist;
		}
	}
	*oldDmin=*Dmin1;
}

int** Malloc2Dint (int sizex, int sizey){
	// Fonction qui alloue dynamiquement un tableau d'entier en 2D.
	
	int **Res=calloc(sizex, sizeof(int*));
	for(int i=0; i<sizex; i++) Res[i]=calloc(sizey ,sizeof(int));
	
	return Res;
}

/*############################ Fin outils ############################*/


/*#################### Manipulation des familles #####################*/

FAMILLE *NbrFam (DISTANCE **d, int countFile, int *countFam){
	// Cette fonction permet d'initialiser le tableau de famille en fonction du nombre.
	// de minimum différent trouvé.
	
	float Dmin1=0; float oldDmin=0;
	int i=0;
	
	while(Dmin1<100){Dmin(d, &Dmin1, &oldDmin, countFile); i++;}
	
	*countFam=i-1;
	FAMILLE *f=calloc(*countFam, sizeof(FAMILLE));
	TestPtr(f);
	
	return f;
}

DISTANCE *FoundSeq (DISTANCE **d, int countFile, float dist, int *compt){
	// Cette fonction permet de trouver les distances entre les séquences.
	// correspondantent au paramètre "dist".
	
	//Première étape, compter le nombre de distance yant "dist"==d.dist.
	*compt=0;
	int sizex=(countFile*(countFile+1))/2;
	int **tmp=Malloc2Dint(sizex, 2); // On créer un tableau de taille triangulaire pour
	TestPtr(tmp);					// stocker i et j, pour ne pas reparcourir le tableau DISTANCE **d par la suite
		
	int i, j;								
	for(i=0; i<countFile; i++){
		for(j=i; j<countFile; j++){
			if(d[i][j].dist==dist){
				tmp[*compt][0]=i; 
				tmp[*compt][1]=j;
				(*compt)+=1;
			}
		}
	}
			
	// On crée le tableau contenant les séquences.
	DISTANCE *d2=calloc(*compt, sizeof(DISTANCE));
	TestPtr(d2);
	
	// Puis on rempli le tableau
	for(i=0; i<*compt; i++) d2[i]=d[tmp[i][0]][tmp[i][1]];
	
	// On libere tmp
	for(i=0; i<sizex; i++) free(tmp[i]);
	free(tmp);
	
	return d2;
}

FAMILLE SeqCommune (SEQUENCE *s, FAMILLE f, int countFile){
	// Cette fonction retire des familles les séquences qui ne sont pas utile.
	
	// On cree un tableau de "countFile" entier pour écrire les apparitions de chaque séquence au sein de la famille.
	int *t=calloc(countFile, sizeof(int));
	
	// On écrit les apparations des séquences.
	for(int i=0; i<countFile; i++){
		for(int j=0; j<f.nbrDist; j++){
			if(!(strcmp(s[i].nomFic, f.d[j].S1.nomFic))) t[f.d[j].S1.num-1]+=1;
			if(!(strcmp(s[i].nomFic, f.d[j].S2.nomFic))) t[f.d[j].S2.num-1]+=1;
		}
	}
	
	// On cherche maintenant l'indice plus grand, qui correspond au numéro de la séquence.
	int i=0; int commun=0;
	while(!t[i]) i++;
	commun=i; i++;
	for(; i<countFile; i++) if(t[i] && t[i]>t[commun]) commun=i;
	
	DISTANCE *Dnew=calloc(t[commun], sizeof(DISTANCE));	i=0;
	
	for(int j=0; j<f.nbrDist; j++){
		// Si d[j] convient on enregistre dans dnew.
		if(!strcmp(f.d[j].S1.nomFic, s[commun].nomFic) || !strcmp(f.d[j].S2.nomFic, s[commun].nomFic)) {Dnew[i]=f.d[j]; i++;}
	}

	// On modifie le nombre de distance.
	f.nbrDist=t[commun];
	
	// On enregistre la séquence commune.
	f.seq=calloc(s[commun].len, sizeof(char));
	strcpy(f.seq, s[commun].nomFic);
	
	// On libère les anciennes distance et on sauvegarde les nouvelles.
	free(f.d);
	f.d=Dnew;
	
	// On libère le tableau utilisé pour les fréquences d'appartitions.
	free(t);
	
	return f;
}

FAMILLE *InitFamille (DISTANCE **d, SEQUENCE *s, int countFile, int *countFam, int *compt){
	// Cette fonction initialise les familles.
	
	FAMILLE *f=NbrFam(d, countFile, countFam);
	
	float Dmin1=0; float oldDmin=0;
	int i=0; // i correspond au numéro de la famille dans le tableau f.
	int c=0; // c correspond à une lettre qui sert de nom pour la famille.
	
	while(i<*countFam){
		// On trouve la valeur minimum et on la renseigne.
		Dmin(d, &Dmin1, &oldDmin, countFile);
		f[i].dist=Dmin1;
		
		// On trouve les sequences qui corrspondent au Dmin.
		f[i].d=FoundSeq(d, countFile, f[i].dist, compt);
		f[i].nbrDist=*compt;
		
		// On enleve les séquences en trop.
		f[i]=SeqCommune(s, f[i], countFile);
		
		// On donne le nom de le famille.
		char *Nom="Famille";
		f[i].NomFam=calloc((int) strlen(Nom)+3, sizeof(char));
		
		if(c==26) c+=6; // On saute les caractère spéciaux de la table ASCII.
		
		sprintf(f[i].NomFam, "Famille_%c", 'A'+c);
		i++; c++;
	}
	
	return f;
}

/*################### Fin manipulation des familles ##################*/


/*###################### Gestion dossier famille #####################*/

void CreatDoss (FAMILLE *f, int countFam, char *DossFam){
	// Cette fonction permet de créer les dossiers familles pour y stocker les sequences.
	
	int ownerAllPerm=00700; // Mode d'ouveture du dossier.
	char Dir[LENAME];
	strcpy(Dir, DossFam); // Dosier ou l'on stocker toutes les familles.
	
	//~ if(!mkdir(Dir, ownerAllPerm)) puts("Open successfully");
	//~ else {puts("Error 6: Open failed"); exit(6);}
	
	// Vérification de l'ouverture.
	if(mkdir(Dir, ownerAllPerm)) exit(6);
	strcat(Dir, "/");
	
	for(int i=0; i<countFam; i++){
		// Boucle qui créer chaque dossier famille.
		char *Dir2=calloc(LENAME, sizeof(char));
		strcpy(Dir2, Dir);
		strcat(Dir2, f[i].NomFam);
		
		//~ if(!mkdir(Dir2, ownerAllPerm)) puts("Open successfully");
		//~ else {puts("Error 6: Open failed"); exit(6);}
		
		// Création du dossier de la famille en question.
		if(mkdir(Dir2, ownerAllPerm)) exit(6); // Si il y a une erreur mkdir renvoie-1
		
		// libération.	
		free(Dir2);
	}
}

void CopieSeqDoss (FAMILLE *f, int countFam, char *DossFam, char *DossSeq){
	// Cette fonction permet de copier les sequences dans leur dossier famille.
	
	for(int i=0; i<countFam; i++){
		// Première étape: on trouve le dossier famille.
		char *Dir=calloc(LENAME, sizeof(char));
		strcpy(Dir, DossFam);
		strcat(Dir, "/");
		strcat(Dir, f[i].NomFam);
		
		for(int j=0; j<f[i].nbrDist; j++){ // nbrDist correspond au nombre de couple de séquence.
			for(int k=0; k<2; k++) // k permet de copier les deux séquences qui correspondent à une distance.
			{
				char *ajout;
				// Choix de la séquence.
				if(!k) ajout=f[i].d[j].S1.nomFic;
				if(k) ajout=f[i].d[j].S2.nomFic;
				
				// Dir2 correspond à ce que l'on veut copier.
				char *Dir2=calloc(LENAME, sizeof(char));
				strcpy(Dir2, DossSeq);
				strcat(Dir2, "/");
				strcat(Dir2, ajout);
				
				// Instruction pour copier.
				char *cmd=calloc(LENAME, sizeof(char));
				strcpy(cmd, "cp ");
				strcat(cmd, Dir2);
				strcat(cmd, " ");
				strcat(cmd, Dir);
				// On copie Dir2 dans Dir.
				system(cmd);
								
				//Libération.
				free(Dir2); free(cmd);
			}
		}
		// Libération.
		free(Dir);
	}
}

void DellDoss (FAMILLE *f, int countFam, char *DossFam){
	// Cette fonction permet de supprimer tous les fichiers et tous les dossiers.
	
	for(int i=0; i<countFam; i++){
		
		//On va dans le dossier général famille puis dans une famille en particulier.
		char *Dir=calloc(LENAME, sizeof(char));
		strcpy(Dir, DossFam);
		strcat(Dir, "/");
		strcat(Dir, f[i].NomFam);
		strcat(Dir, "/");
		
		for(int j=0; j<f[i].nbrDist; j++){
			for(int k=0; k<2; k++)
			{
				// On supprime une séquence puis l'autre.
				char *dell;
				if(!k) dell=f[i].d[j].S1.nomFic;
				if(k) dell=f[i].d[j].S2.nomFic;
				
				// Chemin de la séquence à supprimer.
				char *Dir2=calloc(LENAME, sizeof(char));
				strcpy(Dir2, Dir);
				strcat(Dir2, dell);
				
				// Instruction pour supprimer.
				char *cmd=calloc(LENAME, sizeof(char));
				strcpy(cmd, "rm -f ");
				strcat(cmd, Dir2);
				system(cmd);
				
				// Libération.
				free(Dir2); free(cmd);
			}
		}
		
		//~ if(!rmdir(Dir)) puts("Close successfully");
		//~ else {puts("Error 7: Close Failed"); exit(7);}
		
		// Suppression du dossier de la famille en question.
		if(rmdir(Dir)) exit(7); // Si il y a une erreur rmdir renvoie-1.
		
		// Libération.
		free(Dir);
	}
	
	//~ if(!rmdir(DossFam)) puts("Close successfully");
	//~ else {puts("Error 7: Close Failed"); exit(7);}
	
	// Suppression du dossier où sont stocker toutes les familles.
	if(rmdir(DossFam)) exit(7);
}

/*################### Fin gestion dossier famille ####################*/


/*############################ Affichage #############################*/
void AffFam(FAMILLE *f, int countFam){
	for(int i=0; i<countFam; i++){
		printf("Nom: %s.\tTaille: %d.  Séquence commune: %s\n", f[i].NomFam, f[i].nbrDist, f[i].seq);
		for(int j=0; j<f[i].nbrDist; j++) AffDistsolo(f[i].d[j]);
		puts("");
	}
}

void Aff1Fam(FAMILLE f){
	printf("Nom: %s.\tTaille: %d.  Séquence commune: %s\n", f.NomFam, f.nbrDist, f.seq);
	for(int j=0; j<f.nbrDist; j++) AffDistsolo(f.d[j]);
}
/*########################### Fin affichage ##########################*/


/*########################### Libération #############################*/
void LibereFam (FAMILLE f){
	// Cette fonction permet de libérer une FAMILLE.
	
	// Les (char *)
	free(f.NomFam); free(f.seq);
	
	// Le tableau de DISTANCE
	free(f.d);	
}

void LibereFamAll (FAMILLE *f, int countFam){
	for(int i=0; i<countFam; i++) LibereFam(f[i]);
	free(f);
}
/*########################## Fin libération ##########################*/
