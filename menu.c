#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include "partie.h"


//------------------------- Partie 4 --------------------------


int sauvegarde(partie * pa )
{
    int i,j,rep;
    FILE * f=NULL;
    printf("Sauvegarder Slot 1,2,3,4,5 ?\n");
    scanf("%d",&rep);
    if(rep==1)
        f = fopen("sauvegarde.txt","wt");
    else if(rep==2)
        f = fopen("sauvegarde.txt2","wt");
    else if(rep==3)
        f = fopen("sauvegarde.txt3","wt");
    else if(rep==4)
        f = fopen("sauvegarde.txt4","wt");
    else if(rep==5)
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
    FILE * f=NULL;
    partie * pa=NULL;
    printf("Charger Slot 1,2,3,4,5 ?\n");
    scanf("%d",&rep);
    if(rep==1)
        f = fopen("sauvegarde.txt","rt");
    else if(rep==2)
        f = fopen("sauvegarde.txt2","rt");
    else if(rep==3)
        f = fopen("sauvegarde.txt3","rt");
    else if(rep==4)
        f = fopen("sauvegarde.txt4","rt");
    else if(rep==5)
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
            return rep;
            
        }while(rep!=0 && rep!=1 && rep!=2 && rep!=3 && rep!=4);
    }
    else
    {
        do{
            
            printf("0:Quitter le jeu.\n1:Nouvelle Partie.\n2:Charge une partie.\n");
            scanf("%d",&rep);
            return rep;
        }while(rep!=0 && rep!=1 && rep!=2);
    }
    
    
}
