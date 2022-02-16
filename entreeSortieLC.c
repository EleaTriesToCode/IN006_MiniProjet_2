#include<stdio.h>
#include<stdlib.h>
#include "biblioLC.h"


Biblio* charger_n_entrees(char* nomfic, int n){
    if (n ==0){
        printf("On ne peut pas charger 0 entrées !\n");
        return NULL;
    }
    FILE* f = fopen(nomfic,"r");

    if (f == NULL){
        printf("Erreur à l'ouverture du fichier\n");
        return NULL;
    }

    /*Variables permettant de parcourir le fichier*/
    char ligne[256];
    int i = 0;

    /*Variables plus spécifiques à la structure à créer*/

    int num;
    char titre[100];
    char auteur[100];

    Biblio* bib = creer_biblio();

    /*On parcourt le fichier*/

    while ( (fgets(ligne,256,f))  && (i<n) ){
        if(sscanf(ligne,"%d %s %s",&num,titre,auteur)==3){
            inserer_en_tete(bib,num,titre,auteur);
        }
        else{
            printf("Erreur de formatage du fichier à la ligne %d!\n",i);        //On a choisi de continuer à lire le fichier en cas de fautes de frappe
        }
        i = i+1;        
    }

    fclose(f);
    return bib;

}


void enregistrer_biblio(Biblio *b, char* nomfic){
	FILE* fichier = fopen(nomfic,"w");
	if (fichier == NULL){
		printf("Erreur à l'ouverture du fichier !\n");
	}
	Livre* livre_courant = b->L;
	while (livre_courant){
		fprintf(fichier, "%d %s %s\n", livre_courant->num, livre_courant->titre, livre_courant->auteur);
		livre_courant = livre_courant->suiv;
	}
	fclose(fichier);	
}
