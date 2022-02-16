#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
/*Import des fonctions sur la table de hachage*/
#include "biblioH.h"
#include "entreeSortieH.h"
#include "manipulation_livres_biblioH.h"

/*Import des fonctions sur les listes chainées*/
#include "biblioLC.h"
#include "entreeSortieLC.h"
#include "manipulation_livres_biblio.h"


#define TAILLE_MAX 10000
#define DEBUT_ITER 1000
#define M 50
#define OCCURENCE 5.0
#define PAS 10

/*PLUSIEURS POSSIBILITÉS POUR CETTE QUESTION : ma méthode avec plusieurs occurences rend inévitable la fuite mémoire
(en soit on s'en fout on veut juste une belle courbe), si on en fait qu'une à chaque fois, alors on peut éviter les
fuites mémoires, je sais pas si ça joue sur le temps de calcul, anyways, vas le faire sur les ordis de la fac steuuuuplait,
histoire qu'il y ait quand même des résultats significatifs*/


int main(){
    /*Déclaration des bibliothèques où chercher*/
	Biblio* bibLC;
	BiblioH* bibH;

    /*Variables pour le temps*/
	clock_t temps_initial;
	clock_t temps_final;
	double temps_LC;
	double temps_H;

    /*Ouverture des fichiers où saisir les données*/
	FILE *f_lc = fopen("Evolution_Rech_Doublons_LC.txt", "w");
	FILE *f_h = fopen("Evolution_Rech_Doublons_H.txt", "w");
    
    for(int i = DEBUT_ITER ; i < TAILLE_MAX ; i = i + PAS){
        /*On ouvre le fichier avec les i premières lignes*/
        bibLC = charger_n_entrees("GdeBiblio.txt",i);
        bibH = charger_n_entreesH("GdeBiblio.txt",i,M);
        
        /*Avec LC*/
        temps_initial = clock();
        for(int j = 1 ; j < OCCURENCE; j++){
            recherche_pls_exemplaires(bibLC);
        }
        temps_final = clock();
        temps_LC = ((double)(temps_final - temps_initial)) / (CLOCKS_PER_SEC*OCCURENCE);

        /*Avec H*/
        temps_initial = clock();
        LivreH* listeH = recherche_pls_exemplairesH(bibH);
        temps_final = clock();
        temps_H = ((double)(temps_final - temps_initial)) / (CLOCKS_PER_SEC*OCCURENCE);

        /*Ecriture dans le fichier approprié*/
        fprintf(f_lc, "%i\t", i);
        fprintf(f_lc, "%.10f\n", temps_LC);
        fprintf(f_h,"%i\t", i);
        fprintf(f_h, "%.10f\n", temps_H);
        
        /*Libération de la mémoire allouée*/
        LivreH* tempo;
        while (listeH){
            tempo = listeH;
            listeH = listeH->suivant;
            liberer_livreH(tempo);
        }
        

        liberer_biblio(bibLC);
        liberer_biblioH(bibH);
    }
    fclose(f_lc);
    fclose(f_h);
        
}