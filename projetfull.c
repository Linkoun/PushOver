            #include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "terminalCouleur.h"

/*Structure permettant de reprÈsenter le plateau du PushOver
		pointeur "tableau" : tableau reprÈsentant le plateau de jeu
		int n : nombre de cases par ligne et colonnes*/

typedef struct{

	int * tableau;
	int n;

}plateau;

typedef struct{
    char nomJoueur1[128];
    char nomJoueur2[128];
    int PionJoueurCourant;
    plateau * p;
}partie;


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
//------------------------------------------------------------------------------partie2------------------------------------------------------------------------------

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


//--------------------------- Partie 3 ---------------------------------
/*!
 * Fonction allouant dynamiquement une partie et renvoyant l’adresse de celle-ci.
 * La taille du plateau et les noms des joueurs sont saisis par l’utilisateur.
 */
partie * creerPartie()
{
    partie * partie=NULL;
	int n;
	printf("Choisir la taille du plateau :");
	scanf("%d",&n);
    partie=malloc(256*sizeof(char) +sizeof(int)+sizeof(plateau));
    printf("Entrer le nom du premier joueur.\n");
    scanf("%127s",partie->nomJoueur1);
    printf("Entrer le nom du deuxieme joueur.\n");
    scanf("%127s",partie->nomJoueur2);
    partie->PionJoueurCourant=1;
    partie->p= creerPlateau(n);
    
    return partie;
    
}



/*!
 * Fonction désallouant dynamiquement la partie passée en paramètre
 *
 * \param pa : partie à désallouer
 */

void detruirePartie( partie * pa )
{
	assert ( pa != NULL );
	detruirePlateau(pa->p);
	free(pa);

}



/*!
 * Fonction changeant le pion du joueur courant (1 ou -1)
 *
 * \param pa : partie en cours
 */

void changePionJoueurCourant(partie * pa)
{
    (pa->PionJoueurCourant)=((pa->PionJoueurCourant)*(-1));
}



/*!
 * Fonction modifiant les variables ligne, col, di et dj passées en paramètre avec
 * les valeurs saisies par l’utilisateur. Elle retourne 0 si le joueur a appuyé
 * sur la lettre M et 1 sinon.
 *
 *  \param p : partie
 *  \param ligne : ligne du plateau où l’on souhaite insérer le pion du joueur courant de la partie
 *  \param col : colonne du plateau où l’on souhaite insérer le pion du joueur courant de la partie
 *  \param di : direction d’insertion (ligne)
 *  \param dj : direction d’insertion (colonne)
 */
int saisieJoueur(partie * pa, int * ligne, int * col , int * di, int * dj)
{
    char rep[3];
    do{
        printf("Retourner au menu principal (M) ou saisir un mouvement (ex : G2 ).\n");
        scanf("%2s",rep);
        if(rep[0]=='M')
            return 0;
        else if(rep[0]=='G')
        {
            *(ligne)= rep[1]-'0'; *(col)=0 ; *(di) =0 ; *(dj)= 1;
        }
        
        else if( rep[0] =='D')
        {
            *(ligne)= rep[1]-'0'; *(col)=((pa->p->n)-1) ; *(di) =0 ; *(dj) =-1;
        }
        
        else if( rep[0] =='B')
        {
           *(ligne)= ((pa->p->n)-1); *(col)=rep[1]-'0' ; *(di)=-1 ; *(dj) =0;
        }
        
        else if( rep[0] =='H')
        {
            *(ligne)= 0; *(col)=rep[1]-'0' ; *(di) =1 ; *(dj) = 0;
        }
        
    }while((rep[0]!='G' && rep[0]!='D' && rep[0]!= 'H' && rep[0]!='B') || (rep[1]<'0' || rep[1]>'0'+((pa->p->n)-1)) || !(insertionPionPossible((pa->p),*(ligne),*(col),*(di),*(dj),(pa->PionJoueurCourant)))) ;
    
    return 1;
}


/*!
 * Fonction permettant au joueur courant de jouer.
 * La fonction retourne 1 si le joueur joue, et 0 sinon (s’il appuie sur la touche M).
 *
 * \param pa : partie en cours
 */

int tourJoueurCourant(partie * pa)
{
    int ligne,col,di,dj;
    affichage(pa->p);
    if((pa->PionJoueurCourant) == 1)
        printf("%s\n",pa->nomJoueur1);
    else if((pa->PionJoueurCourant)== -1)
        printf("%s\n",pa->nomJoueur2);
    if(saisieJoueur(pa,&ligne,&col,&di,&dj))
    {
        insertionPion((pa->p),ligne,col,di,dj,(pa->PionJoueurCourant));
        return 1;
    }
    
    return 0;

}

/*!
 * Fonction permettant de jouer à Push over.
 *
 * \param pa : pointeur sur une partie en cours (elle doit être allouée). La partie peut ne pas être
 * un début de partie.
 *
 * Retourne 0 si un joueur veut accéder au menu principal, 1 si la partie s’est terminée normalement
 * (Partie gagnée ou nulle)
 */
int jouer(partie * pa)
{
    while(!(gagne(pa->p)))
    {
        if(tourJoueurCourant(pa))
            changePionJoueurCourant(pa);
        else
            return 0;
        
    }
    affichage(pa->p);
    if(gagne(pa->p)==1)
        printf("Le gagnant est %s (noir)\n", pa->nomJoueur1);
    if(gagne(pa->p)==-1)
        printf("Le gagnant est %s (blanc)\n", pa->nomJoueur2);
    return 1;
        
}

//------------------------- Partie 4 --------------------------


int sauvegarde(partie * pa )
{
    int i,j,rep;
    FILE * f;
    printf("Sauvegarder Slot 1,2,3,4,5 ?\n");
    scanf("%d",&rep);
    if(rep==1)
        f = fopen("sauvegarde.txt","wt");
    if(rep==2)
        f = fopen("sauvegarde.txt2","wt");
    if(rep==3)
        f = fopen("sauvegarde.txt3","wt");
    if(rep==4)
        f = fopen("sauvegarde.txt4","wt");
    if(rep==5)
        f = fopen("sauvegarde.txt5","wt");
    if(f==NULL)
    {
        return 0;
    }
    fprintf(f,"%d ",pa->p->n);
    fprintf(f,"%s ",pa->nomJoueur1);
    fprintf(f,"%s ", pa->nomJoueur2);
    fprintf(f,"%d ",pa->PionJoueurCourant);
    for(i=0 ; i < pa->p->n; i++)
    {
        for(j=0 ; j<pa->p->n ; j++ )
        {
            fprintf(f,"%d",getCase(pa->p,i,j));
            fprintf(f," ");
        }

    }
    fprintf(f,"\n");
    fclose(f);
    return 1;
    
}

partie * chargementPartie()
{
    int i , j ,n,save,rep;
    partie * pa=NULL;
    FILE * f;
    printf("Charger Slot 1,2,3,4,5 ?\n");
    scanf("%d",&rep);
    if(rep==1)
        f = fopen("sauvegarde.txt","rt");
    if(rep==2)
        f = fopen("sauvegarde.txt2","rt");
    if(rep==3)
        f = fopen("sauvegarde.txt3","rt");
    if(rep==4)
        f = fopen("sauvegarde.txt4","rt");
    if(rep==5)
        f = fopen("sauvegarde.txt5","rt");
    if(f==NULL)
    {
        return 0;
    }
    fscanf(f,"%d",&n);
    pa=malloc(256*sizeof(char) +sizeof(int)+sizeof(plateau));
    pa->p= creerPlateau(n);
    pa->p->n=n;
    fscanf(f,"%s", pa->nomJoueur1);
    fscanf(f,"%s",pa->nomJoueur2);
    fscanf(f,"%d",&(pa->PionJoueurCourant));
    for(i=0;i<(pa->p->n) ; i++)
    {
        for(j=0;j<(pa->p->n) ; j++)
        {
            fscanf(f,"%d",&save);
            setCase(pa->p,i,j,save);
        }
    }
    fclose(f);
    return pa;
}

int menu(partie *pa)
{
    int rep;
    if(pa!=NULL)
    {
        do{
            printf("0:Quitter le jeu.\n1:Nouvelle Partie.\n2:Charge une partie.\n3:Sauvegarder la partie\n4:Reprendre la partie\n");
            scanf("%d",&rep);
            

        }while(rep!=0 && rep!=1 && rep!=2 && rep!=3 && rep!=4);
        return rep;
    }
    else
    {
        do{
            
            printf("0:Quitter le jeu.\n1:Nouvelle Partie.\n2:Charge une partie.\n");
            scanf("%d",&rep);
            
        }while(rep!=0 && rep!=1 && rep!=2);
        return rep;
    }
    
    
}


int main()
{
    partie *pa=NULL;
    int rep;
    do{
        rep=menu(pa);
        if(rep==1)
        {
            pa=creerPartie();
            jouer(pa);
        }
        
        if(rep==2)
        {
            pa=chargementPartie();
            jouer(pa);
        }
        if(rep==3)
            sauvegarde(pa);
        if(rep==4)
            jouer(pa);
    }while(rep!=0);
    if(pa!=NULL)
        detruirePartie(pa);
	return 0;
}
