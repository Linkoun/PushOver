#include <stdio.h>
#include "partie.h"
#include "pion.h"
#include "plateau.h"

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