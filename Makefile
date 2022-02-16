all : main mainH comparaison_recherche


#~~~~~~~~~~~~~~~~~
#3.1
comparaison_recherche :comparaison_recherche.o biblioLC.o entreeSortieLC.o manipulation_livres_biblio.o biblioH.o entreeSortieH.o manipulation_livres_biblioH.o
	gcc -o comparaison_recherche comparaison_recherche.o biblioLC.o entreeSortieLC.o manipulation_livres_biblio.o biblioH.o entreeSortieH.o manipulation_livres_biblioH.o -lm

comparaison_recherche.o : comparaison_recherche.c biblioLC.h entreeSortieLC.h manipulation_livres_biblio.h biblioH.h entreeSortieH.h manipulation_livres_biblioH.h
	gcc -c comparaison_recherche.

#~~~~~~~~~~~~~~~~~~
#Main avec les listes chainées
main : main.o biblioLC.o entreeSortieLC.o manipulation_livres_biblio.o
	gcc -o main main.o biblioLC.o entreeSortieLC.o manipulation_livres_biblio.o

main.o : main.c biblioLC.h entreeSortieLC.h manipulation_livres_biblio.h
	gcc -c main.c

biblioLC.o : biblioLC.c biblioLC.h 
	gcc -c biblioLC.c

entreeSortieLC.o : entreeSortieLC.c entreeSortieLC.h biblioLC.h
	gcc -c entreeSortieLC.c

manipulation_livres_biblio.o : biblioLC.c biblioLC.h manipulation_livres_biblio.h
	gcc -c manipulation_livres_biblio.c


#~~~~~~~~~~~~~~~~~~~
#Main avec les tables de hachage
mainH : mainH.o biblioH.o entreeSortieH.o manipulation_livres_biblioH.o
	gcc -o mainH mainH.o biblioH.o entreeSortieH.o manipulation_livres_biblioH.o -lm

mainH.o : mainH.c biblioH.h entreeSortieH.h manipulation_livres_biblioH.h
	gcc -c mainH.c

biblioH.o : biblioH.c biblioH.h
	gcc -c biblioH.c

entreeSortieH.o : entreeSortieH.c entreeSortieH.h biblioH.h
	gcc -c entreeSortieH.c

manipulation_livres_biblioH.o : biblioH.c biblioH.h manipulation_livres_biblioH.h
	gcc -c manipulation_livres_biblioH.c


clean :
	rm -f *.o main
