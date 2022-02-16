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


#define TAILLE 200
#define M 19


int main(){
    	/*Créations des bibliothèques où chercher*/
	Biblio* bibLC;
	BiblioH* bibH;

    FILE* fichier_bib = fopen("GdeBiblio.txt","r");

    /*Variables pour le temps*/
	clock_t temps_initial;
	clock_t temps_final;
	double temps_LC;
	double temps_H;

    /*Ouverture des fichiers où stocker les temps de calcul pour le gnuplot*/

	/*Avec numéro, livres présents*/
	FILE *f_num_p = fopen("Comparaison_Numero_Present.txt", "w");

	/*Avec titre, livres présents*/
	FILE *f_titre_p = fopen("Comparaison_Titre_Present.txt", "w");

	/*Avec auteur, livres présents*/
	FILE *f_auteur_p = fopen("Comparaison_Auteur_Present.txt", "w");

	/*Avec numéro, livres absents*/
	FILE *f_num_a = fopen("Comparaison_Numero_Absent.txt", "w");

	/*Avec titre, livres absents*/
	FILE *f_titre_a = fopen("Comparaison_Titre_Absent.txt", "w");

	/*Avec auteur, livres absents*/
	FILE *f_auteur_a = fopen("Comparaison_Auteur_Absent.txt", "w");


    /*On va prendre une centaine de livres, présents dans la bibliothèque, dans laquelle on va piocher à chaque
    tour de boucle un livre aléatoire à rechercher*/
    char titre_a_chercher[TAILLE][256];
    char auteur_a_chercher[TAILLE][256];
    int numero;
    char ligne[256];

    int i = 0;

    while(fgets(ligne,256,fichier_bib)&& (i < TAILLE)){
        if(!(sscanf(ligne,"%d %s %s",&numero,titre_a_chercher[i],auteur_a_chercher[i])==3)){
            printf("Erreur dans le fichier !\n");
            return 0;
        }
        i++;
    }

    char* titre_absent = "TractatusLogicoPhilosophicus";
    char* auteur_absent = "AndreComteSponville";

    for(i = 1; i < TAILLE ; i ++){
        bibLC = charger_n_entrees("GdeBiblio.txt",i);
        bibH = charger_n_entreesH("GdeBiblio.txt",i,M);

        /*Recherche d'éléments présents*/
        /*Recherche par numéro*/

        numero = rand()%(i+1);

        /*Avec LC*/
		temps_initial = clock();
		recherche_num(bibLC, numero);
		temps_final = clock();
		temps_LC = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;

		/*Avec H*/
		temps_initial = clock();
		recherche_numH(bibH, numero);
		temps_final = clock();
		temps_H = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;

		/*Ecriture dans le fichier approprié*/
		fprintf(f_num_p, "%i\t", i);
		fprintf(f_num_p, "%f\t", temps_LC);
		fprintf(f_num_p, "%f\n", temps_H);


        /*Recherche par titre*/

        /*Avec LC*/
        temps_initial = clock();
        recherche_titre(bibLC,titre_a_chercher[numero]);
        temps_final = clock();
        temps_LC = ((double)(temps_final - temps_initial))/ CLOCKS_PER_SEC;

        /*Avec H*/
        temps_initial = clock();
        recherche_titreH(bibH,titre_a_chercher[numero]);
        temps_final = clock();
        temps_H = ((double)(temps_final - temps_initial))/ CLOCKS_PER_SEC;

        /*Ecriture dans le fichier approprié*/
		fprintf(f_titre_p, "%i\t", i);
		fprintf(f_titre_p, "%f\t", temps_LC);
		fprintf(f_titre_p, "%f\n", temps_H);


        /*Recherche des livres d'un même auteur*/

        /*Avec LC*/
        srand(i);
        temps_initial = clock();
        for(int j = 0 ; j < 500 ; j++){
            recherche_auteur(bibLC,auteur_a_chercher[(rand()%i)]);
        }
        temps_final = clock();
        temps_LC = ((double)(temps_final - temps_initial))/ (CLOCKS_PER_SEC*500.0);

        /*Avec H*/
        srand(i);
        temps_initial = clock();
        for(int j = 0 ; j< 500 ; j++){
            recherche_auteurH(bibH,auteur_a_chercher[(rand()%i)]);
        }
        temps_final = clock();
        temps_H = ((double)(temps_final - temps_initial))/ (CLOCKS_PER_SEC*500.0);

        /*Ecriture dans le fichier approprié*/
		fprintf(f_auteur_p, "%i\t", i);
		fprintf(f_auteur_p, "%.15f\t", temps_LC);
		fprintf(f_auteur_p, "%.15f\n", temps_H);

        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        /*Recherche d'éléments absents*/
        /*Recherche par numéro*/

        numero = -1;

        /*Avec LC*/
		temps_initial = clock();
		recherche_num(bibLC, numero);
		temps_final = clock();
		temps_LC = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;

		/*Avec H*/
		temps_initial = clock();
		recherche_numH(bibH, numero);
		temps_final = clock();
		temps_H = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;

		/*Ecriture dans le fichier approprié*/
		fprintf(f_num_a, "%i\t", i);
		fprintf(f_num_a, "%f\t", temps_LC);
		fprintf(f_num_a, "%f\n", temps_H);


        /*Recherche par titre*/

        /*Avec LC*/
        temps_initial = clock();
        recherche_titre(bibLC,titre_absent);
        temps_final = clock();
        temps_LC = ((double)(temps_final - temps_initial))/ CLOCKS_PER_SEC;

        /*Avec H*/
        temps_initial = clock();
        recherche_titreH(bibH,titre_absent);
        temps_final = clock();
        temps_H = ((double)(temps_final - temps_initial))/ CLOCKS_PER_SEC;

        /*Ecriture dans le fichier approprié*/
		fprintf(f_titre_a, "%i\t", i);
		fprintf(f_titre_a, "%f\t", temps_LC);
		fprintf(f_titre_a, "%f\n", temps_H);


        /*Recherche des livres d'un même auteur*/

        /*Avec LC*/
        temps_initial = clock();
        recherche_auteur(bibLC,auteur_absent);
        temps_final = clock();
        temps_LC = ((double)(temps_final - temps_initial))/ CLOCKS_PER_SEC;

        /*Avec H*/

        temps_initial = clock();
        recherche_auteurH(bibH,auteur_absent);
        temps_final = clock();
        temps_H = ((double)(temps_final - temps_initial))/ CLOCKS_PER_SEC;

        /*Ecriture dans le fichier approprié*/
		fprintf(f_auteur_a, "%i\t", i);
		fprintf(f_auteur_a, "%f\t", temps_LC);
		fprintf(f_auteur_a, "%f\n", temps_H);


        liberer_biblioH(bibH);
        liberer_biblio(bibLC);
    }
       /*Fermeture de tous les fichiers utilisés*/

    fclose(fichier_bib);
    fclose(f_auteur_a);
    fclose(f_auteur_p);
    fclose(f_num_a);
    fclose(f_num_p);
    fclose(f_titre_a);
    fclose(f_titre_p);
    
}