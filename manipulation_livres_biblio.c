#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"manipulation_livres_biblio.h"
#include"biblioLC.h"



/*Fonction permettant d'afficher un livre sous le format num : "titre de auteur"*/
void afficher_livre(Livre* livre){
    printf("%d : %s de %s\n",livre->num,livre->titre,livre->auteur);
}

/*Fonction permettant d'afficher une bibliothèque, à raison d'un livre par ligne*/
void afficher_biblio(Biblio* bib){
    Livre* livre_courant = bib->L;
    while (livre_courant){
        afficher_livre(livre_courant);
        printf("\n");
        livre_courant = livre_courant->suiv;
    }
}


/*Fonction retournant le premier livre avec le numéro num dans la bibliothèque bib, NULL s'il n'est pas présent*/
Livre* recherche_num(Biblio*bib, int n){
    Livre* l_courant = bib->L;

    while ( (l_courant) && (l_courant->num != n )){
        l_courant = l_courant->suiv;
    }
    return l_courant;
}

/*Fonction retournant le premier livre avec le titre titre dans la bibliothèque bib, NULL s'il n'est pas présent*/
Livre* recherche_titre(Biblio* bib, char* titre){
    Livre* livre_courant = bib->L;
    while ( (livre_courant) && (strcmp(livre_courant->titre,titre) != 0)){
        livre_courant = livre_courant->suiv;
    }
    return livre_courant;
}


/*Fonction recherchant tous les livres d'un même auteur dans bib et les retournant 
sous la forme d'une bibliothèque (livres dupliqués)*/
Biblio* recherche_auteur(Biblio* bib,char* auteur){
    Biblio* bib_auteur = creer_biblio();
    Livre* l_courant = bib->L;
    Livre* l_auteur;
    while (l_courant){
        if((strcmp(l_courant->auteur,auteur))==0){
            inserer_en_tete(bib_auteur,l_courant->num,l_courant->titre,l_courant->auteur);
        }
        l_courant = l_courant->suiv;
    }
    return bib_auteur; 
}

/*Fonction supprimant un livre de numéro num, titre titre et auteur auteur d'une bibliothèque bib*/
void supprimer_livre(Biblio* bib, int num, char* auteur, char* titre){
    Livre* l_courant;
    Livre* l_prec;
    if ((bib != NULL) && (bib->L != NULL)){
        l_courant = bib->L;
        /*On vérifie la tête*/
        if ( (l_courant->num == num) && (strcmp(l_courant->titre,titre)==0) && (strcmp(l_courant->auteur,auteur)==0) ){
            Livre* tmp = l_courant->suiv;
            liberer_livre(l_courant);
            bib->L = tmp;
        }
        else{

            l_prec = l_courant;
            l_courant = l_courant->suiv;
            while ((l_courant) && !((l_courant->num == num) && (strcmp(l_courant->titre,titre)==0) && (strcmp(l_courant->auteur,auteur)==0) )){
                l_prec = l_courant;
                l_courant = l_courant->suiv;
            }
            if (l_courant){
                l_prec->suiv = l_courant->suiv;
                liberer_livre(l_courant);
            }
        }
    }
}

/*Fonction faisant la fusion de deux Biblio dans bib1 (modifiée par effet de bord) et libérant bib2*/
void fusion_bib(Biblio* bib1, Biblio* bib2){
    Livre* l_courant = bib1->L;
    while(l_courant->suiv){
        l_courant = l_courant->suiv;
    }
    l_courant->suiv = bib2->L;
    bib2->L = NULL;             
    free(bib2);
}

/*Fonction retournant si l2 est un doublon de l1 (sert de manière annexe dans recherche_pls_exemplaires)*/
int est_doublon(Livre* l1, Livre*l2){
    return ((strcmp(l1->auteur,l2->auteur)==0)&&(strcmp(l1->titre,l2->titre)==0)&&(l1->num != l2->num));
}

/*Fonction donnant une liste des livres présents en plusieurs exemplaires dans la bibliothèque bib*/
Livre* recherche_pls_exemplaires(Biblio* bib){
    Livre* res = NULL;
    Livre* nouvelle_tete;

    Livre* courant_1 = bib->L;
    Livre* courant_2;

    while (courant_1){
        courant_2 = bib->L;
        while(courant_2){
            if(est_doublon(courant_1,courant_2)){
                nouvelle_tete = dupliquer(courant_1);
                nouvelle_tete->suiv = res;
                res = nouvelle_tete;
                break;
            }
            courant_2 = courant_2->suiv;
        }
        courant_1 = courant_1->suiv;
    }
        
    return res; 
}

