#include "Fonctions.h"
///==================== Machine abstraite TOF=================================================================
void fermer_TOF(TOF *F)
{rewind(F->fichier);
    fwrite(&(F->entete),sizeof(Entete_TOF),1,F->fichier);//sauvgarder l'entete
    rewind(F->fichier);
    fclose(F->fichier);


}
void Aff_Entete_TOF(TOF *F,int i,int val){
    switch(i){
    case 1://modifier la tete
        F->entete.nb_bloc=val;
        break;
    case 2://modifier le nombre de caracteres inserer
        F->entete.dernier_pos=val;
        break;

    }
}

int entete_TOF(TOF F,int i){
    switch(i){
    case 1://retourner le nombre de bloc
        return F.entete.nb_bloc;
        break;
    case 2://retourner la derniere position
        return F.entete.dernier_pos;
        break;
    }
}
void Ecrire_Dir_TOF(TOF *F,int i,TOF_Bloc buf){
    printf("\n====afichage dans ecrir dir tof");
    affiche_enreg(buf.tab[0]);
    fseek(F->fichier,sizeof(Entete_TOF)+sizeof(TOF_Bloc)*(i-1),SEEK_SET);//positionné sur le i eme bloc
    fwrite(&buf,sizeof(TOF_Bloc),1,F->fichier);//ecriture

}

void Lire_Dir_TOF(TOF F,int i,TOF_Bloc *buf){
    fseek(F.fichier,sizeof(Entete_TOF)+sizeof(TOF_Bloc)*(i-1),SEEK_SET);////positionné sur le i eme bloc
    fread(buf,sizeof(TOF_Bloc),1,F.fichier);//lecture
    //printf("la valeur lue est %s\n",buf->chaine);
}
void ouvrire_TOF(TOF *F,char nom[20],char mode){

    if (mode =='A' || mode =='a'){
        F->fichier=fopen(nom,"rb+");
        fread(&(F->entete),sizeof(Entete_TOF),1,F->fichier);//lecture de l'entete
    }
    else
    if (mode =='N' || mode =='n'){
        F->fichier=fopen(nom,"wb+");
        TOF_Bloc buf;
        //initialisation de l'entete
        Aff_Entete_TOF(F,1,0);
        Aff_Entete_TOF(F,2,0);
       //ecriture d'entete
        fwrite(&(F->entete),sizeof(Entete_TOF),1,F->fichier);
       //nitialisation du Buffer_liste
       // sprintf(buf.chaine,"");
       // Ecrire_Dir_TOVC(F,1,buf);
    }
    else printf("\nErreur dans le mode d'ouverture!\n");
}

void Alloc_bloc_TOF(TOF *F )
{Aff_Entete_TOF(F,1,entete_TOF(*F,1)+1);}
///===================================================LOVC================================================================
void Aff_Entete_LOVC(LOVC *F,int i,int val){
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
    case 4:
        F->entete.nb_bloc=val;
     break;
    }
}

int entete_LOVC(LOVC F,int i){
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
    case 4:
       return F.entete.nb_bloc;
        break;

    }
}
void Ecrire_Dir_LOVC(LOVC *F,int i,Buffer_LOVC buf){
    fseek(F->file,sizeof(Entete_LOVC)+sizeof(Buffer_LOVC)*(i-1),SEEK_SET);//positionné sur le i eme bloc
    fwrite(&buf,sizeof(Buffer_LOVC),1,F->file);//ecriture

}

void Lire_Dir_LOVC(LOVC F,int i,Buffer_LOVC *buf){
    fseek(F.file,sizeof(Entete_LOVC)+sizeof(Buffer_LOVC)*(i-1),SEEK_SET);////positionné sur le i eme bloc
    fread(buf,sizeof(Buffer_LOVC),1,F.file);//lecture
}


void ouvrire_LOVC(LOVC *F,char nom[20],char mode){

    if (mode =='A' || mode =='a'){
        F->file=fopen(nom,"rb+");
        fread(&(F->entete),sizeof(Entete_LOVC),1,F->file);//lecture de l'entete
    }
    else
    if (mode =='N' || mode =='n'){
        F->file=fopen(nom,"wb+");
      Buffer_LOVC buf;
        //initialisation de l'entete
        Aff_Entete_LOVC(F,1,0);
        Aff_Entete_LOVC(F,2,0);
        Aff_Entete_LOVC(F,3,0);
        Aff_Entete_LOVC(F,4,0);
        //ecriture d'entete
       fwrite(&(F->entete),sizeof(Entete_LOVC),1,F->file);
       //nitialisation du Buffer_liste
        sprintf(buf.tab,"");
        buf.suiv=NULL;
        Ecrire_Dir_LOVC(F,1,buf);
    }
    else printf("\nErreur dans le mode d'ouverture!\n");


}

void Fermer_LOVC(LOVC *F){
    rewind(F->file);
    fwrite(&(F->entete),sizeof(Entete_LOVC),1,F->file);//sauvgarder l'entete
    rewind(F->file);
    fclose(F->file);
}
void Alloc_Bloc_LOVC(LOVC *F,int dernier_Bloc){//en ajoute un bloc vide a la derniere position
  Buffer_LOVC buf;
    //Lire_Dir_LOVC(*F,dernier_Bloc,&buf);//lecture du dernier bloc
    //modification du dernier bloc et l'entete
    Aff_Entete_LOVC(F,4,dernier_Bloc);
    //sauvgarde le bloc
    buf.suiv=dernier_Bloc+1;
    sprintf(buf.tab,"%s","");
    //sauvgarde du nouveau bloc
    Ecrire_Dir_LOVC(F,dernier_Bloc,buf);
    //initalisation du nouveau bloc
}
void creer_memoire(LOVbarC Fo)
{


if (Fo.file!=NULL){
        Buffer_LOVC Lbuf;
        strcpy(Lbuf.tab,"");
        Buffer_liste buf;
        LOVC F;
        ouvrire_LOVC(&F,"Memoire.bin",'n');
        int bloc=entete(Fo,1);//indice bloc pour basculer le fichier ouvrage
      //  int tbloc=1;//indice bloc pour basculer le fichier livres
      int suiv=1;
        int j=0;//indice pour tbuf
        int i=0;//indice pour buf
         while(bloc!=NULL){

           Aff_Entete_LOVC(&F,1,1);
            Lire_Dir_LOVbarC(Fo,bloc,&buf);
            del_type(buf.tab);//en suprimme le type
            printf("\n%s",buf.tab);
            int len_bloc=strlen(buf.tab);
            for (i=0;i<b;i++){
                if(buf.tab[i]=='\0'){ sprintf(Lbuf.tab,"%s\0",Lbuf.tab);
                break;
                  }
                sprintf(Lbuf.tab,"%s%c",Lbuf.tab,buf.tab[i]);

                j++;
                if (j==Taille_Bloc-1){
                    Lbuf.tab[j]='\0';
                    j=0;
                    Alloc_Bloc_LOVC(&F,suiv);
                   Lbuf.suiv=suiv+1;
                  Ecrire_Dir_LOVC(&F,suiv,Lbuf);
                  suiv++;
             strcpy(Lbuf.tab,"");
            }

            }
            if(buf.suiv!=NULL){sprintf(Lbuf.tab,"%s/",Lbuf.tab);
            j++;
            if (j==Taille_Bloc-1){
                    Lbuf.tab[j]='\0';
                    j=0;
                    Alloc_Bloc_LOVC(&F,suiv);
                   Lbuf.suiv=suiv+1;
                  Ecrire_Dir_LOVC(&F,suiv,Lbuf);
                  suiv++;
                  strcpy(Lbuf.tab,"");
                  }
            }
            bloc=buf.suiv;
            Lbuf.suiv=NULL;
            Ecrire_Dir_LOVC(&F,suiv,Lbuf);

            Aff_Entete_LOVC(&F,4,suiv);


        }

        Fermer_LOVC(&F);
}

}

void affichage_Memoire(LOVC F){
    int i=entete_LOVC(F,1);
    Buffer_LOVC buf;
    printf("\n************************************DEBUT AFFICHAGE MEMOIRE************************************************\n");
  while(i!=NULL){
       Lire_Dir_LOVC(F,i,&buf);
        printf(" le contenue du beffer est %s\n",buf.tab);
        i=buf.suiv;
      }
    printf("\n************************************FIN AFFICHAGE MEMOIRE************************************************\n");

}

///------------------------------------------------------------------------------------------------------------
//=========Machine Abstraite LOV\C============================================================================


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
    case 4:
        F->entete.nb_bloc=val;
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
    case 4:
       return F.entete.nb_bloc;
        break;

    }
}

void Ecrire_Dir_LOVbarC(LOVbarC *F,int i,Buffer_liste buf){
    fseek(F->file,sizeof(Entete)+sizeof(Buffer_liste)*(i-1),SEEK_SET);//positionné sur le i eme bloc
    fwrite(&buf,sizeof(Buffer_liste),1,F->file);//ecriture

}

void Lire_Dir_LOVbarC(LOVbarC F,int i,Buffer_liste *buf){
    fseek(F.file,sizeof(Entete)+sizeof(Buffer_liste)*(i-1),SEEK_SET);////positionné sur le i eme bloc
    fread(buf,sizeof(Buffer_liste),1,F.file);//lecture
}
void ouvrire_LOVbarC(LOVbarC *F,char nom[20],char mode){

    if (mode =='A' || mode =='a'){
        F->file=fopen(nom,"rb+");
        fread(&(F->entete),sizeof(Entete),1,F->file);//lecture de l'entete
    }
    else
    if (mode =='N' || mode =='n'){
        F->file=fopen(nom,"wb+");
        Buffer_liste buf;
        //initialisation de l'entete
        Aff_Entete(F,1,0);
        Aff_Entete(F,2,0);
        Aff_Entete(F,3,0);
        Aff_Entete(F,4,0);
        //ecriture d'entete
       fwrite(&(F->entete),sizeof(Entete),1,F->file);
       //nitialisation du Buffer_liste
        sprintf(buf.tab,"");
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

void Alloc_Bloc(LOVbarC *F,int dernier_Bloc ){//en ajoute un bloc vide a la derniere position
    Buffer_liste buf;

    Lire_Dir_LOVbarC(*F,dernier_Bloc,&buf);//lecture du dernier bloc
    //modification du dernier bloc et l'entete
    buf.suiv=dernier_Bloc+1;
    Aff_Entete(F,4,dernier_Bloc);
    //sauvgarde le bloc
   // Ecrire_Dir_LOVbarC(F,dernier_Bloc,buf);

    //initalisation du nouveau bloc
    buf.suiv=NULL;
    sprintf(buf.tab,"%s","");
    //sauvgarde du nouveau bloc
    Ecrire_Dir_LOVbarC(F,dernier_Bloc,buf);


}
///=============Macihne abstraite TOVC======================================
void Aff_Entete_TOVC( TOVC *F,int i,int val){
    switch(i){
    case 1://le dernier bloc
        F->entete.nb_bloc=val;
        break;
    case 2://la derniere position dans le dernier bloc
        F->entete.dernier_pos=val;
        break;

    }
}

int entete_TOVC(TOVC F,int i){
    switch(i){
    case 1://retourner la tete
        return F.entete.nb_bloc;
        break;
    case 2://retourner la derniere position dans le ddernier bloc
        return F.entete.dernier_pos;
        break;


    }
}
void Ecrire_Dir_TOVC(TOVC *F,int i,Buffer *buf){
    fseek(F->fichier,sizeof(Entete_TOVC)+sizeof(Tbloc)*(i-1),SEEK_SET);//positionné sur le i eme bloc
    fwrite(buf,sizeof(Tbloc),1,F->fichier);//ecriture

}

void Lire_Dir_TOVC(TOVC F,int i,Buffer *buf){
    fseek(F.fichier,sizeof(Entete_TOVC)+sizeof(Tbloc)*(i-1),SEEK_SET);////positionné sur le i eme bloc
    fread(buf,sizeof(Tbloc),1,F.fichier);//lecture
    //printf("la valeur lue est %s\n",buf->chaine);
}
void ouvrire_TOVC(TOVC *F,char nom[20],char mode){

    if (mode =='A' || mode =='a'){
        F->fichier=fopen(nom,"rb+");
        fread(&(F->entete),sizeof(Entete_TOVC),1,F->fichier);//lecture de l'entete
    }
    else
    if (mode =='N' || mode =='n'){
        F->fichier=fopen(nom,"wb+");
        Buffer buf;
        //initialisation de l'entete
        Aff_Entete_TOVC(F,1,0);
        Aff_Entete_TOVC(F,2,0);
       //ecriture d'entete
        fwrite(&(F->entete),sizeof(Entete_TOVC),1,F->fichier);
       //nitialisation du Buffer_liste
        sprintf(buf.chaine,"");
        Ecrire_Dir_TOVC(F,1,&buf);
    }
    else printf("\nErreur dans le mode d'ouverture!\n");


}

void Fermer_TOVC(TOVC *F){
    rewind(F->fichier);
    fwrite(&(F->entete),sizeof(Entete_TOVC),1,F->fichier);//sauvgarder l'entete
    rewind(F->fichier);
    fclose(F->fichier);
}


void Alloc_Bloc_TOVC(TOVC *F){
    Aff_Entete_TOVC(F,1,entete_TOVC(*F,1)+1);
}

///=========================Fonctions du TP========================================
void del_type(char ouvrage[b]){//fonction qui supprime le type
    int j=0,i=0;//j pour ouvrage i pour temp
    char temp[b];//variable temporaire
    strcpy(temp,"");
    for(j=0;j<strlen(ouvrage);j++){

        if (j!=2*(t-1)+8 && j!=2*(t-1)+9){
            sprintf(temp,"%s%c",temp,ouvrage[j]);
        }
    }
    sprintf(ouvrage,"%s",temp);
    //modfication du champ taille
    char taille[5];
    strncat(taille,ouvrage,4);
    taille[4]='\0';
    int taille_int=atoi(taille)-2;
    char nouvelle_taille[5];
    int_to_char(taille_int,nouvelle_taille);
    for(int i=0;i<4;i++){
        ouvrage[i]=nouvelle_taille[i];
    }

}
void Cree_Livre(LOVbarC Fo){//Fo: fichier ouvrage
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
                    Ecrire_Dir_TOVC(&F,tbloc,&tbuf);
                    strcpy(tbuf.chaine,"");
                    tbloc++;

                }
            }
           if(buf.suiv!=NULL){ sprintf(tbuf.chaine,"%s/",tbuf.chaine);
            j++;
              if (j==Taille_Bloc-1){
                    tbuf.chaine[j]='\0';
                    j=0;
                    Alloc_Bloc_TOVC(&F);
                    Ecrire_Dir_TOVC(&F,tbloc,&tbuf);
                    strcpy(tbuf.chaine,"");
                    tbloc++;

                }
           }
            bloc=buf.suiv;


        }
        //traitement du dernier tbloc et l entet_tovc
        if (j!=0){

            Alloc_Bloc_TOVC(&F);
            Ecrire_Dir_TOVC(&F,tbloc,&tbuf);
            Aff_Entete_TOVC(&F,1,tbloc);
            Aff_Entete_TOVC(&F,2,j);
        }
        Fermer_TOVC(&F);

    }

}


void majuscule(char nom[20])
{int i=0;
while(nom[i])
{
    nom[i]=toupper(nom[i]);
    i++;
}
}



//========debugging stuff=======================
void affichage_entete(LOVbarC F){
printf("\n la tete %d\n",entete(F,1));
printf(" le nombre de caracteres inserer %d\n",entete(F,2));
printf(" le nombre de caracteres supprimer %d\n",entete(F,3));
printf(" Le nombre de bloc est : %d\n",entete(F,4));
}

void affichage_bloc(LOVbarC F,int *k){//affichier un seul bloc
    Buffer_liste buf;
    int indice=0,cpt=1, i=0,taille_type;
    char chaine[b];
    char chaine2[t];
    strcpy(chaine2,"");
    Lire_Dir_LOVbarC(F,*k,&buf);
    sprintf(chaine,"%s",buf.tab);
    printf(" \n le contenue de bloc  %d est : %s\n",*k,buf.tab);
    while(chaine[indice]!='\0')
    {printf(" \n louvrage %d est :\n",cpt);
         for(i=0;i!=4;i++)
         {chaine2[i]=chaine[indice];
         indice++;
           }
         chaine2[4]='\0';
         printf(" la clee est : %s\n",chaine2);
         for(i=0;i!=t-1;i++)
         {chaine2[i]=chaine[indice];indice++;
        }
         chaine2[t-1]='\0';
         printf(" la titre est  est : %s\n",chaine2);
           for(i=0;i!=t-1;i++)
         {chaine2[i]=chaine[indice];
          indice++;}

         chaine2[t-1]='\0';
         printf(" les auteurs sont : %s\n",chaine2);
          for(i=0;i!=2;i++)
         {chaine2[i]=chaine[indice];indice++; }
         chaine2[2]='\0';
         taille_type=atoi(chaine2);
         for(i=0;i!=taille_type;i++)
         {chaine2[i]=chaine[indice];
         indice++; }
            chaine2[taille_type]='\0';
             printf(" le type est  : %s\n",chaine2);
             for(i=0;i!=4;i++)
         {chaine2[i]=chaine[indice];
            indice++;}
             chaine2[4]='\0';
             printf(" l'anne de publication est : %s\n",chaine2);
        if(chaine[indice]=='1'){printf(" oui il est disponible \n");}
        else{printf(" desolee il n'est pas disponible \n");}
        indice++;
        for(i=0;i!=4;i++)
         {chaine2[i]=chaine[indice];
         indice++;
           }
         chaine2[4]='\0';
         printf(" la cote est : %s\n",chaine2);

        printf(" le resume : ");
       while((chaine[indice]!='/')&&(chaine[indice]!='\0'))
          {printf("%c",chaine[indice]);
           indice++;
         }
         printf("\n/////////////////////////////////////////////////////////////////////////////////////////////////\n");
         if(chaine[indice]!='\0'){indice++;cpt++;}


    }
    *k=buf.suiv;
}



void affichage_bParB(LOVbarC F){//affichage bloc par bloc meme si il eté supprimer logiquement

    int j =0;
    char ouvrage[b];
    int taille,i=entete(F,1);
    Buffer_liste buf;
    if(i!=NULL){Lire_Dir_LOVbarC(F,i,&buf);}
printf("\n***********************************************DEBUT AFFICHAGE**********************************************\n");
    while (i!=0){

        //affichage_bloc(F,&i);
        recuperer_chaine(&F,4,&i,&j,ouvrage,&buf);
        taille=atoi(ouvrage);
           recuperer_chaine(&F,taille,&i,&j,ouvrage,&buf);
        if(i!=NULL){  printf(" le contenue de buf %d est %s\n",i,ouvrage);}

    }
printf("\n***********************************************FIN AFFICHAGE**********************************************\n");
}

//hadi ntesti biha
void ecrire_chaine(LOVbarC *F,int i,char s[b]){
    Buffer_liste buf;
    Lire_Dir_LOVbarC(*F,i,&buf);
    sprintf(buf.tab,"%s",s);

    Aff_Entete(F,2,entete(*F,2)+strlen(s));
    Ecrire_Dir_LOVbarC(F,i,buf);
}

void insertion_nonO(LOVbarC *F,char chaine[b]){
   // Alloc_Bloc(F);
    ecrire_chaine(F,entete(*F,1),chaine);


}

void aleat_chaine(char chaine[50],int taille)
{
    char alphabet[26]="abcdefghijklmnopqrstuvwxyz";
    strcpy(chaine,"");


    for (int i=0;i<taille;i++){
        chaine[i]=alphabet[rand()%26];
    }
    chaine[taille-1]='\0';

}
void aleat_resum(char chaine[50],int max , int min)
{ char alphabet[26]="abcdefghijklmnopqrstuvwxyz";
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
void aleat_type(char *chaine[3])
{int n ;
char type[3];
   n=rand()%4;
   switch(n)
   {
       case 0  :
           strcpy(type,"TI");// Text imprime
           break;
        case 1  :
           strcpy(type,"DE");// document electronique
           break;

        case 2  :
           strcpy(type,"AR");// Article
           break;
        case 3  :
           strcpy(type,"PR");// P
           break;
   }
   sprintf(chaine,"%s",type);
}
void aleat_anne(char chaine[5])
{int n ;
  n=rand()%72+1950;

  int_to_char(n,chaine);

}
void int_to_char(int num ,char chain[5])
 {char chaine[11]="0123456789";
 char chaine2[5]="0000";
 int i ,n;
 for(i=3;i!=-1;i--)
 {n=num%10;
 if(n!=0){chaine2[i]=chaine[n];}
num=num/10;
}
chaine2[4]='\0';
 sprintf(chain,"%s",chaine2);
}
void aleat_disponible(char *dispo[2])
{
    int a;
    a=(int) rand()%2;
     sprintf(dispo,"%d",a);
}



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
            strcpy(ouvrage,"0000");
            //generation de la cle
            char cle_char[5];
            int_to_char(cle,cle_char);
sprintf(ouvrage,"%s%s",ouvrage,cle_char);
            //generation du titre
            char titre[t];//de 19 caractere
            aleat_chaine(titre,t);//de t caractere
sprintf(ouvrage,"%s%s",ouvrage,titre);
            //generation du auteur
            char auteur[t];
           aleat_chaine(auteur,t);//de t caractere
sprintf(ouvrage,"%s%s",ouvrage,auteur);
            //generation du type
            char type[3];
            aleat_type(type);
sprintf(ouvrage,"%s%s",ouvrage,type);
            //generation du l anne
            char anne_char[5];
            aleat_anne(anne_char);
sprintf(ouvrage,"%s%s",ouvrage,anne_char);
            //generation du champ disponible
            char disp[2];
            aleat_disponible(disp);
sprintf(ouvrage,"%s%s",ouvrage,disp);

            //generation du la cote (la meme que la cle)
sprintf(ouvrage,"%s%s",ouvrage,cle_char);
            //generation du reume
            char resume[50];
            aleat_resum(resume,15,10);
            sprintf(ouvrage,"%s%s",ouvrage,resume);
            int taille=strlen(ouvrage)-4;
            char taille_char[5];
            int_to_char(taille,taille_char);
            for (int i=0;i<4;i++){
                ouvrage[i]=taille_char[i];
            }
}
void Cree_Ouvrage(LOVbarC *F){
    ouvrire_LOVbarC(F,"ouvrages.bin",'n');
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
        int i;
        int ernier_bloc=1;
        int dernier_inserer=1;
        char ouvrage[b];//variable qui va contenire l'ouvrage
        int saturation=0;//bool qui indique l'obligation d ajouter un autre bloc
        for ( i=0;i<n;i++){
            remplir_ouvrage(ouvrage,i);

            j=strlen(ouvrage)+strlen(buf.tab);

            if (j<b-1){


                sprintf(buf.tab,"%s%s",buf.tab,ouvrage);//on ajoute l ouvrage dans le bloc
            }else{
                saturation=1;

                 // if(i == n-1)  {dernier_inserer=1;}
            }

             if(saturation==1 || i==n-1){
                if((saturation==0)&&(i == n-1)){buf.suiv=NULL;}
               else{buf.suiv=bloc+1;}
                Alloc_Bloc(F,dernier_inserer);
                 dernier_inserer++;
                Ecrire_Dir_LOVbarC(F,bloc,buf);//on ecrit le bloc
                Aff_Entete(F,2,entete(*F,2)+j);//incrementation du nombre de caractere inserer
                j=0;
                 if(saturation==1){ sprintf(buf.tab,"%s",ouvrage);}
                   else{strcpy(buf.tab,"");}
                   saturation=0;
                   bloc++;


                 }

        }
        if(strcmp(buf.tab,"")!=0)
        {
            buf.suiv=NULL;
            Ecrire_Dir_LOVbarC(F,bloc,buf);//on ecrit le bloc
            Aff_Entete(F,2,entete(*F,2)+strlen(buf.tab));//incrementation du nombre de caractere inserer

        }



    }



    Fermer_LOVbarC(F);
}
void recherche (LOVbarC *F ,int clee, int *bloc, int *pos , int *trouv)
{
    int i,k,j=0;
    i=entete(*F,1);
    *trouv=0;
    int taille;
    char taille_art[5];
    Buffer_liste buf;
    int stop=0;
    int indice =0;
    char ouvrage[b]; // on recupere l'ouvrage
    char cle2[5];// la clee recuperer de l'ouvrage

    if(i!=NULL){
            Lire_Dir_LOVbarC(*F,i,&buf);
    }
     while (i!=0){
       //affichage_bloc(F,&i);
        recuperer_chaine(F,4,&i,&j,taille_art,&buf);
        taille=atoi(taille_art);
        recuperer_chaine(F,4,&i,&j,cle2,&buf);
        cle2[5]='\0';
        printf(" clee = %s\n",cle2);

       if(i==0){*pos=j;break;}
        j-=8;
        *bloc=i;
        *pos=j;




         if(clee==atoi(cle2)){
                *trouv=1;

                break;
         }
        else  if(clee<atoi(cle2)){
                        break;
                        }
          recuperer_chaine(&F,taille+4,&i,&j,ouvrage,&buf);




    }



}
void insertion(LOVbarC *F )
{ char *type[50];
    int clee,trouv,bloc,pos;
       char *cle[4];
       char  titre[50];
       char disponible[1];
       char  annee[4];
       char auteurs[50];
       char resume[50];
       char ouvrage[200];

       printf("entrer la clee :");scanf("%d",clee);
       recherche(F,clee,&bloc,&pos,&trouv);
       if(trouv==0){
           Buffer_liste buf;
            int_to_char(clee,cle);
            aleat_anne(annee);
           // aleat_chaine(titre,t);
           // aleat_type(type,t);
            aleat_disponible(disponible);
            aleat_chaine(auteurs,t);
            aleat_resum(resume,10,15);
            sprintf(ouvrage,"%s%s%s%s%s%s%s%s",cle,titre,auteurs,type,annee,disponible,cle,resume);
           Lire_Dir_LOVbarC(*F,bloc,&buf);
 }

       else{printf(" il existe deja ");}


}
void modif_dispo(LOVbarC *F ,int clee , char nv_etat) // 1 pour disponible et 0 pour indisponible
{int pos,bloc,trouv;
 recherche(F,clee,&bloc,&pos,&trouv);
 if(trouv==1)
 {int i;
     Buffer_liste buf;
     Lire_Dir_LOVbarC(*F,bloc,&buf);
   pos=pos+14+(2*(t-1));
   buf.tab[pos]=nv_etat;
   Ecrire_Dir_LOVbarC(F,bloc,buf);
   }

 else
    {printf(" desole ce livre n'existe pas merci d'entrer une clee qui existe!\n"); }

}

///=================================================================
void del_type_cote(char ouvrage[b])
{
    del_type(ouvrage);
    int j=0,i=0;//j pour ouvrage i pour temp
    char temp[b];//variable temporaire
    strcpy(temp,"");
    for(j=0;j<strlen(ouvrage);j++){

        if (j!=2*(t-1)+13 && j!=2*(t-1)+14 && j!=2*(t-1)+15 && j!=2*(t-1)+16){
            sprintf(temp,"%s%c",temp,ouvrage[j]);
        }
    }
    sprintf(ouvrage,"%s",temp);
    //modfication du champ taille
    char taille[5];
    strncat(taille,ouvrage,4);
    taille[4]='\0';
    int taille_int=atoi(taille)-4;
    char nouvelle_taille[5];
    int_to_char(taille_int,nouvelle_taille);
    for(int i=0;i<4;i++){
        ouvrage[i]=nouvelle_taille[i];
    }


}
int detectType(char ouvrage[b]){

    char type=ouvrage[2*(t-1)+8];
    switch (type){
    case 'A' :
        return 1;//1 est article
        break;
    case 'P':
        return 2;//2 est periodique
        break;
    case 'T':
        return 3;//3 est Texte imprime
        break;
    case 'D':
        return 4;//4 est Document electronique
        break;
    default:
        printf("\nType introuvale %s",type);
        break;
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
void recuperer_chaine(LOVbarC *F,int n, int *i, int *j, char chaine[],Buffer_liste *buf) //
   {

    int k=0;
    sprintf(chaine,"%s","");

    for(k=0;k<n;k++)                    // boucle de n itérations correspondant a la longueur de la chaine
    {                            // indice de parcours de la chaine resultata et j celui du tableau
        if((*j)<=b && buf->tab[(*j)]!='\0') // si le kièmem caractère de la chaine correspondant au j ime car du buffer  est toujour dans le bloc i et le bloc tjr contient des information
        {                               // le caractère 99 correspond a la fin de la chaine dans le tableau
            chaine[k]=buf->tab[(*j)];   // recuperation du caractère dans la position k de la chaine
            (*j)++;                      // deplacement d'une position dans le buffer
        }
        else                             // si le k ièeme caractère a recuperer sort du buffer
        {
            (*i)=buf->suiv;

            if(*i==NULL){  break;}
            // on passe au suivant du bloc i dans la liste
            Lire_Dir_LOVbarC(*F,(*i),buf);
            // lecture
            chaine[k]=buf->tab[0];       // recuperation du premier caractère du tableau de carractère correspondant au ka ième car de la chaine
            (*j)=1;                      //positionnement eu second caractère dans le nouveau buffer
        }
    }
   chaine[k]='\0';
                         // fin de la chaine obtenue
}
void remplir_livre(TOVC *F , int *bloc , int *pos , char ouvrage[] ,Buffer * buf )
{

    for(int i =0 ; i<strlen(ouvrage); i++){
        //printf(" i = %d\n",i);
        if(Taille_Bloc-1==*pos){
        //printf(" ecriture \n");
        Alloc_Bloc_TOVC(F);
        Aff_Entete_TOVC(F,2,entete_TOVC(*F,2)+strlen(buf->chaine));
        Ecrire_Dir_TOVC(F,*bloc,buf);
            (*bloc)++;
            *pos=0;
    }



    buf->chaine[*pos]=ouvrage[i];

    (*pos)++;
}
buf->chaine[*pos]='\0';
}

void remplir_memoire(LOVC *F ,char ouvragee[b] ,int * bloc ,int *pos , Buffer_LOVC *buf ){
int i ;
int n;
//scanf("%d",&n);
printf(" pos = %d\n",(*pos));
    printf(" strelen = %d\n",strlen(ouvragee));
for(i =0 ; i != strlen(ouvragee);i++)
{
    if(b-1==*pos)
{Alloc_Bloc_LOVC(F,*bloc);
    buf->suiv=(*bloc)+1;

    int n ;

    buf->suiv=(*bloc)+1;


    Ecrire_Dir_LOVC(F,*bloc,*buf);
    (*bloc)++;
   (*pos)=0;
}
   buf->tab[*pos]=ouvragee[i];
   (*pos)++;

}
buf->tab[*pos]='\0';
}

void remplir_articl(TOVC *F , int *bloc , int * pos , char ouvrage[] , Tbloc *buf ){
 for(int i =0 ; i<strlen(ouvrage); i++){
        //printf(" i = %d\n",i);
        if(Taille_Bloc-1==*pos){
        //printf(" ecriture \n");
        Alloc_Bloc_TOVC(F);
        Aff_Entete_TOVC(F,2,entete_TOVC(*F,2)+strlen(buf->chaine));
        Ecrire_Dir_TOVC(F,*bloc,buf);
            (*bloc)++;
            *pos=0;
    }



    buf->chaine[*pos]=ouvrage[i];

    (*pos)++;
}
buf->chaine[*pos]='\0';

}


void remplir_periodique(TOF *F , int *bloc ,int *pos,TOF_Bloc *buf ,enregistrement enrg){
    if((*pos)== Taille_Bloc_TOF-1){
        Alloc_bloc_TOF(F);
        Aff_Entete_TOF(F,2,*pos);
        buf->nb_enreg_inserer=*pos;
        Ecrire_Dir_TOF(F,*bloc,*buf);

        (*bloc)++;
        (*pos)=0;
        }

    buf->tab[(*pos)]=enrg;

   *pos=*pos+1;
   printf(" la position est %d\n",*pos);
    }


void cree_fichier(LOVbarC F){
    Buffer_liste buf;
    TOVC F_art,F_liv;//F1 article ,F3 livre
    Buffer buf_art,buf_liv;
    LOVC F_mem;//F2 memoires
    Buffer_LOVC buf_mem;
    TOF F_per;//F4 periodique
    TOF_Bloc buf_per;
Aff_Entete_TOVC(&F_liv,2,0);
Aff_Entete_TOVC(&F_liv,1,0);
    ouvrire_TOF(&F_per,"periodique.bin",'n');
    ouvrire_LOVC(&F_mem,"memoires.bin",'n');
    ouvrire_TOVC(&F_liv,"livres.bin",'n');
    ouvrire_TOVC(&F_art,"articles.bin",'n');
    int i=0,bloc=0;//indices ouvrages.bin
    int pos_mem=0,bloc_mem=1;//indices memoires.bin
   int pos_per=0,bloc_per=1;//indices periodique.bin
    int pos_liv=0,bloc_liv=1;//indices livres.bin
    int pos_art=0,bloc_art=1;//indices articles.bin0
       bloc= entete(F , 1);
       int n=0;
    if(bloc!=NULL){
            Lire_Dir_LOVbarC(F,bloc,&buf);
    }

    while(bloc!=NULL){
            char taille_char[5];
            recuperer_chaine(&F,4,&bloc,&i,taille_char,&buf);
            int taille = atoi(taille_char);
            char ouvrage[b];
            i-=4;
            recuperer_chaine(&F,taille+4,&bloc,&i,ouvrage,&buf);
            if (bloc==NULL){break;}
            printf("\n======Original=====\nlouvrage avant switch est %s\n",ouvrage);

            switch(detectType(ouvrage)){///10detectType(ouvrage)
            case 1://cas d un article
                printf("\n================Article================\n");
                del_type_cote(ouvrage);
                remplir_articl(&F_art,&bloc_art,&pos_art,ouvrage,&buf_art);

                break;
            case 2://cas d un periodique
                printf("\n================periodique================\n");
                enregistrement enrg;
                remplir_enreg(ouvrage,&enrg);//del type est dans remplire enreg
                remplir_periodique(&F_per,&bloc_per,&pos_per ,&buf_per,enrg);
                break;
            case 3://cas d un livre
                printf("\n================Livre================\n");
                del_type(ouvrage);


               remplir_livre(&F_liv,&bloc_liv,&pos_liv,ouvrage,&buf_liv);

                break;
            case 4://cas d une memoire
                printf("\n================Memoire================\n");
                del_type(ouvrage);
                Aff_Entete_LOVC(&F_mem,1,1);

                remplir_memoire(&F_mem,ouvrage,&bloc_mem,&pos_mem,&buf_mem);
                break;

             }
    }
    if ((pos_art!=0)&&(pos_art<Taille_Bloc))
    {  Alloc_Bloc_TOVC(&F_art);
     Aff_Entete_TOVC(&F_art,2,entete_TOVC(F_art,2)+strlen(buf_art.chaine));
            Ecrire_Dir_TOVC(&F_art,bloc_art,&buf_art);

    }



     if ((pos_liv!=0)&&(pos_liv<Taille_Bloc))
    {       Alloc_Bloc_TOVC(&F_liv);
    Aff_Entete_TOVC(&F_liv,2,entete_TOVC(F_liv,2)+strlen(buf_liv.chaine));

        Ecrire_Dir_TOVC(&F_liv,bloc_liv,&buf_liv);

    }

     if ((pos_mem!=0)&&(pos_mem<b))
    {         Alloc_Bloc_LOVC(&F_mem,bloc_mem);

    Aff_Entete_LOVC(&F_mem,1,1);
    int n ;
     buf_mem.suiv=NULL;
    Ecrire_Dir_LOVC(&F_mem,bloc_mem,buf_mem );
    }
        if(pos_mem==0){
        Lire_Dir_LOVC(F_mem,bloc_mem-1,&buf_mem);

        buf_mem.suiv=NULL;
         Ecrire_Dir_TOVC(&F_art,bloc_mem-1,&buf_mem);

    }
    printf( "%d pos_per \n",pos_per);
    if(pos_per!=0)
    {Alloc_bloc_TOF(&F_per);
        buf_per.nb_enreg_inserer=pos_per;

        Aff_Entete_TOF(&F_per,2,pos_per);

        Ecrire_Dir_TOF(&F_per,bloc_per,buf_per);


    }

    Fermer_TOVC(&F_art);

     Fermer_TOVC(&F_liv);
     fermer_TOF(&F_per);
     Fermer_LOVC(&F_mem);
     Fermer_LOVbarC(&F);



}
void Affichage_TOF(TOF F)
{int nb_bloc=entete_TOF(F,1);
TOF_Bloc buf;

int dernier_pos=entete_TOF(F,2);
for(int i =1;i!=nb_bloc+1;i++)
{ Lire_Dir_TOF(F,i,&buf);

    for(int ind = 0  ; ind!=buf.nb_enreg_inserer ; ind++)
{ if( i==nb_bloc && ind==dernier_pos  )break;
printf("////////////////////////////////////////////////////////////\n");
affiche_enreg(buf.tab[ind]);


}

}

}
void remplir_enreg(char ouvrage[b],enregistrement *enr){
    del_type(ouvrage);

    int i=4 ,pos=0;
    char cle[5];
    for(pos=0;pos!=4;pos++)
    { enr->cle[pos]=ouvrage[i];
    i++;
   }
    enr->cle[4]='\0';

    for(pos=0;pos!=t-1;pos++)
    { enr->titre[pos]=ouvrage[i];
      i++;
    }
    enr->titre[t-1]='\0';
    for(pos=0;pos!=t-1;pos++)
    { enr->auteurs[pos]=ouvrage[i];
      i++;
    }
    enr->auteurs[t-1]='\0';
    for(pos=0;pos!=4;pos++)
    { enr->anne_pub[pos]=ouvrage[i];
    i++;
   }
    enr->anne_pub[4]='\0';
    enr->dispo[0]=ouvrage[i];
    enr->dispo[1]='\0';


}


void affiche_enreg(enregistrement enr){
    printf("\nAffichage de enregistrement");
    printf("\nLa cle : %s",enr.cle);
    printf("\nL'auteur: %s",enr.auteurs);
    printf("\nLe titre: %s",enr.titre);
    printf("\nL'annee: %s",enr.anne_pub);
    printf("\nDisponibilite: %s",enr.dispo);
}
