
exe: main.o plateau.o pion.o partie.o menu.o
	gcc -Wall -o exe pion.o main.o plateau.o partie.o menu.o

main.o: main.c partie.h 
	gcc -c main.c

pion.o: pion.c plateau.h pion.h
	gcc -c pion.c

plateau.o: plateau.c plateau.h
	gcc -c plateau.c

partie.o: partie.c partie.h plateau.h pion.h
	gcc -c partie.c

menu.o: menu.c plateau.h partie.h
	gcc -c menu.c

clean: 
	rm -f *.o exe