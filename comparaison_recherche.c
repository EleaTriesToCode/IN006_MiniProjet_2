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


#define TAILLE 1500
#define M 19
#define OCCURENCE 100.0

void menu(){
    printf("On va comparer l'efficacité de nos deux structures de données sur différentes opérations :\n\n");
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

    /*Initialisation des bibliothèques où chercher*/
	Biblio* bibLC;
	BiblioH* bibH;

    /*Ouverture du fichier base de données*/
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

    char* titre_absent = "TractatusLogicoPhilosophicus";        //Pas besoin de changer le titre ou l'auteur du livre absent
    char* auteur_absent = "AndreComteSponville";

    /*Selon ce qui est choisi avec le menu, on va effectuer nos différents tests*/

    switch (rep)
    {
    case 0:
        printf("Aucun test réalisé.\n");
        return 0;
    
    case 1 :
        for(i = 1 ; i < TAILLE ; i++){
            bibLC = charger_n_entrees("GdeBiblio.txt",i);
            bibH = charger_n_entreesH("GdeBiblio.txt",i,M);

            srand(i);
            /*Avec LC*/
            temps_initial = clock();
            for(int j = 1 ; j < OCCURENCE; j++){
                recherche_num(bibLC,(rand()%i));
            }
            temps_final = clock();
            temps_LC = ((double)(temps_final - temps_initial)) / (CLOCKS_PER_SEC*OCCURENCE);

            /*Avec H*/
            temps_initial = clock();
            for(int j = 1 ; j < OCCURENCE ; j++){
                recherche_numH(bibH,(rand()%i));
            }
            temps_final = clock();
            temps_H = ((double)(temps_final - temps_initial)) / (CLOCKS_PER_SEC*OCCURENCE);

            /*Ecriture dans le fichier approprié*/
            fprintf(f_num_p, "%i\t", i);
            fprintf(f_num_p, "%.10f\t", temps_LC);
            fprintf(f_num_p, "%.10f\n", temps_H);

            /*Libération des bibliothèques (pour limiter la perte mémoire)*/
            liberer_biblio(bibLC);
            liberer_biblioH(bibH);

        }
    case 2 :
        for(i = 1 ; i < TAILLE ; i++){
            bibLC = charger_n_entrees("GdeBiblio.txt",i);
            bibH = charger_n_entreesH("GdeBiblio.txt",i,M);

            /*Avec LC*/
            temps_initial = clock();
            for(int j = 1 ; j < OCCURENCE; j++){
                recherche_num(bibLC,-1);
            }
            temps_final = clock();
            temps_LC = ((double)(temps_final - temps_initial)) / (CLOCKS_PER_SEC*OCCURENCE);

            /*Avec H*/
            temps_initial = clock();
            for(int j = 1 ; j < OCCURENCE ; j++){
                recherche_numH(bibH,-1);        //Aucun livre n'a le numéro -1, ça n'a conceptuellement pas de sens, on peut donc s'en servir ici
            }
            temps_final = clock();
            temps_H = ((double)(temps_final - temps_initial)) / (CLOCKS_PER_SEC*OCCURENCE);

            /*Ecriture dans le fichier approprié*/
            fprintf(f_num_a, "%i\t", i);
            fprintf(f_num_a, "%.10f\t", temps_LC);
            fprintf(f_num_a, "%.10f\n", temps_H);
            /*Libération des bibliothèques (pour limiter la perte mémoire)*/
            liberer_biblio(bibLC);
            liberer_biblioH(bibH);
        }
    case 3 :
        for(i = 1 ; i < TAILLE ; i++){
            bibLC = charger_n_entrees("GdeBiblio.txt",i);
            bibH = charger_n_entreesH("GdeBiblio.txt",i,M);

            srand(i);
            /*Avec LC*/
            temps_initial = clock();
            for(int j = 1 ; j < OCCURENCE; j++){
                recherche_titre(bibLC,titre_a_chercher[(rand()%i)]);
            }
            temps_final = clock();
            temps_LC = ((double)(temps_final - temps_initial)) / (CLOCKS_PER_SEC*OCCURENCE);

            /*Avec H*/
            temps_initial = clock();
            for(int j = 1 ; j < OCCURENCE ; j++){
                recherche_titreH(bibH,titre_a_chercher[(rand()%i)]);
            }
            temps_final = clock();
            temps_H = ((double)(temps_final - temps_initial)) / (CLOCKS_PER_SEC*OCCURENCE);

            /*Ecriture dans le fichier approprié*/
            fprintf(f_titre_p, "%i\t", i);
            fprintf(f_titre_p, "%.10f\t", temps_LC);
            fprintf(f_titre_p, "%.10f\n", temps_H);

            /*Libération des bibliothèques (pour limiter la perte mémoire)*/
            liberer_biblio(bibLC);
            liberer_biblioH(bibH);
        }
    case 4 :
        for(i = 1 ; i < TAILLE ; i++){
            bibLC = charger_n_entrees("GdeBiblio.txt",i);
            bibH = charger_n_entreesH("GdeBiblio.txt",i,M);

            /*Avec LC*/
            temps_initial = clock();
            for(int j = 1 ; j < OCCURENCE; j++){
                recherche_titre(bibLC,titre_absent);
            }
            temps_final = clock();
            temps_LC = ((double)(temps_final - temps_initial)) / (CLOCKS_PER_SEC*OCCURENCE);

            /*Avec H*/
            temps_initial = clock();
            for(int j = 1 ; j < OCCURENCE ; j++){
                recherche_titreH(bibH,titre_absent);
            }
            temps_final = clock();
            temps_H = ((double)(temps_final - temps_initial)) / (CLOCKS_PER_SEC*OCCURENCE);

            /*Ecriture dans le fichier approprié*/
            fprintf(f_titre_a, "%i\t", i);
            fprintf(f_titre_a, "%.10f\t", temps_LC);
            fprintf(f_titre_a, "%.10f\n", temps_H);

            /*Libération des bibliothèques (pour limiter la perte mémoire)*/
            liberer_biblio(bibLC);
            liberer_biblioH(bibH);
        }
    case 5 :
        for(i = 1 ; i < TAILLE ; i++){
            bibLC = charger_n_entrees("GdeBiblio.txt",i);
            bibH = charger_n_entreesH("GdeBiblio.txt",i,M);

            srand(i);
            /*Avec LC*/
            temps_initial = clock();
            for(int j = 1 ; j < OCCURENCE; j++){                    
                recherche_auteur(bibLC,auteur_a_chercher[(rand()%i)]);
            }
            temps_final = clock();
            temps_LC = ((double)(temps_final - temps_initial)) / (CLOCKS_PER_SEC*OCCURENCE);
            /*Avec H*/
            temps_initial = clock();
            for(int j = 1 ; j < OCCURENCE ; j++){
                recherche_auteurH(bibH,auteur_a_chercher[(rand()%i)]);
            }
            temps_final = clock();
            temps_H = ((double)(temps_final - temps_initial)) / (CLOCKS_PER_SEC*OCCURENCE);

            /*Ecriture dans le fichier approprié*/
            fprintf(f_auteur_p, "%i\t", i);
            fprintf(f_auteur_p, "%.10f\t", temps_LC);
            fprintf(f_auteur_p, "%.10f\n", temps_H);

            /*Libération des bibliothèques (pour limiter la perte mémoire)*/
            liberer_biblio(bibLC);
            liberer_biblioH(bibH);
        } 
    case 6 : 
        for(i = 1 ; i < TAILLE ; i++){
            bibLC = charger_n_entrees("GdeBiblio.txt",i);
            bibH = charger_n_entreesH("GdeBiblio.txt",i,M);

            srand(i);
            /*Avec LC*/
            temps_initial = clock();
            for(int j = 1 ; j < OCCURENCE; j++){
                recherche_auteur(bibLC,auteur_absent);
            }
            temps_final = clock();
            temps_LC = ((double)(temps_final - temps_initial)) / (CLOCKS_PER_SEC*OCCURENCE);

            /*Avec H*/
            temps_initial = clock();
            for(int j = 1 ; j < OCCURENCE ; j++){
                recherche_auteurH(bibH,auteur_absent);
            }
            temps_final = clock();
            temps_H = ((double)(temps_final - temps_initial)) / (CLOCKS_PER_SEC*OCCURENCE);

            /*Ecriture dans le fichier approprié*/
            fprintf(f_auteur_a, "%i\t", i);
            fprintf(f_auteur_a, "%.10f\t", temps_LC);
            fprintf(f_auteur_a, "%.10f\n", temps_H);

            /*Libération des bibliothèques (pour limiter la perte mémoire)*/
            liberer_biblio(bibLC);
            liberer_biblioH(bibH);
        }
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
