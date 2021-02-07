#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Fonctions.h"

void Cree_Livre2(LOVbarC Fo){//Fo: fichier ouvrage
    if (Fo.file!=NULL){
        Buffer tbuf;
        Buffer_liste buf;
        TOVC F;
        ouvrire_TOVC(&F,"livres.bin",'n');

    }

}





void affichage_bloc2(LOVbarC F,int *i){//affichier un seul bloc
    Buffer_liste buf;
    Lire_Dir_LOVbarC(F,*i,&buf);
    printf("\nLe contenue du bloc %d :%s",*i,buf.tab);
    *i=buf.suiv;
}
void affichage_bparb2(LOVbarC F){
    int i=entete(F,1);
    while(i!=NULL){
        affichage_bloc2(F,&i);
    }
}

int main(){
LOVbarC F;
Cree_Ouvrage(&F);
ouvrire_LOVbarC(&F,"ouvrage.bin",'a');
affichage_entete(F);
affichage_bparb2(F);

return 0;
}
