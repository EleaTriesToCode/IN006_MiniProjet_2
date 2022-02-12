#include<stdio.h>
#include<stdlib.h>
#include"biblioH.h"
#ifndef MANIP_LIVRE_BIBH
#define MANIP_LIVRE_BIBH

/*Fonction permettant d'afficher un livre sous le format num : "titre de auteur"*/
void afficher_livre(LivreH* livre);

/*Fonction permettant d'afficher une bibliothèque, à raison d'un livre par ligne*/
void afficher_biblio(BiblioH* bib);

/*Fonction retournant le premier livre avec le numéro num dans la bibliothèque bib, NULL s'il n'est pas présent*/
LivreH* recherche_num(BiblioH*bib, int n);

/*Fonction retournant le premier livre avec le titre titre dans la bibliothèque bib, NULL s'il n'est pas présent*/
LivreH* recherche_titre(BiblioH* bib, char* titre);

/*Fonction recherchant tous les livres d'un même auteur dans bib et les retournant 
sous la forme d'une bibliothèque (livres dupliqués)*/
BiblioH* recherche_auteur(BiblioH* bib,char* auteur);

/*Fonction supprimant un livre de numéro num, titre titre et auteur auteur d'une bibliothèque bib*/
void supprimer_livre(BiblioH** bib, int num, char* auteur, char* titre);

/*Fonction faisant la fusion de deux Biblio dans bib1 (modifiée par effet de bord) et libérant bib2*/
void fusion_bib(BiblioH* bib1, BiblioH* bib2);

/*Fonction vérifiant que deux livres sont doublons l'un de l'autre*/
int est_doublon(LivreH* l1, LivreH*l2);

/*Fonction donnant une liste des livres présents en plusieurs exemplaires dans la bibliothèque bib*/
LivreH* recherche_pls_exemplaires(BiblioH* bib);

#endif
