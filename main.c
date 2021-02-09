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

            j=-1;
        }
    }
    temp[i]='\0';
    sprintf(ouvrage,"%s",temp);

}

void Cree_Livre2(LOVbarC Fo){//Fo: fichier ouvrage
    if (Fo.file!=NULL){
        Buffer tbuf;
        strcpy(tbuf.chaine,"");
        Buffer_liste buf;
        TOVC F;
        ouvrire_TOVC(&F,"livres.bin",'n');
        int bloc=entete(Fo,1);//indice bloc pour basculer le fichier ouvrage
        int tbloc=1;//indice bloc pour basculer le fichier livres
        int j=0;//indice pour tbuf
        int i=0;//indice pour buf
        while(bloc!=NULL){
            Lire_Dir_LOVbarC(Fo,bloc,&buf);
            del_type(buf.tab);//en suprimme le type
            int len_bloc=strlen(buf.tab);
            for (i=0;i<len_bloc;i++){
                sprintf(tbuf.chaine,"%s%c",tbuf.chaine,buf.tab[i]);

                j++;
                if (j==Taille_Bloc-1){
                    tbuf.chaine[j]='\0';
                    j=0;
                    Alloc_Bloc_TOVC(&F);
                    Ecrire_Dir_TOVC(&F,tbloc,tbuf);
                    strcpy(tbuf.chaine,"");
                    tbloc++;
                }
            }
            bloc=buf.suiv;

        }
        //traitement du dernier tbloc et l entet_tovc
        if (j!=0){
            Alloc_Bloc_TOVC(&F);
            Ecrire_Dir_TOVC(&F,tbloc,tbuf);
            Aff_Entete_TOVC(&F,1,tbloc);
            Aff_Entete_TOVC(&F,2,j);
        }
        Fermer_TOVC(&F);

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
void affiche_livre(TOVC F){
printf("\n nb bloc: %d indice libre %d",entete_TOVC(F,1),entete_TOVC(F,2));
Buffer tbuf;
for(int i=1;i<=entete_TOVC(F,1);i++){
    Lire_Dir_TOVC(F,i,&tbuf);
    printf("\n contenu du bloc %d est :%s .",i,tbuf.chaine);
}
}
int main(){
LOVbarC F;
TOVC F2;
Buffer tbuf;
Cree_Ouvrage(&F);
ouvrire_LOVbarC(&F,"ouvrage.bin",'a');
affichage_bParB(F);
Cree_Livre2(F);
ouvrire_TOVC(&F2,"livres.bin",'a');
//Lire_Dir_TOVC(F2,1,&tbuf);
//rintf("\n%s",tbuf.chaine);
//affiche_livre(F2);
affichage_bparb2(F);
return 0;
}
