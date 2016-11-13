#ifndef PLATEAU_H
#define PLATEAU_H

#include "terminalCouleur.h"
typedef struct{
    
    int * tableau;
    int n;
    
}plateau;



void clear_terminal();
int color_printf(COULEUR_TERMINAL fg, COULEUR_TERMINAL bg, const char * format, ...);
plateau * creerPlateau( int n );
void detruirePlateau( plateau * p );
int getCase(plateau * p, int i , int j );
void setCase( plateau * p ,int i, int j, int val );
void affichage( plateau * p );


#endif