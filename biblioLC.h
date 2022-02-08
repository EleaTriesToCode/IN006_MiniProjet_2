#ifndef BIBLIOLC_H
#define BIBLIOLC_H

typedef struct livre {
	int num ;
	char * titre ;
	char * auteur ;
	struct livre * suiv ;
} Livre ;

typedef struct { /* Tete fictive */
	Livre * L ; /* Premier element */
} Biblio ;

/*Fonction permettant de créer un livre à l'aide de son numéro, d'un titre, et d'un auteur et retourne un pointeur sur la structure*/
Livre* creer_livre(int num, char* titre, char* auteur);

/*Fonction permettant de libérer la place allouée en mémoire au Livre l*/
void liberer_livre(Livre* l);


/*Créé une bibliothèque en initialisant son champ livre à null*/
Biblio* creer_biblio();

/*Libère la Biblio b allouée*/
void liberer_biblio(Biblio* b);

/*Fonction permettant d'insérer un livre caractérisé par son numéro, son titre et son auteur en tête d'une Biblio b*/
void inserer_en_tete(Biblio* b, int num, char* titre, char* auteur);


#endif
