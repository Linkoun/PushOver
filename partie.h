#ifndef PARTIE_H
#define PARTIE_H

#include <assert.h>
#include "plateau.h"


typedef struct{
    char nomJoueur1[128];
    char nomJoueur2[128];
    int PionJoueurCourant;
    plateau * p;
}partie;

partie * creerPartie();
void detruirePartie( partie * pa );
void changePionJoueurCourant(partie * pa);
int saisieJoueur(partie * pa, int * ligne, int * col , int * di, int * dj);
int tourJoueurCourant(partie * pa);
int jouer(partie * pa);


#endif