#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Fonctions.h"
void alea_chaine(char chaine[],int max,int min){ //sup ou egale a min et strictement inf a max
    char alphabet[26]="abcdefghijklmnopqrstuvwxyz";
    strcpy(chaine,"");
    if (max > min){
    int nombreDeCaracteres=rand()%(max - min)+min;
    for (int i=0;i<nombreDeCaracteres;i++){
        chaine[i]=alphabet[rand()%26];
    }
    chaine[nombreDeCaracteres-1]='\0';
    }
    else {
        printf("\nErreur dans les arguments max ou min");
    }

}
void remplir_ouvrage(char ouvrage[b],int cle){
            strcpy(ouvrage,"");
            //insertion de la cle
            char cle_char[4];
            int_to_char(cle,cle_char);
            sprintf(ouvrage,"%s%s",ouvrage,cle_char);

            //insertion du titre
            char titre[20];
            alea_chaine(titre,20,3);
            sprintf(ouvrage,"%s%s",ouvrage,titre);

            //insertion du auteur
            char auteur[20];
            alea_chaine(auteur,20,3);
            sprintf(ouvrage,"%s%s",ouvrage,auteur);

            //insertion du type
            char type[24];
            aleat_type(type);
            sprintf(ouvrage,"%s%s",ouvrage,type);

            //insertion du champ disponible
            char disp[1];
            aleat_disponible(disp);
            sprintf(ouvrage,"%s%s",ouvrage,disp);

            //insertion du la cote (la meme que la cle)
            sprintf(ouvrage,"%s%s",ouvrage,cle_char);

            //insertion du reume
            char resume[50];
            alea_chaine(resume,15,10);
            sprintf(ouvrage,"%s%s",ouvrage,resume);



}

void Cree_Ouvrage2(LOVbarC *F){
    ouvrire_LOVbarC(F,"ouvrage.bin",'n');
    int n=0;
    printf("\nEntrer le nombre des ouvrages: ");
    scanf("%d",&n);
    if(n>0){
        Buffer_liste buf;//buffer
        strcpy(buf.tab,"");
        buf.suiv=NULL;
        int j=0,bloc=1;//indice de buf.suiv
        Aff_Entete(F,1,bloc);
        Aff_Entete(F,4,bloc);
        char ouvrage[b];//variable qui va contenire l'ouvrage
        int saturation=0;//bool qui indique l'obligation d ajouter un autre bloc
        for (int i=0;i<n;i++){
            remplir_ouvrage(ouvrage,i);
            j=strlen(ouvrage)+strlen(buf.tab);

            if (j<b-1){
                if (strlen(buf.tab)>0){//pour separe les ouvrages par un slash /

                    sprintf(buf.tab,"%s/",buf.tab);
                    j++;
                }
                sprintf(buf.tab,"%s%s",buf.tab,ouvrage);//on ajoute l ouvrage dans le bloc
            }else{
                saturation=1;
            }

             if(saturation || i==n-1){

                if (i==7)printf("77");
                Ecrire_Dir_LOVbarC(F,bloc,buf);//on ecrit le bloc
                //modification de lentete
                Aff_Entete(F,2,entete(*F,2)+j);//incrementation du nombre de caractere inserer
                if (i!=n-1)Alloc_Bloc(F);
                bloc++;
                j=0;
                saturation=0;
                //initialisation du buffer par l ouvrage precedent;
                sprintf(buf.tab,ouvrage);




            }

        }

    }


    Fermer_LOVbarC(F);
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
LOVbarC F;
int main(){
    Buffer_liste buf;
    Cree_Ouvrage2(&F);
    ouvrire_LOVbarC(&F,"ouvrage.bin",'a');
    affichage_entete(F);
    affichage_bparb2(F);







return 0;
}
