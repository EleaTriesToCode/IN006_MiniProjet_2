#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>
#include"biblioH.h"


/*Fonction retournant la clef associée à l'auteur en faisant la somme des valeurs ASCII de chaque lettre*/
int fonctionClef(char* auteur){
    int res = 0;
    int i = 0;
    while(auteur[i]){
        res += (int) auteur[i];
        i++;
    }
    return res;
}

/*Fonction permettant de créer un livre pour la table de hachage*/
LivreH* creer_livreH(int num,char* titre,char* auteur){

    LivreH* res = (LivreH*) malloc(sizeof(LivreH));
    res->clef = fonctionClef(auteur);
    res->num = num;
    res->titre = strdup(titre);
    res->auteur = strdup(auteur);
    res->suivant = NULL;

    return res;
}

/*Fonction libérant l'espace mémoire alloué à l*/
void liberer_livreH(LivreH* l){
    free(l->titre);
    free(l->auteur);
    free(l);
}

/*Fonction créant une bibliothèque avec une table de taille m*/
BiblioH* creer_biblioH(int m){
    BiblioH* res = (BiblioH*) malloc(sizeof(BiblioH));
    res->nE = 0;
    res->m = m;
    res->T = (LivreH**)(malloc(m*sizeof(LivreH*)));
    for(int i = 0 ; i < m ; i++){
        (res->T)[i] = NULL;
    }
    return res;
}


/*Fonction permettant de libérer la mémoire occupée par une bibliothèque.*/
void liberer_biblioH(BiblioH* b){
    LivreH** tableauH = b->T;
    LivreH* liste_courante;
    LivreH* tmp;
    for (int i = 0; i < b->m; i++){
        liste_courante = tableauH[i];
        while (liste_courante){
            tmp = liste_courante;
            liste_courante = liste_courante->suivant;
            liberer_livreH(tmp);
        }
    }
    free(b->T);
    free(b);
}

/*Fonction permettant d'obtenir la clé hachée d'un livre à partir de sa clé et de la taille m de la table*/
int fonctionHachage(int clef, int m){
    float a = (sqrt(5)-1)/2;
    float ka = clef*a;
    return floor(m*(ka-floor(ka)));
}

/*Fonction permettant d'ajouter un livre à la bibliothèque*/
void insererH(BiblioH* b, int num, char* titre, char* auteur){
    LivreH* livre = creer_livreH(num,titre,auteur);

    int pos = fonctionHachage(livre->clef, b->m);
    LivreH* liste_clefH = (b->T)[pos];
    livre->suivant = liste_clefH;
    (b->T)[pos] = livre;
    b->nE++;
}

