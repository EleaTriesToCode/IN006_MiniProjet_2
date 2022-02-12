#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>
#include"biblioH.h"

int fonctionClef(char* auteur){
    int res = 0;
    int i = 0;
    while(auteur[i]){
        res += (int) auteur[i];
        i++;
    }
    return res;
}

LivreH* creer_livre(int num,char* titre,char* auteur){

    LivreH* res = (LivreH*) malloc(sizeof(LivreH));
    res->clef = fonctionClef(auteur);
    res->num = num;
    res->titre = strdup(titre);
    res->auteur = strdup(auteur);
    res->suivant = NULL;

    return res;
}

void liberer_livre(LivreH* l){
    free(l->titre);
    free(l->auteur);
    free(l->suivant);
    free(l);
}

BiblioH* creer_biblio(int m){
    BiblioH* res = (BiblioH*) malloc(sizeof(BiblioH));
    res->nE = 0;
    res->m = m;
    res->T = (LivreH**)(malloc(m*sizeof(LivreH*)));
    return res;
}

void liberer_biblio(BiblioH* b){
    LivreH** tableauH = b->T;
    LivreH* liste_courante;
    LivreH* tmp;
    for (int i = 0; i < b->nE; i++){
        liste_courante = tableauH[i];
        while (liste_courante){
            tmp = liste_courante->suivant;
            liberer_livre(liste_courante);
            liste_courante = tmp;
        }
    } free(tableauH);
    free(b);
}

int fonctionHachage(int clef, int m){
    float a = (sqrt(5)-1)/2;
    float ka = clef*a;
    return floor(m*(ka-floor(ka)));
}

void inserer(BiblioH* b, int num, char* titre, char* auteur){
    LivreH* livre = creer_livre(num,titre,auteur);
    int pos = fonctionHachage(livre->clef, b->m);
    LivreH* liste_clefH = (b->T)[pos];
    livre->suivant = liste_clefH;
    (b->T)[pos] = livre;
}
