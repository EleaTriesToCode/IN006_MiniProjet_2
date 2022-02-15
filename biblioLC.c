#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioLC.h"

Livre* creer_livre(int num, char* titre, char* auteur){
	Livre* nouveau = (Livre*)(malloc(sizeof(Livre)));
	if (nouveau == NULL){
		printf("Erreur d'allocation mémoire !\n");
		return NULL;
	}
	nouveau->num = num;
	nouveau->titre = strdup(titre);
	nouveau->auteur = strdup(auteur);
	nouveau->suiv = NULL;
	return nouveau;
}


void liberer_livre(Livre* l){
	free(l->titre);
	free(l->auteur);
	free(l);
}



Biblio* creer_biblio(){
	Biblio* nouvelle_biblio = (Biblio*)(malloc(sizeof(Biblio)));
	if (nouvelle_biblio == NULL){
		printf("Erreur d'allocation mémoire !\n");
		return NULL;
	}
	nouvelle_biblio->L = NULL;
	return nouvelle_biblio;
}

void liberer_biblio(Biblio* b){
	Livre* livre_courant = b->L;
	Livre* tmp;
	while (livre_courant->suiv){
		tmp = livre_courant->suiv;
		liberer_livre(livre_courant);
		livre_courant = tmp;
	}
}

void inserer_en_tete(Biblio* b, int num, char* titre, char* auteur){
	Livre* nouveau = creer_livre(num,titre,auteur);
	nouveau->suiv = b->L;
	b->L = nouveau;
}

Livre* dupliquer (Livre* l){
	char* titre = strdup(l->titre);
    char* auteur = strdup(l->auteur);
    Livre* l_copie = (Livre*)malloc(sizeof(Livre));
	l_copie->auteur = auteur;
	l_copie->titre = titre;
	l_copie->num = l->num;
	l_copie ->suiv = NULL;
	return l_copie;
}
