#include <stdio.h>
#include "menu.h"
#include "partie.h"

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