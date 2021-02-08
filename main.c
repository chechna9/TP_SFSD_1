#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Fonctions.h"
void del_type(char ouvrage[b]){//fonction qui supprime le type
    int j=0,i=0;//j pour confirmer la taille du type par exemple 07 est pas une cle ou une cote
    char temp[b];//variable temporaire
    char taille_type[3];
    strcpy(taille_type,"");
    strcpy(temp,"");
    while (ouvrage[i]!='\0'){

            if (j==40){
                sprintf(taille_type,"%c%c",ouvrage[i],ouvrage[i+1]);//on extraire la taille du type
               //pour connaitre les cases qu il faut suater

            if(strcmp(taille_type,"07")==0){
                i+=9;
            }
            else if(strcmp(taille_type,"10")==0){
                i+=12;

            }
            else if(strcmp(taille_type,"13")==0){
                i+=15;
            }
            else if(strcmp(taille_type,"21")==0){
                i+=23;
            }


            }

        sprintf(temp,"%s%c",temp,ouvrage[i]);
        i++;j++;
        //si il y a plus qu un seul ouvrage dans le bloc
        if (ouvrage[i]=='/'){
                printf("\n slash");
            j=-1;
        }
    }
    temp[i]='\0';
    sprintf(ouvrage,"%s",temp);

}

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
Buffer_liste buf;
Lire_Dir_LOVbarC(F,1,&buf);
printf("\nOLD %s",buf.tab);
del_type(buf.tab);
printf("\n NEW %s",buf.tab);
return 0;
}
