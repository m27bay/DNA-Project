#include "distance.h"

/*################### Manipulation des distances 1 ###################*/

float SumD1 (char *s1, char *s2){
	// Cette fonction fait la somme des caractères.
	
	TestStrVide(s1); TestStrVide(s2);
	
	// Cas ou les deux chaînes sont identiques.
	if(!strcmp(s1, s2)) return 0;
	
	float SumD1=0;
	// On fait la somme des distances lettres par lettres.
	for(int i=0; i<(int) strlen(s1); i++) SumD1+=DistCaract[Convert(s1[i])][Convert(s2[i])];
	
	return SumD1;
}

DISTANCE **CalculeD1(SEQUENCE *s, int countFile){
	// Cette fonction calculer de manière triangulaire les distances
	// pour diviser par 2 le nombre d'opération.
	
	
	// Initialisation //
	TrieSeqCroissant(s, countFile);
    MemeTaille(s, countFile);
    DISTANCE **d=Malloc2D(countFile, countFile);
    TestPtr(d);
    
    int i, j;
	for(i=0; i<countFile; i++){
		for(j=i; j<countFile; j++){
			d[i][j].S1=s[i];
			d[i][j].S2=s[j];
			
			d[i][j].dist=SumD1(d[i][j].S1.seq, d[i][j].S2.seq);
		}
	}	
    return d;
}

/*################# Fin manipulation des distances 1 #################*/


/*################### Manipulation des distances 2 ###################*/

float Min3(float a, float b, float c){
	return (a<=b && a<=c) ? a : (b<=a && b<=c) ? b : c;
}

float D2(char *m1, char *m2){
	int n=(int) strlen(m1); int m=(int) strlen(m2);
	
	// Premièrement on calcul dans un tableau toutes les distances possibles.
	float **t=Malloc2Dfloat(n+1, m+1);
	TestPtr(t);
	t[0][0]=0;
	
	// On rempli les deux bords de notre tableau, c'est à dire la distance entre un caractère et '-'.
	for(int i=1; i<n+1; i++) t[i][0]=t[i-1][0]+1.5;
	for(int j=1; j<m+1; j++){
		t[0][j]=t[0][j-1]+1.5;
		for(int i=1; i<n+1; i++){
			
			// On calcule maintenant le centre du tableau via les trois possibilitées.
			float Inserm1, Inserm2, Substi;
			
			// Deuxième cas: on aligne les deux caractères, on "substitue" l'un par l'autre.
			Substi=t[i-1][j-1] + DistCaract[Convert(m1[i-1])][Convert(m2[j-1])];
			
			// Deuxième cas: on ajoute un '-' dans m1.
			Inserm1=t[i-1][j] + 1.5;
			
			// Troisème cas: on ajoute un '-' dans m2.
			Inserm2=t[i][j-1] + 1.5;
					
			// On regarde la plus petite des opérations.
			t[i][j]=Min3(Substi, Inserm1, Inserm2);
		}
	}
	
	// La distance correspond au dernier élément du tableau,
	// lorsque l'on a vu toutes les possibilitées.
	float Dist=t[n][m];
	
	AffTab2Dfloat(t, n, m);
	
	for(int i=0; i<n+1; i++) free(t[i]);
	free(t);
	
	return Dist;
}

DISTANCE **CalculeD2(SEQUENCE *s, int countFile){
	// Cette fonction calculer de manière triangulaire les distances
	// pour diviser par 2 le nombre d'opération.
	
	
	// Initialisation //
	TrieSeqCroissant(s, countFile);
    DISTANCE **d=Malloc2D(countFile, countFile);
    
    int i, j;
	for(i=0; i<countFile; i++){
		for(j=i; j<countFile; j++){
			d[i][j].S1=s[i];
			d[i][j].S2=s[j];
			
			d[i][j].dist=D2(d[i][j].S1.seq, d[i][j].S2.seq);
		}
	}	
    return d;
}

/*################# Fin manipulation des distances 2 #################*/


/*############################## Outils ##############################*/

float** Malloc2Dfloat (int sizex, int sizey){
	// Fonction qui alloue dynamiquement un tableau de float en 2D.
	
	float **Res=calloc(sizex, sizeof(float*));
	for(int i=0; i<sizex; i++) Res[i]=calloc(sizey ,sizeof(float));
	
	return Res;
}

DISTANCE** Malloc2D (int sizex, int sizey){
	// Fonction qui alloue dynamiquement un tableau de DISTANCE en 2D.
	DISTANCE **Res=calloc(sizex, sizeof(DISTANCE*));
	for(int i=0; i<sizex; i++) Res[i]=calloc(sizey ,sizeof(DISTANCE));
	
	return Res;
}

int Convert(char c){
	// Fonction qui converti les caractères en numéros pour pouvoir
	// utiliser le tableau de distance par la suite.
	
	return (c=='A')?0:((c=='C')?1:((c=='G')?2:(c=='T')?3:((c=='-')?4: -1)));
}

float *DellDoublons (float *t, int size, int *pos){
	float *t2=calloc(size, sizeof(float));
	TestPtr(t2);
	
	*pos=0; int i=0;
	while(i<size){
		while(!t[i]) i++;
		t2[*pos]=t[i]; i++;
		while(t[i]==t2[*pos]) i++;
		*pos+=1; 
	}

	return t2;
}

void TrieDistCroissante (float *t, int size){
	// On tries les distances dans *t.
	
	for(int i=0; i<size; i++){ 
		int j=i-1;
		while(j>=0 && t[j]>t[j+1]){
			
			float tmp=t[j];
			t[j]=t[j+1];
			t[j+1]=tmp;
			
			j=j-1;
		}
	}
}

float *TabDist (DISTANCE **d, int countFile, int *pos){
	// On copie d'abord toutes les distances.
	int sizex=(countFile*(countFile+1))/2; int compt=0;
	float *t=calloc(sizex+1, sizeof(float));
	TestPtr(t);
	
	for(int i=0; i<countFile; i++) for(int j=i; j<countFile; j++) {t[compt]=d[i][j].dist; compt++;}
	
	// On les tries.
	TrieDistCroissante(t, sizex);
	
	// On enlève les doublons.
	float *t2=DellDoublons(t, sizex, pos);
	TestPtr(t2);
	
	free(t);
	
	return t2;
}

/*############################ Fin outils ############################*/


/*############################ Affichage #############################*/

void EcrireDistTriang (DISTANCE **d, int countFile){
	FILE *Fichier=NULL;
	Fichier=fopen("TabDistTriang.txt", "w");
	
	if(Fichier){
		// On écrit d'abord la première ligne du tableau avec le nom des fichiers.
		fputs("\t\t\t", Fichier);
		int i;
		for(i=0; i<countFile; i++) fprintf(Fichier, "%s\t", d[0][i].S2.nomFic);
		fputs("\n\n", Fichier);
		
		// On écrit ensuite ligne par ligne.
		int k=0; int l=0; i=0;
		
		for(int j=0; j<countFile; j++){
			// On écrit d'abord le nom du fichier. 
			fprintf(Fichier, "%s", d[0][k].S2.nomFic);
			k++; l++; i=l;
			
			// Puis on insere des espaces pour donner une forme triangulaire.
			for(int m=1; m<l; m++) fputs("\t\t\t", Fichier);
			
			// Enfin on écrit la distances
			for(; i<=countFile; i++) fprintf(Fichier,"\t  %.2f\t", d[j][i-1].dist);
			
			fputs("\n\n", Fichier);
		}
		fclose(Fichier);
	}
}

void AffDistsolo (DISTANCE d){
	printf("D(%s, %s) = %.1f\n", d.S1.nomFic, d.S2.nomFic, d.dist);
}

void AffDistTest (DISTANCE **d, int countFile){
	float val=1; int i, j;
	while(val<50){  
		for(i=0; i<countFile; i++){
			for(j=i; j<countFile; j++){
				if(d[i][j].dist==val) AffDistsolo(d[i][j]);
			}
		}
		val+=0.5;
	}
}

void AffTab2Dfloat(float **t, int n, int m){
	for(int i=0; i<n+1; i++){
		for(int j=0; j<m+1; j++){
			printf("%.2f  ", t[i][j]);
		}
		printf("\n");
	}
}

/*########################### Fin affichage ##########################*/


/*########################### Libération #############################*/
void LibereDistAll (DISTANCE **d, int countFile){
	for(int i=0; i<countFile; i++) free(d[i]);
	free(d);
}
/*########################## Fin libération ##########################*/
