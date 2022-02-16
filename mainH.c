#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "biblioH.h"
#include "entreeSortieH.h"
#include "manipulation_livres_biblioH.h"

#define M 19

void menu(){
	printf("0 - Sortie du programme\n");
	printf("1 - Affichage de la bibliothèque\n");
	printf("2 - Insérer ouvrage\n");
	printf("3 - Recherche d'un livre selon son numéro\n");
	printf("4 - Recherche d'un livre selon son titre\n");
	printf("5 - Recherche de tous les livres d'un même auteur\n");
	printf("6 - Suppression d'un livre de la bibliothèque\n");
	printf("7 - Fusion de deux bibliothèques\n");
	printf("8 - Recherche des livres présents en plusieurs exemplaires dans la bibliothèque\n");
}

int main(int argc, char** argv){
	/*Récupération des données passées en ligne de commande*/
	if (argc != 3){
		printf("Erreur formatage ligne de commande.\nOn attend 2 arguments supplémentaires.");
		return 0;
	}
	char* nom_fichier = argv[1];
	if (atoi(argv[2]) == 0){
		printf("Erreur formatage ligne de commande.\nOn attend un nombre en second argument.");
	}
	int nb_lignes = atoi(argv[2]);

	/*Chargement selon ligne de commande*/
	BiblioH* biblio = charger_n_entreesH(nom_fichier,nb_lignes,M);
	
	/*Actions sur la bibliothèque selon le choix de l'utilisateur*/
	int rep;
	int num;
	char titre[256];
	char auteur[256];
	char entree[256];
	do{
		/*Affichage du menu et récupération de la réponse*/
		menu();
		fgets(entree, 10,stdin);
		rep = atoi(entree);
		/*Réalisation de l'action souhaitée*/
		switch(rep){
		case 1 :;
			printf("Affichage de la bibliothèque :\n");
			afficher_biblioH(biblio);
			break;
		case 2 :; 
			printf ("Saisissez le numéro, le titre et l'auteur de l'ouvrage :\n");
			if (fgets(entree,256,stdin)) {
				if (sscanf(entree, "%d %s %s\n",&num, titre, auteur) == 3){
					insererH(biblio, num, titre, auteur);
					printf ("Ajout fait\n");
				} else {
				printf ("Erreur formatage\n");
				}	
			}
			break;
		case 3 :;
			printf("Recherche d'un livre par numéro :\n");
			printf ("Saisissez le numéro recherché :\n");
			if (fgets(entree,10,stdin)) {
				if (sscanf(entree, "%d\n",&num) == 1){
					LivreH* l = recherche_numH(biblio,num);
					if (l){
						printf("Livre recherché :\n");
						afficher_livreH(l);
					}else{
						printf("Livre introuvable.\n");
					}
				}else{
					printf ("Erreur formatage\n");
				}
			}
			break ;
		case 4 :; 
			printf("Recherche d'un livre par titre :\n");
			printf ("Saisissez le titre recherché :\n");
			if (fgets(entree,256,stdin)) {
				if (sscanf(entree, "%s\n",titre) == 1){
					LivreH* l = recherche_titreH(biblio,titre);
					if (l){
						printf("Livre recherché :\n");
						afficher_livreH(l);
					}else{
						printf("Livre introuvable.\n");
					}
				}else{
					printf ("Erreur formatage\n");
				}
			}
			break ;
		case 5 :;
			printf("Recherche de tous les livres d'un auteur :\n");
			printf ("Saisissez l'auteur désiré :\n");;
			if (fgets(entree,256,stdin)) {
				if (sscanf(entree, "%s\n",auteur) == 1){
					BiblioH* b = recherche_auteurH(biblio,auteur);
					if (b){
						printf("Livres de l'auteur recherché :\n");
						afficher_biblioH(b);
						/*on peut la libérer directement*/
						liberer_biblioH(b);
					}else{
						printf("Auteur introuvable.\n");
					}
				}else{
					printf ("Erreur formatage\n");
				}
			}
			break ;
		case 6 :;
			printf("Suppression d'un livre de la bibliothèque :\n");
			printf ("Saisissez le numéro, le titre et l'auteur de l'ouvrage que vous voulez supprimer :\n");
			if (fgets(entree,256,stdin)) {
				if (sscanf(entree, "%d %s %s\n",&num, titre, auteur) == 3){
					supprimer_livreH(biblio, num, auteur, titre);
					printf ("Suppression faite\n");
				} else {
				printf ("Erreur formatage\n");
				}
			}
			break ;
		case 7 :; 
			printf("Fusionner des bibliothèques :\n");
			char nom_fichier_2[256];
			int nb_entrees;
			printf ("Saisissez nom du fichier où se trouve la bibliothèque à fusionner à la bibliothèque courante, et le nombre d'entrées à fusionner :\n");
			char entree[256];
			if (fgets(entree,256,stdin)) {
				if (sscanf(entree, "%s %d\n",nom_fichier_2, &nb_entrees) == 2){
					BiblioH* bib2 = charger_n_entreesH(nom_fichier_2,nb_entrees,M);
					fusion_bibH(biblio, bib2);
					printf ("Fusion faite\n");
				} else {
				printf ("Erreur formatage\n");
				}
			}
			break ;
		case 8 :; 
			printf("Recherche des livres présents en plusieurs exemplaires :\n");
			BiblioH* res = creer_biblioH(M);
			(res->T)[0] = recherche_pls_exemplairesH(biblio);
			if ((res->T)[0]){
				afficher_biblioH(res);
				liberer_biblioH(res);
			}else{
				printf("Aucun doublon présent.\n");
			}
			break;					
		}	
	}while (rep != 0);
	printf("Merci et au revoir!\n");

	/*Libération mémoire*/
	liberer_biblioH(biblio);

	return 0;
}