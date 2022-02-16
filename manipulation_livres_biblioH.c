#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"manipulation_livres_biblioH.h"
#include"biblioH.h"

/*Fonction permettant d'afficher un livre sous le format "clef  = clef / num : titre de auteur"*/
void afficher_livreH(LivreH* livre){
    printf("clef = %d / %d : %s de %s\n",livre->clef,livre->num,livre->titre,livre->auteur);
}

/*Fonction permettant d'afficher une bibliothèque, à raison d'un livre par ligne*/
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

/*Fonction retournant le premier livre avec le numéro num dans la bibliothèque bib, NULL s'il n'est pas présent*/
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
        }
    }
    return NULL;
}

/*Fonction retournant le premier livre avec le titre titre dans la bibliothèque bib, NULL s'il n'est pas présent*/
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


/*Fonction recherchant tous les livres d'un même auteur dans bib et les retournant 
sous la forme d'une bibliothèque (livres dupliqués)*/
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


/*Fonction supprimant un livre de numéro num, titre titre et auteur auteur d'une bibliothèque bib*/
void supprimer_livreH(BiblioH* bib, int num, char* auteur, char* titre){

    /*On récupère la position du livre dans la table*/
    int clef = fonctionHachage(fonctionClef(auteur), bib->m);

    /*On récupère la liste où se trouve le livre à supprimer*/
    LivreH* courant = (bib->T)[clef];
    LivreH* prec;

    /*Si le premier de la liste est celui qu'on veut supprimer, on modifie directement la tête de la liste*/

    if( (courant->num==num) && (strcmp(courant->auteur,auteur)==0) && (strcmp(courant->titre,titre)==0) ){
        (bib->T)[clef]=courant->suivant;
        liberer_livreH(courant);
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
                liberer_livreH(courant);
            }
            courant = courant->suivant;
        }

        if(pas_trouve){
            printf("Erreur, livre à supprimer non présent dans la bibliothèque\n");
        }
                
    }

    

}



/*Fonction faisant la fusion de deux Biblio dans bib1 (modifiée par effet de bord) et libérant bib2*/
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

/*Fonction vérifiant que deux livres sont doublons l'un de l'autre*/
int est_doublonH(LivreH* l1, LivreH* l2){
    return ((strcmp(l1->auteur,l2->auteur)==0)&&(strcmp(l1->titre,l2->titre)==0)&&(l1->num != l2->num));
}

/*Fonction donnant une liste des livres présents en plusieurs exemplaires dans la bibliothèque bib*/
LivreH* recherche_pls_exemplairesH(BiblioH* bib){
    int i;
    int notre_courant_est_doublon;
    LivreH* res = NULL;
    LivreH* courant;
    LivreH* doublon_potentiel;
    LivreH* ajout;
    for(i = 0 ; i < bib->m ; i++){
        courant = (bib->T)[i];
        notre_courant_est_doublon = 0;
        doublon_potentiel = courant;            //On peut dès le courant car son numéro lui étant identique, il ne sera pas compté comme doublon
        while(doublon_potentiel){
            if(est_doublonH(courant,doublon_potentiel)){
                ajout = creer_livreH(doublon_potentiel->num,doublon_potentiel->titre,doublon_potentiel->auteur);
                ajout->suivant = res;
                res = ajout;
                notre_courant_est_doublon = 1;
            }
            doublon_potentiel = doublon_potentiel -> suivant;
        }
        if(notre_courant_est_doublon){      //Si le courant qu'on a trouvé a des doublons, il faut aussi l'ajouter !
            ajout = creer_livreH(courant->num,courant->titre,courant->auteur);
            ajout->suivant = res;
            res = ajout;
        }
    }
    return res;  
}
