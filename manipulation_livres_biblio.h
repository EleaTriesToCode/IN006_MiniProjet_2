#include<stdio.h>
#include<stdlib.h>
#include"biblioLC.h"
#ifndef MANIP_LIVRE_BIB
#define MANIP_LIVRE_BIB

/*Fonction permettant d'afficher un livre sous le format num : "titre de auteur"*/
void afficher_livre(Livre* livre);

/*Fonction retournant le premier livre avec le numéro num dans la bibliothèque bib, NULL s'il n'est pas présent*/
Livre* recherche_num(Biblio*bib, int n);

/*Fonction recherchant tous les livres d'un même auteur dans bib et les retournant 
sous la forme d'une bibliothèque (livres dupliqués)*/
Biblio* recherche_auteur(Biblio* bib,char* auteur);

/*Fonction faisant la fusion de deux Biblio dans bib1 (modifiée par effet de bord) et libérant bib2*/
void fusion_bib(Biblio* bib1, Biblio* bib2);

#endif


