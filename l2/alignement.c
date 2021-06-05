#include "alignement.h"

/*############################## Outils ##############################*/

float Min2float(float a, float b){
	return (a<b)?a:b;
}

char Max4(int A, int C, int G, int T){
	return (A>C && A>G && A>T && A>1)? 'A' : (C>A && C>G && C>T && C>1)? 'C' : (G>A && G>C && G>T && G>1)? 'G' : (T>A && T>C && T>G && T>1)? 'T' : '.';
}

/*############################ Fin outils ############################*/


/*################## Manipulation des alignements ####################*/

/*#################*/

float **CheminCout(char *m1, char *m2){
	// Cette fonction permet de retracer le chemin des possibilitées.
	int n=(int) strlen(m1); int m=(int) strlen(m2);
	
	// Premièrement on calcul dans un tableau toutes les distances possibles.
	float **t=Malloc2Dfloat(n+1, m+1);
	t[0][0]=0;
	
	// On rempli les deux bords de notre tableau, c'est à dire la distance entre un caractère et '-'.
	for(int i=1; i<n+1; i++) t[i][0]=t[i-1][0]+1.5;
	for(int j=1; j<m+1; j++){
		t[0][j]=t[0][j-1]+1.5;
		for(int i=1; i<n+1; i++){
			
			// On calcul maintenant le centre du tableau via les trois possibilitées.
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
	
	return t;
}

char *InverseStr (char *s){
	// Cette fonction permet d'inverser une chaine de caractère.
	
	int len=(int) strlen(s);
	char *InvS=calloc(len+1, sizeof(char));
	TestPtr(InvS);
	
	int j=len-1;
	for(int i=0; i<len; i++) {InvS[i]=s[j]; j--;}
	InvS[len]='\0';
	free(s);
	
	return InvS;
}

char FreqCharMax (ALIGNEMENT a, int posChar){
	// Cette fonction permet de trouver le caractère avec la frèquence max.
	
	int A=0; int C=0; int G=0; int T=0;
	
	for(int i=0; i<a.nbrSeq; i++){
		int len = (int) strlen(a.seq[i]);
		if(posChar<len){
			char tmp=a.seq[i][posChar];
			if(tmp=='A') A++;
			else if(tmp=='C') C++;
			else if(tmp=='G') G++;
			else if(tmp=='T') T++;
		}
	}
	
	return Max4(A, C, G, T);
}

/*#################*/

ALIGNEMENT Aligne2Seq(SEQUENCE s1, SEQUENCE s2){
	// Cette fonction permet d'aligner deux séquences.
	
	int n=s1.len; int m=s2.len;	
	// Premièrement on calcul dans un tableau tous les coûts possibles.
	float **Cout=CheminCout(s1.seq,s2.seq);
	
	// On prépare notre alignement final.
	ALIGNEMENT a;
	
	// On commence par deux séquences.
	a.nbrSeq=2;
	a.S=calloc(a.nbrSeq, sizeof(SEQUENCE));
	a.S[0]=s1; a.S[1]=s2;
	
	// On prépare les séquences modifiées.
	a.seq=calloc(a.nbrSeq, sizeof(SEQUENCE));
	
	char *tmps1=calloc(LENAME, sizeof(char));
	char *tmps2=calloc(LENAME, sizeof(char));
	
	a.dist=Cout[n][m];
	
	// On remonte donc le tableau des coûts en prenant le choix qui coûte
	// le moins entre l'insertion dans S1 ou S1 ou la distance entre S1[i] et S2[i].
	int i=n; int j=m; int k=0;
	while(i>0 && j>0){
		
		float InserS1, InserS2, Substi;
		InserS1=Cout[i][j-1] + 1.5;
		InserS2=Cout[i-1][j] + 1.5;
		Substi=Cout[i-1][j-1] + DistCaract[Convert(s1.seq[i-1])][Convert(s2.seq[j-1])];
		
		float min=Min3(Substi, InserS1, InserS2);
		
		if(min==Substi){
			tmps1[k]=s1.seq[i-1];
			tmps2[k]=s2.seq[j-1];
			i--; j--; k++;
		}
		
		else if(min==InserS1){
			tmps1[k]='-';
			tmps2[k]=s2.seq[j-1];
			j--; k++;
		}
		
		else if(min==InserS2){
			tmps1[k]=s1.seq[i-1];
			tmps2[k]='-';
			i--; k++;
		}
	}
	
	while(i>=1){
		tmps1[k]=s1.seq[i-1];
		tmps2[k]='-';
		i--; k++;
	}
	
	while(j>=1){
		tmps1[k]='-';
		tmps2[k]=s2.seq[j-1];
		j--; k++;
	}
	
	tmps1[k]='\0'; tmps2[k]='\0';
	
	// Comme on part de la fin des séquences, on inverse les séquences modifiées.
	a.seq[0]=calloc(k+1, sizeof(char));
	a.seq[1]=calloc(k+1, sizeof(char));
	
	char *Invs1=InverseStr(tmps1);
	char *Invs2=InverseStr(tmps2);
	
	strcpy(a.seq[0], Invs1);
	strcpy(a.seq[1], Invs2);
	
	free(Invs1); free(Invs2);
	
	// On diminue la taille.
	a.len=k;
	
	// On libère Cout.
	for(int i=0; i<n+1; i++) free(Cout[i]);
	free(Cout);
	
	return a;
}

ALIGNEMENT AjoutSeq(ALIGNEMENT a, SEQUENCE appened){
	// Cette fonction permet d'ajouter une nouvelle séquence.
	
	// On enregistre toutes les distances entre 'appened' et les séquences déjà dans 'a'.
	float *TabD2=calloc(a.nbrSeq, sizeof(float));
	TestPtr(TabD2);
	for(int i=0; i<a.nbrSeq; i++){
		TabD2[i]=D2(a.seq[i], appened.seq);
	}
	
	// On trouve la minimum, pour savoir ou positionner la nouvelle séquence.
	float min=TabD2[0]; int pos=0;
	for(int i=1; i<a.nbrSeq; i++){
		if(TabD2[i]<min) {min=TabD2[i]; pos++;}
	}
	
	free(TabD2);
	
	// On prépare le nouvel alignement.
	ALIGNEMENT new;
	new.nbrSeq=a.nbrSeq+1;	
	
	new.seq=calloc(new.nbrSeq, sizeof(char*));
	for(int i=0; i<new.nbrSeq; i++){
		new.seq[i]=calloc(LENAME, sizeof(char));
	}
	new.S=calloc(new.nbrSeq, sizeof(SEQUENCE));
	
	new.dist=a.dist;
	new.len=a.len;
	
	// On ajoute au début de l'alignement.
	if(!pos){
		ALIGNEMENT tmp=Aligne2Seq(appened, a.S[0]);
		strcpy(new.seq[0], tmp.seq[0]);
		strcpy(new.seq[1], tmp.seq[1]);
		tmp.consensus=NULL;
		
		// On recopie le reste des séquences.
		for(int i=2; i<new.nbrSeq; i++){
			strcpy(new.seq[i],a.seq[i-1]);
		}
		
		// On enregistre les séquences originales.
		int j=1;
		// On ajoute la nouvelle au début.
		new.S[0]=appened;
		for(int i=0; i<a.nbrSeq; i++){
			new.S[j]=a.S[i];
			j++;
		}
		
		// On libére tmp.
		LibereAligne(tmp);
	}
	
	// On ajoute à la fin.
	else if(pos==a.nbrSeq-1){
		// On recopie les séquences avant de mettre la nouvelle séquence.	
		for(int i=0; i<a.nbrSeq-1; i++){
			strcpy(new.seq[i],a.seq[i]);
		}
		
		ALIGNEMENT tmp=Aligne2Seq(a.S[a.nbrSeq-1], appened);
		strcpy(new.seq[new.nbrSeq-2],tmp.seq[0]);
		strcpy(new.seq[new.nbrSeq-1],tmp.seq[1]);
		tmp.consensus=NULL;
		
		// On enregistre les séquences originales.
		for(int i=0; i<a.nbrSeq; i++){
			new.S[i]=a.S[i];
		}
		// On rajoute la nouvelle à la fin.
		new.S[a.nbrSeq]=appened;
		
		// On libére tmp.
		LibereAligne(tmp);
	}
	
	// On ajoute au milieu.
	else{
		// On recopie les séquences avant la nouvelle séquence.
		for(int i=0; i<=pos; i++){
			strcpy(new.seq[i],a.seq[i]);
		}
		
		ALIGNEMENT tmp=Aligne2Seq(a.S[pos], appened);
		strcpy(new.seq[pos],tmp.seq[0]);
		strcpy(new.seq[pos+1],tmp.seq[1]);
		tmp.consensus=NULL;
		
		// Puis on recopie la suite des séquences.
		for(int j=pos+1; j<new.nbrSeq-1; j++){
			strcpy(new.seq[j+1],a.seq[j]);
		}
		
		// On enregistre les séquences originales.
		for(int i=0; i<=pos; i++){
			new.S[i]=a.S[i];
		}
		new.S[pos+1]=appened;
		for(int j=pos+1; j<new.nbrSeq-1; j++){
			new.S[j+1]=a.S[j];
		}
		
		// On libére tmp.
		LibereAligne(tmp);
	}
	a.consensus=NULL;
	LibereAligne(a);
	
	return new;
}

ALIGNEMENT FoundConsensus(ALIGNEMENT a){
	// Cette fonction permet de trouver la séquence consensus d'un alignement.
	
	a.consensus=calloc(a.len+1, sizeof(char));
	
	for(int i=0; i<a.len; i++){
		a.consensus[i]=FreqCharMax(a, i);
	}
	
	return a;
}

ALIGNEMENT AligneFam(FAMILLE f){
	// Cette fonction permet de créer l'alignement au sein d'une famille.
	
	ALIGNEMENT a=Aligne2Seq(f.d[0].S1, f.d[0].S2);
	
	for(int i=1; i<f.nbrDist; i++){
		if(!(strcmp(f.d[i].S1.nomFic, f.seq))) a=AjoutSeq(a, f.d[i].S2);
		else a=AjoutSeq(a, f.d[i].S1);
	}
	a=FoundConsensus(a);
	
	return a;
}

ALIGNEMENT *AligneAllFam(FAMILLE *f, int nbrFam){
	// Cette fonction permet de créer tous les alignements a partir de toutes les familles.
	ALIGNEMENT *a=calloc(nbrFam, sizeof(ALIGNEMENT));
	
	for(int i=0; i<nbrFam; i++){
		a[i]=AligneFam(f[i]);
	}
	
	return a;
}

/*################# Fin manipulation des alignements #################*/


/*############################ Affichage #############################*/

void AffTab2D(int **t, int n, int m){
	for(int i=0; i<n+1; i++){
		for(int j=0; j<m+1; j++){
			printf("%d  ", t[i][j]);
		}
		printf("\n");
	}
}

/*###########################*/
void AffAlignDessin(ALIGNEMENT a){
	// Cette fonction permet de dessiner les alignements des séquences.
	int newSize=a.nbrSeq+(a.nbrSeq-1);
	
	// On trouve la taille de la séquence la plus grande pour créer un
	// tableau avec toutes les séquences et les alignements.
	int lenMax=a.len;
	for(int i=0; i<a.nbrSeq; i++){
		int len=(int) strlen(a.seq[i]);
		if(len>lenMax) lenMax=len;
	}
	
	// On alloue le tableau.
	char **align;
	align=calloc(newSize, sizeof(char**));
	for(int i=0; i<newSize; i++){
		align[i]=calloc(lenMax+2, sizeof(char));
	}
	
	// On recopie les séquences en laissant un espace vide entre chaque
	// pour les alignements.
	int j=0;
	for(int i=0; i<a.nbrSeq; i++){
		strcpy(align[j], a.seq[i]);
		j+=2;
	}
	
	// on trouve la taille minimum pour aligner les séquences et ne pas
	// aligner dans le vide.
	int lenMin=a.len;
	for(int i=0; i<a.nbrSeq; i++){
		int len=(int) strlen(a.seq[i]);
		if(len<lenMin) lenMin=len;
	}
	
	// Enfin on compare les séquences deux à deux et on rempli
	// le tableau entre les deux.
	for(int j=0; j<newSize-2; j+=2){
		for(int i=0; i<lenMin; i++){
			if(align[j][i]==align[j+2][i] && align[j][i]!='\0' && align[j][i]!='-'){
				align[j+1][i]='|';
			}
			else align[j+1][i]=' ';
		}
	}
	
	// On affiche.
	puts("");
	printf("nbrSeq=%d\n", a.nbrSeq);
	printf("Dist=%.2f\n", a.dist);
	puts("Alignement des séquences en cours...");
	
	for(int i=0; i<newSize; i++){
		printf("%s\n", align[i]);
	}
	printf("\nSéquence Consensus:\n%s\n", a.consensus);
	
	// On libère le tableau.
	for(int i=0; i<newSize; i++){
		free(align[i]);
	}
	free(align);
}

void AffAlignDessinAll (ALIGNEMENT *a, int nbrFam){
	for(int i=0; i<nbrFam; i++){
		AffAlignDessin(a[i]);
	}
}
/*###########################*/

/*###########################*/
void AffAlign (ALIGNEMENT a){
	puts("");
	printf("nbrSeq=%d\n", a.nbrSeq);
	printf("Dist=%.2f\n", a.dist);
	
	for(int i=0; i<a.nbrSeq; i++){
		printf("%s\n", a.seq[i]);
	}
	printf("\nSéquence Consensus:\n%s\n", a.consensus);
}

void AffAlignAll (ALIGNEMENT *a, int nbrFam){
	for(int i=0; i<nbrFam; i++){
		AffAlign(a[i]);
	}
}
/*###########################*/

/*########################### Fin affichage ##########################*/


/*########################### Libération #############################*/
void LibereAligne (ALIGNEMENT a){
	// Cette fonction permet de libérer un ALIGNEMENT.
	
	// Le (char *)
	for(int i=0; i<a.nbrSeq; i++){
		free(a.seq[i]);
	}
	free(a.seq);
	free(a.consensus);
	
	free(a.S);
}
	
void LibereAligneAll (ALIGNEMENT *a, int countFam){
	// Cette fonction permet de libérer tous les ALIGNEMENTS.
	
	for(int i=0; i<countFam; i++){
		LibereAligne(a[i]);
	}	
	free(a);
}
/*########################## Fin libération ##########################*/

