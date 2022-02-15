#include<stdio.h>
#include<stdlib.h>
#include "biblioH.h"

BiblioH* charger_n_entreesH(char* nomfic, int n, int m){
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

    BiblioH* bibH = creer_biblioH(m);

    /*On parcourt le fichier*/

    while ( (fgets(ligne,256,f))  && (i<n) ){
        if(sscanf(ligne,"%d %s %s",&num,titre,auteur)==3){
            insererH(bibH, num, titre, auteur);
        }
        else{
            printf("Erreur de formatage du fichier à la ligne %d!\n",i);        //On a choisi de continuer à lire le fichier en cas de fautes de frappe
        }
        i = i+1;        
    }

    fclose(f);
    return bibH;
}



void enregistrer_biblioH(BiblioH *bH, char* nomfic){
	FILE* fichier = fopen(nomfic,"w");
	if (fichier == NULL){
		printf("Erreur à l'ouverture du fichier !\n");
	}
	LivreH** tableauH = bH->T;
	LivreH* liste_courante;
	for (int i = 0; i < bH->nE; i++){
		liste_courante = tableauH[i];
		while (liste_courante){
			fprintf(fichier, "%d %s %s\n", liste_courante->num, liste_courante->titre, liste_courante->auteur);
			liste_courante = liste_courante->suivant;
		}
	}
	fclose(fichier);	
}
