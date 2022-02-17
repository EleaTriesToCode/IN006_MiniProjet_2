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


#define TAILLE 100
#define OCCURENCE 100.0
#define M_MAX 1000

void menu(){
    printf("\nOn va étudier l'évolution de la complexité de différentes opérations selon la taille de la table de hachage :\n");
	printf("0 - Sortie du programme\n");
	printf("1 - Recherche par numéro (élément présent)\n");
	printf("2 - Recherche par numéro (élément absent)\n");
	printf("3 - Recherche par titre (élément présent\n");
	printf("4 - Recherche par titre (élément absent)\n");
	printf("5 - Recherche par auteur (auteur présent)\n");
	printf("6 - Recherche par auteur (auteur absent)\n");
}

int main(){
    /*Choix du test à réaliser*/
    char entree[256];
    menu();
	fgets(entree, 10,stdin);
	int rep = atoi(entree);

	/*Initialisation de la bibliothèque où chercher*/
	BiblioH* bibH;

    FILE* fichier_bib = fopen("GdeBiblio.txt","r");

    /*Variables pour le temps*/
	clock_t temps_initial;
	clock_t temps_final;
	double temps_H;

    /*Ouverture des fichiers où stocker les temps de calcul pour le gnuplot*/

	/*Avec numéro, livres présents*/
	FILE *f_num_p = fopen("Comparaison_Table_Numero_Present.txt", "w");

	/*Avec titre, livres présents*/
	FILE *f_titre_p = fopen("Comparaison_Table_Titre_Present.txt", "w");

	/*Avec auteur, livres présents*/
	FILE *f_auteur_p = fopen("Comparaison_Table_Auteur_Present.txt", "w");

	/*Avec numéro, livres absents*/
	FILE *f_num_a = fopen("Comparaison_Table_Numero_Absent.txt", "w");

	/*Avec titre, livres absents*/
	FILE *f_titre_a = fopen("Comparaison_Table_Titre_Absent.txt", "w");

	/*Avec auteur, livres absents*/
	FILE *f_auteur_a = fopen("Comparaison_Table_Auteur_Absent.txt", "w");


    /*On va prendre une centaine de livres, présents dans la bibliothèque, dans laquelle on va piocher à chaque
    tour de boucle un livre aléatoire à rechercher*/
    char titre_a_chercher[TAILLE][256];
    char auteur_a_chercher[TAILLE][256];
    int numero;
    char ligne[256];

    int m;
    int i = 0;

    while(fgets(ligne,256,fichier_bib)&& (i < TAILLE)){
        if(!(sscanf(ligne,"%d %s %s",&numero,titre_a_chercher[i],auteur_a_chercher[i])==3)){
            printf("Erreur dans le fichier !\n");
            return 0;
        }
        i++;
    }

    char* titre_absent = "TractatusLogicoPhilosophicus";        //Pas besoin de changer le titre ou l'auteur du livre absent
    char* auteur_absent = "AndreComteSponville";

    /*Selon ce qui est choisi avec le menu, on va effectuer nos différents tests*/

    switch (rep)
    {
    case 0:
        printf("Aucun test réalisé.\n");
        return 0;
    
    case 1 :
        for(m = 1 ; m < M_MAX ; m++){
            bibH = charger_n_entreesH("GdeBiblio.txt",TAILLE,m);

            srand(m);
            temps_initial = clock();
            for(int j = 1 ; j < OCCURENCE ; j++){
                recherche_numH(bibH,(rand()%TAILLE));
            }
            temps_final = clock();
            temps_H = ((double)(temps_final - temps_initial)) / (CLOCKS_PER_SEC*OCCURENCE);

            /*Ecriture dans le fichier approprié*/
            fprintf(f_num_p, "%i\t", m);
            fprintf(f_num_p, "%.10f\n", temps_H);

        }
        break;
    case 2 :
        for(m = 1 ; m < M_MAX ; m++){
            bibH = charger_n_entreesH("GdeBiblio.txt",TAILLE,m);

            srand(m);
            /*Avec H*/
            temps_initial = clock();
            for(int j = 1 ; j < OCCURENCE ; j++){
                recherche_numH(bibH,-1);        //Aucun livre n'a le numéro -1, ça n'a conceptuellement pas de sens, on peut donc s'en servir ici
            }
            temps_final = clock();
            temps_H = ((double)(temps_final - temps_initial)) / (CLOCKS_PER_SEC*OCCURENCE);

            /*Ecriture dans le fichier approprié*/
            fprintf(f_num_a, "%i\t", m);
            fprintf(f_num_a, "%.10f\n", temps_H);

        }
        break;
    case 3 :
        for(m = 1 ; m < M_MAX ; m++){
            bibH = charger_n_entreesH("GdeBiblio.txt",TAILLE,m);

            srand(m);
            /*Avec H*/
            temps_initial = clock();
            for(int j = 1 ; j < OCCURENCE ; j++){
                recherche_titreH(bibH,titre_a_chercher[(rand()%TAILLE)]);
            }
            temps_final = clock();
            temps_H = ((double)(temps_final - temps_initial)) / (CLOCKS_PER_SEC*OCCURENCE);

            /*Ecriture dans le fichier approprié*/
            fprintf(f_titre_p, "%i\t", m);
            fprintf(f_titre_p, "%.10f\n", temps_H);

        }
        break;
    case 4 :
        for(m = 1 ; m < M_MAX ; m++){
            bibH = charger_n_entreesH("GdeBiblio.txt",TAILLE,m);

            srand(m);
            /*Avec H*/
            temps_initial = clock();
            for(int j = 1 ; j < OCCURENCE ; j++){
                recherche_titreH(bibH,titre_absent);
            }
            temps_final = clock();
            temps_H = ((double)(temps_final - temps_initial)) / (CLOCKS_PER_SEC*OCCURENCE);

            /*Ecriture dans le fichier approprié*/
            fprintf(f_titre_a, "%i\t", m);
            fprintf(f_titre_a, "%.10f\n", temps_H);

        }
        break;
    case 5 :
        for(m = 1 ; m < M_MAX ; m++){
            bibH = charger_n_entreesH("GdeBiblio.txt",TAILLE,m);

            srand(m);
            /*Avec H*/
            temps_initial = clock();
            for(int j = 1 ; j < OCCURENCE ; j++){
                recherche_auteurH(bibH,auteur_a_chercher[(rand()%TAILLE)]);
            }
            temps_final = clock();
            temps_H = ((double)(temps_final - temps_initial)) / (CLOCKS_PER_SEC*OCCURENCE);

            /*Ecriture dans le fichier approprié*/
            fprintf(f_auteur_p, "%i\t", m);
            fprintf(f_auteur_p, "%.10f\n", temps_H);
        } 
        break;
    case 6 : 
        for(m = 1 ; m < M_MAX ; m++){
            bibH = charger_n_entreesH("GdeBiblio.txt",TAILLE,m);

            srand(m);
            /*Avec H*/
            temps_initial = clock();
            for(int j = 1 ; j < OCCURENCE ; j++){
                recherche_auteurH(bibH,auteur_absent);
            }
            temps_final = clock();
            temps_H = ((double)(temps_final - temps_initial)) / (CLOCKS_PER_SEC*OCCURENCE);

            /*Ecriture dans le fichier approprié*/
            fprintf(f_auteur_a, "%i\t", m);
            fprintf(f_auteur_a, "%.10f\n", temps_H);

        }
        break;
    default:
        break;
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