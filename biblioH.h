#include<stdio.h>
#include<stdlib.h>
#ifndef BIBLIOH_H
#define BIBLIOH_H

/* Type def d'une structure de livre avec une table de hachage */
typedef struct livreh {
    int clef ;
    int num;
    char* titre;
    char* auteur;
    struct livreh * suivant ;
} LivreH ;

typedef struct table {
    int nE ; /*nombre d’elements contenus dans la table de hachage */
    int m ; /*taille de la table de hachage */
    LivreH ** T ; /*table de hachage avec resolution des collisions par chainage */
} BiblioH ;

/*Fonction retournant la clef associée à l'auteur en faisant la somme des valeurs ASCII de chaque lettre*/
int fonctionClef(char* auteur);

/*Fonction permettant de créer un livre pour la table de hachage*/
LivreH* creer_livreH(int num,char* titre,char* auteur);

/*Fonction libérant l'espace mémoire alloué à l*/
void liberer_livreH(LivreH* l);

/*Fonction créant une bibliothèque avec une table de taille m*/
BiblioH* creer_biblioH(int m);

/*Fonction permettant de libérer la mémoire occupée par une bibliothèque.*/
void liberer_biblioH(BiblioH* b);

/*Fonction permettant d'obtenir la clé hachée d'un livre à partir de sa clé et de la taille m de la table*/
int fonctionHachage(int cle, int m);

/*Fonction permettant d'ajouter un livre à la bibliothèque*/
void insererH(BiblioH* b, int num, char* titre, char* auteur);

#endif
