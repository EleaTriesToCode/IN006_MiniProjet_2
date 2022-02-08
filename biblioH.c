#include<stdio.h>
#include<stdlib.h>
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
    free(l);
}

BiblioH* creer_biblio(int m){
    BiblioH* res = (BiblioH*) malloc(sizeof(BiblioH));
    res->nE = 0;
    res->m = m;
    res->T = NULL;
    return res;
}

void liberer_biblio(BiblioH* b){
    
    LivreH* l_courant = *(b->T);
    LivreH* tmp;
    /*On libère la table de hachage livres par livres*/
    while(l_courant){
        l_courant = tmp;
        l_courant = l_courant->suivant;
        liberer_livre(tmp);
    }
    /*On peut libérer le tableau de pointeurs et le reste de la structure*/
    free(b->T);
    free(b);

}