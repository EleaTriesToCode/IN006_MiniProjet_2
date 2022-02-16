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

#define TAILLE 400
#define M 19

int main()
{
	/*Créations des bibliothèques où chercher*/
	Biblio *bibLC = charger_n_entrees("GdeBiblio.txt", TAILLE);
	BiblioH *bibH = charger_n_entreesH("GdeBiblio.txt", TAILLE, M);

	/*Ouverture du fichier contenant les livres à chercher*/
	FILE *fichier_bib = fopen("GdeBiblio.txt", "r");

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

	/*Compteur du nombre de lectures souhaitées*/
	int cpt_lecture = 1;

	/*Buffers pour la lecture*/
	char ligne[256];
	int numero;
	char auteur[256];
	char titre[256];

	/*Variables pour le temps*/
	clock_t temps_initial;
	clock_t temps_final;
	double temps_LC;
	double temps_H;

	/*Lecture et recherche de chaque livre à rechercher selon son numéro, titre puis auteur*/
	while (fgets(ligne, 256, fichier_bib) && cpt_lecture <= TAILLE * 2)
	{ /*x2 car on voudra aussi lire des livres absents*/
		if (!(sscanf(ligne, "%d %s %s", &numero, titre, auteur) == 3))
		{
			printf("Erreur de lecture");
			break;
		}

		/*Recherche selon numéro*/

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
		if (cpt_lecture <= TAILLE)
		{
			fprintf(f_num_p, "%i\t", cpt_lecture);
			fprintf(f_num_p, "%f\t", temps_LC);
			fprintf(f_num_p, "%f\n", temps_H);
		}
		else
		{
			fprintf(f_num_a, "%i\t", cpt_lecture);
			fprintf(f_num_a, "%f\t", temps_LC);
			fprintf(f_num_a, "%f\n", temps_H);
		}

		/*Recherche selon titre*/
		/*Avec LC*/
		temps_initial = clock();
		recherche_titre(bibLC, titre);
		temps_final = clock();
		temps_LC = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
		/*Avec H*/
		temps_initial = clock();
		recherche_titreH(bibH, titre);
		temps_final = clock();
		temps_H = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
		/*Ecriture dans le fichier approprié*/
		if (cpt_lecture <= TAILLE)
		{
			fprintf(f_titre_p, "%i\t", cpt_lecture);
			fprintf(f_titre_p, "%f\t", temps_LC);
			fprintf(f_titre_p, "%f\n", temps_H);
		}
		else
		{
			fprintf(f_titre_a, "%i\t", cpt_lecture);
			fprintf(f_titre_a, "%f\t", temps_LC);
			fprintf(f_titre_a, "%f\n", temps_H);
		}

		/*ensuite pour le titre et l'auteur ça va être du copy paste en gros*/

		cpt_lecture++;
	}

	return 0;
}