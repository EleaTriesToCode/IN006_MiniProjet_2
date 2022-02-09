all : main

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

clean :
	rm -f *.o main
