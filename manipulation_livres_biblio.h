#include<stdio.h>
#include<stdlib.h>
#include"biblioLC.h"
#ifndef MANIP_LIVRE_BIB
#define MANIP_LIVRE_BIB

/*Fonction permettant d'afficher un livre sous le format num : "titre de auteur"*/
void afficher_livre(Livre* livre);

/*Fonction permettant d'afficher une bibliothèque, à raison d'un livre par ligne*/
void afficher_biblio(Biblio* bib);

/*Fonction retournant le premier livre avec le numéro num dans la bibliothèque bib, NULL s'il n'est pas présent*/
Livre* recherche_num(Biblio*bib, int n);

/*Fonction retournant le premier livre avec le titre titre dans la bibliothèque bib, NULL s'il n'est pas présent*/
Livre* recherche_titre(Biblio* bib, char* titre);

/*Fonction recherchant tous les livres d'un même auteur dans bib et les retournant 
sous la forme d'une bibliothèque (livres dupliqués)*/
Biblio* recherche_auteur(Biblio* bib,char* auteur);

/*Fonction supprimant un livre de numéro num, titre titre et auteur auteur d'une bibliothèque bib*/
void supprimer_livre(Biblio* bib, int num, char* auteur, char* titre);

/*Fonction faisant la fusion de deux Biblio dans bib1 (modifiée par effet de bord) et libérant bib2*/
void fusion_bib(Biblio* bib1, Biblio* bib2);

/*Fonction retournant si l2 est un doublon de l1 (sert de manière annexe dans recherche_pls_exemplaires)*/
int est_doublon(Livre* l1, Livre*l2);

/*Fonction donnant une liste des livres présents en plusieurs exemplaires dans la bibliothèque bib*/
Livre* recherche_pls_exemplaires(Biblio* bib);



#endif


