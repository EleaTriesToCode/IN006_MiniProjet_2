#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*Import des fonctions sur la table de hachage*/
#include "biblioH.h"
#include "entreeSortieH.h"
#include "manipulation_livres_biblioH.h"

/*Import des fonctions sur les listes chainées*/
#include "biblioLC.h"
#include "entreeSortieLC.h"
#include "manipulation_livres_biblio.h"


#define M 19


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

	/*Chargement selon ligne de commande les deux structures*/
	BiblioH* biblioh = charger_n_entrees(nom_fichier,nb_lignes,M);


}