#include<stdio.h>
#include<stdlib.h>
#include"manipulation_livres_biblio.h"
#include"biblioLC.h"


/*D l’affichage d’un livre.*/

void afficher_livre(Livre* livre){
    printf("%d : %s de %s\n",livre->num,livre->titre,livre->auteur);
}

/*E l’affichage d’une bibliothèque.*/

/*D la recherche d’un ouvrage par son numéro.*/

Livre* recherche_num(Biblio*bib, int n){
    Livre* l_courant = bib->L;

    while ( (l_courant) && (l_courant->num != n )){
        l_courant = l_courant->suiv;
    }
    return l_courant;
}

/*E la recherche d’un ouvrage par son titre.*/

/*D la recherche de tous les livres d’un même auteur (retourne une bibliothèque).*/

Biblio* recherche_auteur(Biblio* bib,char* auteur){
    Biblio* bib_auteur = creer_biblio();
    Livre* l_courant = bib->L;
    Livre* l_auteur;
    while (l_courant){
        if(strcmp(l_courant->auteur,auteur)){
            char* titre = strdup(l_courant->auteur);
            char* auteur = strdup(l_courant->auteur);
            inserer_en_tete(bib_auteur,l_courant->num,titre,auteur);
        }
        l_courant = l_courant->suiv;
    }
    return bib_auteur    
}

/*E la suppression d’un ouvrage (à partir de son numéro, son auteur et son titre).*/

/*D la fusion de deux bibliothèques en ajoutant la deuxième bibliothèque à la première, et en
supprimant la deuxième.*/

void fusion_bib(Biblio* bib1, Biblio* bib2){
    Livre* l_courant = bib1->L;
    while(l_courant->suiv){
        l_courant = l_courant->suiv;
    }
    l_courant->suiv = bib2->L;
    bib2->L = NULL;             //Oulah...
    free(bib2);
}

/*E + D ? la recherche de tous les ouvrages avec plusieurs exemplaires. Deux ouvrages sont identiques s’ils
ont le même auteur et le même titre (seul le numéro change). Cette fonction devra renvoyer
une liste comprenant tous les exemplaires de ces ouvrages, avec une complexité-temps pire cas
en O(n 2 ) où n est la taille de la bibliothèque.*/