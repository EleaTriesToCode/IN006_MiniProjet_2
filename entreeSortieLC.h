#include<stdio.h>
#include<stdlib.h>
#include "biblioLC.h"

#ifndef ENTREE_SORTIE_LC
#define ENTREE_SORTIE_LC


/*Fonction permettant de charger n entrées à partir du fichier d'adresse nomfic dans une bibliothèque et la retournant*/
Biblio* charger_n_entrees(char* nomfic, int n);

/*Fonction permettant d'enregistrer une bibliothèque b dans un fichier d'adresse nomfic*/
void enregistrer_biblio(Biblio *b, char* nomfic);

#endif