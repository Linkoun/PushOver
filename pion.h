#ifndef PION_H
#define PION_H


int indiceValide( plateau * p , int indice);
int caseValide( plateau * p,int indiceLigne , int indiceColonne);
int caseVide(plateau * p , int i , int j);
int colRempli(plateau * p, int col);
int ligneRempli(plateau * p, int ligne);
int insertionPionPossible (plateau * p, int ligne, int col, int di, int dj, int pion);
void insertionPion(plateau * p, int ligne, int col, int di, int dj, int pion);
int gagne(plateau * p);






#endif