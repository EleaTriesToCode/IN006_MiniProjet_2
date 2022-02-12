#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"manipulation_livres_biblio.h"
#include"biblioLC.h"


/*D l’affichage d’un livre.*/

void afficher_livre(LivreH* livre){
    printf("clef = %d / %d : %s de %s\n",livre->clef,livre->num,livre->titre,livre->auteur);
}

/*E l’affichage d’une bibliothèque.*/
void afficher_biblio(BiblioH* bib){
    LivreH** tableauH = bib->T;
    LivreH* liste_courante;
    for (int i = 0; i<bib->nE; i++){
        liste_courante = tableauH[i];
        while (liste_courante){
            afficher_livre(liste_courante);
            liste_courante = liste_courante->suivant;
        }
    }
}

/*D la recherche d’un ouvrage par son numéro.*/

LivreH* recherche_num(Biblio*bib, int n){
    LivreH** tableauH = bib->T;
    LivreH* liste_courante;
    for (int i = 0; i<bib->nE; i++){
        liste_courante = tableauH[i];
        while (liste_courante){
            if (liste_courante->num == n){
                return liste_courante;
            }
            liste_courante = liste_courante->suivant;
        }
    }
}

/*E la recherche d’un ouvrage par son titre.*/
LivreH* recherche_titre(Biblio* bib, char* titre){
    LivreH** tableauH = bib->T;
    LivreH* liste_courante;
    for (int i = 0; i<bib->nE; i++){
        liste_courante = tableauH[i];
        while (liste_courante){
            if (strcmp(liste_courante->titre,titre) == 0){
                return liste_courante;
            }
            liste_courante = liste_courante->suivant;
        }
    }
}

/*D la recherche de tous les livres d’un même auteur (retourne une bibliothèque).*/

BiblioH* recherche_auteur(BiblioH* bib,char* auteur){
    BiblioH* res = creer_biblio(bib->m);
    int ou_chercher = fonctionHachage(fonctionClef(auteur),bib->m);
    LivreH* liste_auteur = (bib->T)[ou_chercher];
    while (liste_auteur){
        if (strcmp(liste_auteur->auteur,auteur)==0){
            inserer(res, liste_auteur->num, liste_auteur->titre, liste_auteur->auteur); 
        }
        liste_auteur = liste_auteur->suivant;
    }
    return res;
}

/*E la suppression d’un ouvrage (à partir de son numéro, son auteur et son titre).*/
void supprimer_livre(BiblioH** bib, int num, char* auteur, char* titre){
    

}

/*D la fusion de deux bibliothèques en ajoutant la deuxième bibliothèque à la première, et en
supprimant la deuxième.*/

void fusion_bib(BiblioH* bib1, BiblioH* bib2){
    
}

/*E + D ? la recherche de tous les ouvrages avec plusieurs exemplaires. Deux ouvrages sont identiques s’ils
ont le même auteur et le même titre (seul le numéro change). Cette fonction devra renvoyer
une liste comprenant tous les exemplaires de ces ouvrages, avec une complexité-temps pire cas
en O(n^2) où n est la taille de la bibliothèque.*/

Livre* recherche_pls_exemplaires(BiblioH* bib){
    

}