#include <stdio.h>
#include "plateau.h"


/*
 * Fonction retournant 1 si l'indice est valide par rapport au plateau
 *
 * param p: plateau
 * param indice : entier compris entre [0,n-1];
 */


int indiceValide( plateau * p , int indice)
{
    if(indice <= (p->n)-1 && indice >=0)
    {
        return 1;
    }
    else return 0;
}


/*!
 * Fonction retournant 1 si la case (indiceLigne,indiceColonne) existe sur le plateau
 *
 *  \param p : plateau
 *  \param indiceLigne : entier correspondant a un indice de ligne
 *  \param indiceColonne : entier correspondant a un indice de colonne
 */


int caseValide( plateau * p,int indiceLigne , int indiceColonne)
{
    if(indiceValide(p,indiceLigne))
    {
        if (indiceValide(p,indiceColonne))
            return 1;
        else return 0;
    }
    else return 0;
}

/*!
 * Fonction retournant 1 si la case (i,j) du plateau p est vide
 *  \param p : plateau
 *  \param i : entier correspondant a un indice de ligne
 *  \param j : entier correspondant a un indice de colonne
 */



int caseVide(plateau * p , int i , int j)
{
    if( getCase(p,i,j) == 0)
        return 1;
    else return 0;
}



int colRempli(plateau * p, int col)
{
    int nb=0;
    int i;
    for(i = 0 ; i < (p->n) ; i++ )
    {
        if(!(caseVide(p,i,col)))
            nb++;
    }
    return nb;
}

int ligneRempli(plateau * p, int ligne)
{
    int nb=0;
    int i;
    for(i = 0 ; i < (p->n) ; i++ )
    {
        if(!(caseVide(p,ligne,i)))
            nb++;
    }
    return nb;
}


/*!
 * Fonction retournant 1 si le pion peut etre ajoute a partir de la case (ligne,col)
 * dans la direction donnee par di,dj
 *
 *  \param p : plateau
 *  \param ligne : ligne de la case ou l'on insere le pion
 *  \param col : colonne de la case ou l'on insere le pion
 *  \param di : direction sur les lignes
 *              // -1 si l’on insere vers le haut,
 *              //  0 si l’on reste sur la meme ligne,
 *              //  1 si l’on insere vers le bas
 *  \param dj : direction sur les colonnes
 *              // -1 si l’on insere vers la gauche,
 *              //  0 si l’on reste sur la meme colonne,
 *              //  1 si l’on insere vers la droite
 *  \param pion : 1 ou -1 suivant le joueur
 */

int insertionPionPossible (plateau * p, int ligne, int col, int di, int dj, int pion)
{
    
    if( ligne == 0 && di == 1 && dj == 0)
    {
        
        if( (colRempli(p,col) == (p->n) && pion == getCase(p,((p->n)-1),col)) ||  colRempli(p,col) != (p->n))
            return 1;
    }
    
    
    else if( ligne == (p->n)-1 && di == -1 && dj == 0)
    {
        
        if( (colRempli(p,col)== (p->n) && pion == getCase(p,0,col))|| colRempli(p,col) != (p->n))
            return 1;
        
    }
    
    else if(col == 0 && di == 0 && dj == 1)
    {
        
        if((ligneRempli(p,ligne) == (p->n) && pion == getCase(p,ligne,((p->n)-1))) || ligneRempli(p,ligne) !=(p->n))
            return 1;
    }
    
   	else if(col == (p->n)-1 && di == 0 && dj == -1)
    {
        
        if((ligneRempli(p,ligne) == (p->n) && pion == getCase(p,ligne,0)) || ligneRempli(p,ligne) !=(p->n))
            return 1;
    }
    return 0;
}

/*!
 * Fonction inserant le pion a partir de la case (ligne,col)
 * dans la direction donnee par di,dj
 *
 *  \param p : plateau
 *  \param ligne : ligne de la case ou l'on insere le pion
 *  \param col : colonne de la case ou l'on insere le pion
 *  \param di : direction sur les lignes
 *              // -1 si l’on insere vers le haut,
 *              //  0 si l’on reste sur la meme ligne,
 *              //  1 si l’on insere vers le haut
 *  \param dj : direction sur les colonnes
 *              // -1 si l’on insere vers la gauche,
 *              //  0 si l’on reste sur la meme colonne,
 *              //  1 si l’on insere vers la droite
 *  \param pion : 1 ou -1 suivant le joueur
 */
void insertionPion(plateau * p, int ligne, int col, int di, int dj, int pion)
{
    int vide=0;
    int i;
    int nbvide=0;
    // INSERTION PAR LE HAUT
    if(ligne == 0 && di == 1 && dj == 0)
    {
        nbvide=(p->n)-colRempli(p,col);
        for(i=1; i<(p->n) ; i++)
        {
            if(caseVide(p,(p->n)-i,col))
                vide++;
            if(vide==nbvide)
                setCase(p,((p->n)-i),col,getCase(p,((p->n)-i-1),col));
        }
        setCase(p,ligne,col,pion);
    }
    
    
    // INSERTION PAR LE BAS
    else if( ligne == (p->n)-1 && di == -1 && dj == 0)
    {
        nbvide=(p->n)-colRempli(p,col);
        for(i=0; i<(p->n)-1 ; i++)
        {
            if(caseVide(p,i,col))
                vide++;
            if(vide==nbvide)
                setCase(p,i,col,getCase(p,(i+1),col));
        }
        setCase(p,ligne,col,pion);
    }
    
    
    
    // INSERTION PAR LA DROITE
    
    else if( col == (p->n)-1 && di == 0 && dj == -1)
    {
        nbvide=(p->n)-ligneRempli(p,ligne);
        for(i=0; i<(p->n)-1 ; i++)
        {
            if(caseVide(p,ligne,i))
                vide++;
            if(vide==nbvide)
                setCase(p,ligne,i,getCase(p,ligne,(i+1)));
       	}
        setCase(p,ligne,col,pion);
    }
    
    // INSERTION PAR LA GAUCHE
    else if(col == 0 && di == 0 && dj == 1)
    {
        nbvide=(p->n)-ligneRempli(p,ligne);
        for(i=1; i<(p->n) ; i++)
        {
            if(caseVide(p,ligne,(p->n)-i))
                vide++;
            if(vide==nbvide)
                setCase(p,ligne,((p->n)-i),getCase(p,ligne,((p->n)-i-1)));
        }
        setCase(p,ligne,col,pion);
    }
}


/*!
 * Fonction retournant 1 ou -1 si l’un des joueurs a gagne, 2 si match nul et 0 si la partie
 * n’est pas finie.
 *
 *  \param p : plateau
 */
int gagne(plateau * p)
{
    
    int n,i;
    int j1=0;
    int j2=0;
    for( i=0 ; i < (p->n) ; i++ )
    {
        int noir=0;
        int blanc=0;
        for(n=0 ; n<(p->n); n++)
        {
            if(*((p->tableau)+n+i*(p->n)) == 1)
                noir++;
            if(*((p->tableau)+n+i*(p->n)) == -1 )
                blanc++;
            if(noir==(p->n))
                j1++;
            if(blanc==(p->n))
                j2++;
            
        }
    }
    for( n=0 ; n< (p->n) ; n++ )
    {
        int noir=0;
        int blanc=0;
        for(i=0 ; i<(p->n); i++)
        {
            if(*((p->tableau)+n+i*(p->n)) == 1)
                noir++;
            if(*((p->tableau)+n+i*(p->n)) == -1 )
                blanc++;
            if(noir==(p->n))
                j1++;
            if(blanc==(p->n))
                j2++;
            
        }
    }
    if(!(j1 || j2))
        return 0;
    
    else if(j1>j2)
        return 1;
    
    else if(j2>j1)
        return -1;
    
    else if(j2==j1)
        return 2;
    
    return 0;
}