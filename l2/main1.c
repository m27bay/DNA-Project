#include "distance.h"

int main(int argc, char **argv){
	
	int nbrFile=0;
	
	// On stock le chemin d'accès pour aller lire les séquences.
	char pwd[LENAME];
	getcwd(pwd, LENAME); // Permet d'obtenir le chemin d'acces du programme.
	strcat(pwd, argv[1]);
	
/*####################################################################*/

	SEQUENCE *S=InitSeq(pwd, &nbrFile);
	TrieSeqCroissant(S, nbrFile);
	AffSeq(S, nbrFile);
	
	DISTANCE **D1=CalculeD1(S, nbrFile);
	//~ EcrireDistTriang(D1, nbrFile);
	
	DISTANCE **D2=CalculeD2(S, nbrFile);
	EcrireDistTriang(D2, nbrFile);
	
/*####################################################################*/
	
	LibereSeqAll(S, nbrFile);
	
	LibereDistAll(D1, nbrFile);
	LibereDistAll(D2, nbrFile);
	
/*####################################################################*/

	exit(0);
}
