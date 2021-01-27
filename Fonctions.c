#include "Fonctions.h"
//=========Machine Abstraite===================================

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

void Alloc_Bloc(LOVbarC *F){//en ajoute un bloc vide a la derniere position
    Buffer buf;
    int dernier_Bloc = entete(*F,1);
    Lire_Dir_LOVbarC(*F,dernier_Bloc,&buf);//lecture du dernier bloc
    //printf("lecture\n");
    //modification du dernier bloc et l'entete
    buf.suiv=dernier_Bloc+1;
    Aff_Entete(F,1,dernier_Bloc+1);
    //sauvgarde le bloc
    Ecrire_Dir_LOVbarC(F,dernier_Bloc,buf);
    //printf("sauv 1\n");
    //initalisation du nouveau bloc
    buf.suiv=NULL;
    sprintf(buf.tab,"%s","");
    //sauvgarde du nouveau bloc

    Ecrire_Dir_LOVbarC(F,dernier_Bloc+1,buf);
    //printf("sauvgrad 2\n");

}

//========debugging stuff=======================
void affichage_entete(LOVbarC F){
printf("\nla tete %d",entete(F,1));
printf(" le nombre de caracteres inserer %d",entete(F,2));
printf(" le nombre de caracteres supprimer %d\n",entete(F,3));
}

void affichage_bloc(LOVbarC F,int *i){//affichier un seul bloc
    Buffer buf;
    Lire_Dir_LOVbarC(F,*i,&buf);
    printf("\nLe contenue du bloc %d :%s",*i,buf.tab);
    *i=buf.suiv;
}

void affichage_bParB(LOVbarC F){//affichage bloc par bloc meme si il eté supprimer logiquement
    int i=1;
    while (i!=NULL){
        affichage_bloc(F,&i);
    }

}
//hadi ntesti biha
void ecrire_chaine(LOVbarC *F,int i,char s[b]){
    Buffer buf;
    Lire_Dir_LOVbarC(*F,i,&buf);
    sprintf(buf.tab,"%s",s);
    Aff_Entete(F,2,entete(*F,2)+strlen(s));
    Ecrire_Dir_LOVbarC(F,i,buf);
}

void insertion_nonO(LOVbarC *F,char chaine[b]){
    Alloc_Bloc(F);
    ecrire_chaine(F,entete(*F,1),chaine);


}
