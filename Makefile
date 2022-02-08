all : main

main : main.o biblioLC.o entreeSortieLC.o
	gcc -o main main.o biblioLC.o entreeSortieLC.o

main.o : main.c biblioLC.h entreeSortieLC.h
	gcc -c main.c

biblioLC.o : biblioLC.c biblioLC.h 
	gcc -c biblioLC.c

entreeSortieLC.o : entreeSortieLC.c entreeSortieLC.h biblioLC.h
	gcc -c entreeSortieLC.c


clean :
	rm -f *.o main
