#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Fonctions.h"



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
TOVC F;
ouvrire_TOVC(&F,"not.bin",'n');
Buffer buf;
sprintf(buf.chaine,"hello world");
Ecrire_Dir_TOVC(&F,1,buf);
printf("%s",buf.chaine);
Fermer_TOVC(&F);
return 0;
}
