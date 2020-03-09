#include "famille.h"

int main(int agrc, char **argv){
	
	int nbrFile=0;
	int nbrFam=0; int nbrFam2=0; 
	int comptDist=0; int comptDist2=0;
	
	char pwd[LENAME];
	getcwd(pwd, LENAME);
	strcat(pwd, argv[1]);
	
	SEQUENCE *S=InitSeq(pwd, &nbrFile);
	//~ AffSeq(S, nbrFile);

	DISTANCE **D1=CalculeD1(S, nbrFile);
	//~ EcrireDistTriang(D1, nbrFile);
	
	DISTANCE **Dist2=CalculeD2(S, nbrFile);
	//~ EcrireDistTriang(Dist2, nbrFile);
	
/*####################################################################*/
	
	FAMILLE *F=InitFamille(D1, S, nbrFile, &nbrFam, &comptDist);
	//~ AffFam(F, nbrFam);
	
	FAMILLE *F2=InitFamille(Dist2, S, nbrFile, &nbrFam2, &comptDist2);
	AffFam(F, nbrFam2);

/*####################################################################*/
	
	char *DossFam="famille"; char *DossSeq=(argv[1]+1);
	
	//~ CreatDoss(F, nbrFam, DossFam);
	//~ CopieSeqDoss(F, nbrFam, DossFam, DossSeq);
	//~ DellDoss(F, nbrFam, DossFam);
	
	CreatDoss(F2, nbrFam2, DossFam);
	CopieSeqDoss(F2, nbrFam2, DossFam, DossSeq);
	DellDoss(F2, nbrFam2, DossFam);

/*####################################################################*/
	
	LibereSeqAll(S, nbrFile);
	
	LibereDistAll(D1, nbrFile);
	LibereDistAll(Dist2, nbrFile);
	
	LibereFamAll(F, nbrFam);
	LibereFamAll(F2, nbrFam2);
	
/*####################################################################*/
	
	exit(0);
}
