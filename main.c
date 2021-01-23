#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define b 100
#include "Fonctions.h"
//=======Declarations des structures===========================================
typedef struct Tbloc{
    char tab[b];//tableau de caractere
    int suiv;//numero du bloc suivant
} Tbloc;

typedef struct Tbloc Buffer;//declaration du buffer

typedef struct Entete{
    int tete;//adresse du premier bloc
    int nbInsert;//nombre globale des caracteres inserer
    int nbSupp;//nombre globale des caractere supprimer
}Entete;

typedef struct Fichier_LOVbarC {
    Entete entete;
    FILE *file;
}LOVbarC;

//=========Machine Abstraite==========================

void Aff_Entete(LOVbarC *F,int i,int val){
    switch(i){
    case 1://modifier la tete
        F->entete.tete=val;
        break;
    case 2://modifier le nombre de caracteres inserer
        F->entete.nbInsert=val;
        break;
    case 3://modifier le nombre de caracteres supprimer
        F->entete.nbSupp=val;
        break;

    }
}

int entete(LOVbarC F,int i){
    switch(i){
    case 1://retourner la tete
        return F.entete.tete;
        break;
    case 2://retourner le nombre de caracteres inserer
        return F.entete.nbInsert;
        break;
    case 3://retourner le nombre de caracteres supprimer
        return F.entete.nbSupp;
        break;

    }
}

void Ecrire_Dir_LOVbarC(LOVbarC *F,int i,Buffer buf){
    fseek(F->file,sizeof(Entete)+sizeof(Buffer)*(i-1),SEEK_SET);//positionné sur le i eme bloc
    fwrite(&buf,sizeof(Buffer),1,F->file);//ecriture
}

void Lire_Dir_LOVbarC(LOVbarC F,int i,Buffer *buf){
    fseek(F.file,sizeof(Entete)+sizeof(Buffer)*(i-1),SEEK_SET);////positionné sur le i eme bloc
    fread(buf,sizeof(Buffer),1,F.file);//lecture
}

void ouvrire_LOVbarC(LOVbarC *F,char nom[],char mode){

    if (mode =='A' || mode =='a'){
        F->file=fopen(nom,"rb+");
        fread(&(F->entete),sizeof(Entete),1,F->file);//lecture de l'entete
    }
    else
    if (mode =='N' || mode =='n'){
        F->file=fopen(nom,"wb+");
        Buffer buf;
        //initialisation de l'entete
        Aff_Entete(F,1,1);
        Aff_Entete(F,2,0);
        Aff_Entete(F,3,0);
        //ecriture d'entete
        fwrite(&(F->entete),sizeof(Entete),1,F->file);
       //initialisation du buffer
        sprintf(buf.tab,"%s","");
        buf.suiv=NULL;
        Ecrire_Dir_LOVbarC(F,1,buf);
    }
    else printf("\nErreur dans le mode d'ouverture!\n");


}

void Fermer_LOVbarC(LOVbarC *F){
    rewind(F->file);
    fwrite(&(F->entete),sizeof(Entete),1,F->file);//sauvgarder l'entete
    rewind(F->file);
    fclose(F->file);
}

//========debugging stuff=======================
void affichage_entete(LOVbarC F){
printf("\nla tete %d",entete(F,1));
printf(" le nombre de caracteres inserer %d",entete(F,2));
printf(" le nombre de caracteres supprimer %d\n",entete(F,3));
}

void affichage_bloc(LOVbarC F,int i){//affichier un seul bloc
    Buffer buf;
    Lire_Dir_LOVbarC(F,i,&buf);
    printf("\nLe contenue du bloc %d :%s",i,buf.tab);
}

void affichage_bParB(LOVbarC F){//affichage bloc par bloc meme si il eté supprimer logiquement

    for (int i=1;i<=entete(F,1);i++){
        affichage_bloc(F,i);
    }

}
//hadi ntesti biha
void ecrire_chaine(LOVbarC *F,int i,char s[b]){
    Buffer buf;
    sprintf(buf.tab,"%s",s);
    Ecrire_Dir_LOVbarC(F,i,buf);
}
LOVbarC F;
int main()
{
    Buffer buf1,buf2,buf3;
    ouvrire_LOVbarC(&F,"texte.txt",'a');

    affichage_entete(F);

    sprintf(buf1.tab,"on est a bloc1");
    Ecrire_Dir_LOVbarC(&F,1,buf1);

    sprintf(buf2.tab,"on est a bloc2");
    Ecrire_Dir_LOVbarC(&F,2,buf2);

    sprintf(buf3.tab,"on est a bloc3");
    Ecrire_Dir_LOVbarC(&F,3,buf3);
    Aff_Entete(&F,1,3);
    affichage_bParB(F);
    Fermer_LOVbarC(&F);


    return 0;
}
