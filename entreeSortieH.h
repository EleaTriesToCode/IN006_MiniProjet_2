#ifndef ENTREESORTIEH_H
#define ENTREESORTIEH_H

/*Fonction permettant de charger n entrées à partir d'un fichier nommé nomfic*/
BiblioH* charger_n_entrees(char* nomfic, int n, int m);

/*Fonction permettant de passer d'une bibliothèque à un fichier nummé nomfic (enregistrer la bibliothèque)*/
void enregistrer_biblio(BiblioH *bH, char* nomfic);

#endif
