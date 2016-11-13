#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "plateau.h"



void clear_terminal()
{
    printf("\033[2J");
    printf("\033[0;0H");
}

int color_printf(COULEUR_TERMINAL fg, COULEUR_TERMINAL bg, const char * format, ...)
{
    int res;
    va_list args;
    printf("\x1B[1;%02d;%02dm", fg + 30, bg + 40);
    va_start(args, format);
    res = vprintf(format, args);
    va_end(args);
    printf("\x1B[00m");
    return res;
}

// Fonction permet d'allouer dynamiquement un plateau dont l'adresse est retournÈe.
// n est la taille d'un cÙtÈ.

plateau * creerPlateau( int n )
{
    
    assert( n>=2 && n<=8 );
    plateau * p=malloc(sizeof(plateau));
    // alloue la memoire pour un plateau.
    if ( p == NULL)
    {
        printf("Erreur.La memoire n'a pas pu etre alloue.\n");
        exit(1);
    }
    p->n = n;
    p->tableau = malloc(n*n*sizeof(int)); // alloue la memoire pour chaque case du tableau.
    if ( p->tableau == NULL)
    {
        printf("Erreur.La memoire n'a pas pu etre alloue.\n");
        exit(1);
    }
    
    return p;
}

// Fonction desallouant dynamiquement le plateau passe en paramËtre.
// p est le plateau a dÈsallouer

void detruirePlateau( plateau * p )
{
    assert ( p != NULL );
    free(p->tableau);
    free(p);
    
}

// Fonction retournant la valeur de la case (i,j) du plateau p.
// p est le plateau.
// i est un entier correspondant au numero de la ligne.
// j est un entier correspondant au numero de la colonne.
int getCase(plateau * p, int i , int j )
{
    assert( i>=0 && i<=((p->n)-1));
    assert( j>=0 && j<=((p->n)-1));
    int res;
    res = *((p-> tableau) + j+i*(p->n));
    return res;
}



// Fonction modifiant la valeur(-1 ou 1) de la case(i,j) du plateau p.
// p est le plateau.
// i est un entier correspondant au numero de la ligne.
// j est un entier correspondant au numero de la colonne.

void setCase( plateau * p ,int i, int j, int val )
{
    assert( val== 1 || val ==-1 || val == 0);
    assert( i>=0 && i<=((p->n)-1));
    assert( j>=0 && j<=((p->n)-1));
    
    *((p-> tableau)+ j+i*(p->n)) = val;
    
}

// Fonction affichant le plateau sur le terminal.

void affichage( plateau * p )
{
    int i,m;
    i=0;
    int ord;
    char e[]="       ";
    char r[]="###";
    char s[]=" ";
    printf("%s",s);
    for(m=0;m<(p->n);m++)
    {
        printf("%4d   ", m);
    }
    printf("\n");
    while(i<(p->n))
    {
        if (i%2==0)
        {
            ord=1;
        }
        else ord =0;
        printf("%s",s);
        for(m=0;m<(p->n);m++)
        {
            if(m%2==ord)	color_printf(BLACK,MAGENTA, "%s" , e);
            else color_printf(BLACK,YELLOW, "%s" , e);
            
        }
        printf("\n");
        printf("%d",i);
        for(m=0;m<(p->n);m++)
        {
            if(getCase(p,i,m)== -1)
            {
                if(m%2==ord)	color_printf(WHITE,MAGENTA, "%5s  " , r);
                else color_printf(WHITE,YELLOW, "%5s  " ,r);
            }
            
            else if(getCase(p,i,m)== 1)
            {
                if(m%2==ord)	color_printf(BLACK,MAGENTA, "%5s  " , r);
                else color_printf(BLACK,YELLOW, "%5s  " ,r);
            }
            
            else
            {
                if(m%2==ord)	color_printf(BLACK,MAGENTA, "%4s   " , s);
                else color_printf(BLACK,YELLOW, "%4s   " ,s);
            }
            
            
            
        }
        
        printf("\n");
        
        printf("%s",s);
        for(m=0;m<(p->n);m++)
        {
            
            if(m%2==ord)	color_printf(BLACK,MAGENTA, "%s" , e);
            else color_printf(BLACK,YELLOW, "%s" , e);
            
        }
        
        printf("\n");
        
        i++;
    }
}
//------------------------------------------------------------------------------