#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"manipulation_livres_biblioH.h"
#include"biblioH.h"


/*D l’affichage d’un livre.*/

void afficher_livreH(LivreH* livre){
    printf("clef = %d / %d : %s de %s\n",livre->clef,livre->num,livre->titre,livre->auteur);
}

/*E l’affichage d’une bibliothèque.*/
void afficher_biblioH(BiblioH* bib){
    LivreH** tableauH = bib->T;
    LivreH* liste_courante;
    for (int i = 0; i<bib->m; i++){
        liste_courante = tableauH[i];
        while(liste_courante){
            afficher_livreH(liste_courante);
            liste_courante = liste_courante->suivant;
        }
    }
}

/*D la recherche d’un ouvrage par son numéro.*/

LivreH* recherche_numH(BiblioH* bib, int n){
    LivreH** tableauH = bib->T;
    LivreH* liste_courante;
    for (int i = 0; i<bib->m; i++){
        liste_courante = tableauH[i];
        while (liste_courante){
            if (liste_courante->num == n){
                return liste_courante;
            }
            liste_courante = liste_courante->suivant;
            printf("passage\n");
        }
    }
    return NULL;
}

/*E la recherche d’un ouvrage par son titre.*/
LivreH* recherche_titreH(BiblioH* bib, char* titre){
    LivreH** tableauH = bib->T;
    LivreH* liste_courante;
    for (int i = 0; i<bib->m; i++){
        liste_courante = tableauH[i];
        while (liste_courante){
            if (strcmp(liste_courante->titre,titre) == 0){
                return liste_courante;
            }
            liste_courante = liste_courante->suivant;
        }
    }
    return NULL;
}

/*D la recherche de tous les livres d’un même auteur (retourne une bibliothèque).*/

BiblioH* recherche_auteurH(BiblioH* bib,char* auteur){
    BiblioH* res = creer_biblioH(bib->m);
    int ou_chercher = fonctionHachage(fonctionClef(auteur),bib->m);
    LivreH* liste_auteur = (bib->T)[ou_chercher];
    while (liste_auteur){
        if (strcmp(liste_auteur->auteur,auteur)==0){
            insererH(res, liste_auteur->num, liste_auteur->titre, liste_auteur->auteur); 
        }
        liste_auteur = liste_auteur->suivant;
    }
    return res;
}



/*E la suppression d’un ouvrage (à partir de son numéro, son auteur et son titre).*/
void supprimer_livreH(BiblioH* bib, int num, char* auteur, char* titre){

    /*On récupère la position du livre dans la table*/
    int clef = fonctionHachage(fonctionClef(auteur), bib->m);

    /*On récupère la liste où se trouve le livre à supprimer*/
    LivreH* courant = (bib->T)[clef];
    LivreH* prec;

    /*Si le premier de la liste est celui qu'on veut supprimer, on modifie directement la tête de la liste*/

    if( (courant->num==num) && (strcmp(courant->auteur,auteur)==0) && (strcmp(courant->titre,titre)==0) ){
        (bib->T)[clef]=courant->suivant;
        free(courant);
    }
    else{
        /*Sinon, on peut passer ce premier élément et rentrer dans notre boucle*/
        prec = courant;
        courant = courant->suivant;
        int pas_trouve = 1;
        while ( (courant) && (pas_trouve) ){
            if((courant->num==num) && (strcmp(courant->auteur,auteur)==0) && (strcmp(courant->titre,titre)==0) ){
                prec->suivant = courant->suivant;
                pas_trouve = 0;
                free(courant);
            }
            courant = courant->suivant;
        }

        if(pas_trouve){
            printf("Erreur, livre à supprimer non présent dans la bibliothèque\n");
        }
                
    }

    

}



/*D la fusion de deux bibliothèques en ajoutant la deuxième bibliothèque à la première, et en
supprimant la deuxième.*/

void fusion_bibH(BiblioH* bib1, BiblioH* bib2){
    int i;

    LivreH** table_a_parcourir = bib2->T;
    LivreH** table_a_remplir = bib1->T;
    LivreH* courant;
    LivreH* suite;

     for(i = 0 ; i < bib2->m ; i++){
        courant = table_a_parcourir[i];
        int cle_remplissage = fonctionHachage(i,bib1->m);
        while(courant){
        suite = courant->suivant;
            courant->suivant = table_a_remplir[cle_remplissage];
            table_a_remplir[cle_remplissage]= courant;
            courant = suite;
        }
    }
    free(table_a_parcourir);
    free(bib2);
}

/*E + D ? la recherche de tous les ouvrages avec plusieurs exemplaires. Deux ouvrages sont identiques s’ils
ont le même auteur et le même titre (seul le numéro change). Cette fonction devra renvoyer
une liste comprenant tous les exemplaires de ces ouvrages, avec une complexité-temps pire cas
en O(n^2) où n est la taille de la bibliothèque.*/

int est_doublonH(LivreH* l1, LivreH* l2){
    return ((strcmp(l1->auteur,l2->auteur)==0)&&(strcmp(l1->titre,l2->titre)==0)&&(l1->num != l2->num));
}


LivreH* recherche_pls_exemplairesH(BiblioH* bib){
    int i;
    LivreH* res = NULL;
    LivreH* courant;
    LivreH* doublon_potentiel;
    LivreH* ajout;

    for(i = 0 ; i < bib->m ; i++){
        courant = (bib->T)[i];
        doublon_potentiel = courant->suivant;
        while(doublon_potentiel){

            if(est_doublonH(courant,doublon_potentiel)){
                ajout = creer_livreH(doublon_potentiel->num,doublon_potentiel->titre,doublon_potentiel->auteur);
                ajout->suivant = res;
                res = ajout;
            }
            doublon_potentiel = doublon_potentiel -> suivant;
        }
    }
    return res;  
}
