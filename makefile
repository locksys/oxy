main.exe:  fir.o fichiers.o iir.o affichage.o mesure.o integration.o main.o
	gcc fir.o fichiers.o iir.o mesure.o  affichage.o integration.o main.o -o main.exe

iir.o: iir.c iir.h
	gcc -c iir.c
	
fir.o: fir.c fir.h
	gcc -c fir.c
	
affichage.o: affichage.c affichage.h
	gcc -c affichage.c

mesure.o: mesure.c mesure.h
	gcc -c mesure.c

integration.o: integration.c integration.h
	gcc -c integration.c
	
main.o: main.c main.h
	gcc -c main.c
	
clean:
	rm -rf *.o *.out *.exe
