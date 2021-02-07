#include "Fonctions.h"
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

void Alloc_Bloc(LOVbarC *F){//en ajoute un bloc vide a la derniere position
    Buffer_liste buf;
    int dernier_Bloc = entete(*F,4);
    Lire_Dir_LOVbarC(*F,dernier_Bloc,&buf);//lecture du dernier bloc
    //modification du dernier bloc et l'entete
    buf.suiv=dernier_Bloc+1;
    Aff_Entete(F,4,dernier_Bloc+1);
    //sauvgarde le bloc
    Ecrire_Dir_LOVbarC(F,dernier_Bloc,buf);

    //initalisation du nouveau bloc
    buf.suiv=NULL;
    sprintf(buf.tab,"%s","");
    //sauvgarde du nouveau bloc
    Ecrire_Dir_LOVbarC(F,dernier_Bloc+1,buf);


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
void Ecrire_Dir_TOVC(TOVC *F,int i,Buffer buf){
    //printf("\nvaleur a ecrire %s",buf.chaine);
    fseek(F->fichier,sizeof(Entete_TOVC)+sizeof(Tbloc)*(i-1),SEEK_SET);//positionné sur le i eme bloc
    fwrite(&buf,sizeof(Tbloc),1,F->fichier);//ecriture

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
        Aff_Entete(F,1,0);
        Aff_Entete(F,2,0);
       //ecriture d'entete
        fwrite(&(F->entete),sizeof(Entete_TOVC),1,F->fichier);
       //nitialisation du Buffer_liste
        sprintf(buf.chaine,"");

        //Ecrire_Dir_TOVC(F,1,buf);
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

//=========================Fonctions du TP========================================
void cree_livre(LOVbarC F , TOVC * F2)
{ouvrire_TOVC(F2,"livres.bin",'N');
 ouvrire_LOVbarC(&F,"ouvrage.bin",'A');
    Buffer_liste buf;
    Buffer Tbuf;
    int i ;
    int nb=0;//nb de bloc de TOVC
    char type_taille[2];
     int k,indice_tab=0;
    k=entete(F,1);
    printf(" k = %d\n",k);
   int bloc=1,indice;
   F2->entete.nb_bloc=0;
  while (k!=NULL){  int i=0,taille_type;
            char chaine[200];
            char chaine2[Taille_Bloc];
            indice=0;
            strcpy(chaine2,"");
            Lire_Dir_LOVbarC(F,k,&buf);
            sprintf(chaine,"%s",buf.tab);
printf(" la chaine est %s\n",buf.tab);
    while(chaine[indice]!='\0')
    { for(i=0;i!=28;i++)//recuperer la clee le titre est les auteures
          {chaine2[indice_tab]=chaine[indice];
          indice++;
          indice_tab++;
            if(indice_tab==Taille_Bloc){chaine2[Taille_Bloc]='\0';

                sprintf(Tbuf.chaine,"%s",chaine2);
                  printf("  buf1= %s\n",Tbuf.chaine);
                 Ecrire_Dir_TOVC(F2,bloc,Tbuf);
                 printf(" ok 2");
                 nb++;
                 bloc++;
                 indice_tab=0;
            }
          }
          for(i=0;i!=2;i++)//lire la taille du bloc
          {type_taille[i]=chaine[indice];
          indice++;
          }
          type_taille[2]='\0';
          taille_type=atoi(type_taille);
          indice=indice+taille_type;
        while((chaine[indice]!='/')&&(chaine[indice]!='\0')) // recuperer la disponibilité l'anne de distribution  le code et le resumé
          {chaine2[indice_tab]=chaine[indice];
          indice++;
          indice_tab++;
            if(indice_tab==Taille_Bloc){chaine2[Taille_Bloc]='\0';
            sprintf(Tbuf.chaine,"%s",chaine2);
            Ecrire_Dir_TOVC(F2,bloc,Tbuf);
            printf("  buf2= %s\n",Tbuf.chaine);
           nb++;
            bloc++;
            indice_tab=0;
            }
          }
         if(chaine[indice]!='\0'){indice++;
         if(indice_tab==Taille_Bloc){
                    printf("  buf3= %s\n",Tbuf.chaine);
                        bloc++;
                    indice_tab=0;
                    strcpy(Tbuf.chaine,"/");
                    indice_tab++;
                    Ecrire_Dir_TOVC(F2,bloc,Tbuf);
                    nb++;
                }
                else{chaine2[indice_tab]='/' ;
                indice_tab++;}

 }
        }
 if(indice_tab==Taille_Bloc){
                    printf("  buf3= %s\n",Tbuf.chaine);
                        bloc++;
                    indice_tab=0;
                    strcpy(Tbuf.chaine,"/");
                    indice_tab++;
                    Ecrire_Dir_TOVC(F2,bloc,Tbuf);
                   nb++;
                }
                chaine2[indice_tab]='\0';
                    sprintf(Tbuf.chaine,"%s",chaine2);
                    printf("  buf4= %s\n",Tbuf.chaine);
                     Ecrire_Dir_TOVC(F2,bloc,Tbuf);
                     nb++;



    k=buf.suiv;
 }
 F2->entete.nb_bloc=nb;
 F2->entete.dernier_pos=indice_tab;

printf(" le nb de bloc est************  %d\n",nb);
 //Fermer_TOVC(F2);


}
/*void affichage_TOVC(TOVC F)
{Buffer Tbuf;

int nb_bloc =entete_TOVC(F,1);

printf(" entete 1 = %d\n",nb_bloc);
int i;
  for(i=1;i!=nb_bloc+1;i++){Lire_Dir_TOVC(F,i,&Tbuf);
  printf(" le contenu du beffer %d est : %s\n",i,buf.chaine);
    }
}*/


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
    char chaine[200];
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
         for(i=0;i!=t;i++)
         {chaine2[i]=chaine[indice];indice++;
        }
         chaine2[t]='\0';
         printf(" la titre est  est : %s\n",chaine2);
           for(i=0;i!=t;i++)
         {chaine2[i]=chaine[indice];
          indice++;}

         chaine2[t]='\0';
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
    int i;
    i=entete(F,1);
printf("\n***********************************************DEBUT AFFICHAGE**********************************************\n");
    while (i!=NULL){
        affichage_bloc(F,&i);
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
    Alloc_Bloc(F);
    ecrire_chaine(F,entete(*F,1),chaine);


}

void aleat_chaine(char *nom[50],int taille)
{ int i ;
  char no[50]={0};
  strcpy(nom,"");

    char nomm[26]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
       for (i=0  ; i != taille ;i++ )
       {
           sprintf(no,"%s%c",no,nomm[rand()%26]);

       }
       nom[taille]='\0';
       sprintf(nom,"%s",no);

}
void aleat_resum(char *nom[50],int min , int max)
{ int i ;
  char no[50]={0};
  strcpy(nom,"");
int a;
a=(int)rand()%(max-min)+min;
    char nomm[26]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
       for (i=0  ; i != a ;i++ )
       {
           sprintf(no,"%s%c",no,nomm[rand()%26]);

       }
       nom[a]='\0';
       sprintf(nom,"%s",no);

}
void aleat_type(char *chaine[24])
{int n ;
char type[24];
   n=rand()%4;
   switch(n)
   {
       case 0  :
           strcpy(type,"13Texte imprime");// avec la taille du  type au debut
           break;
        case 1  :
           strcpy(type,"21Document electronique");
           break;

        case 2  :
           strcpy(type,"07Article");
           break;
        case 3  :
           strcpy(type,"10Periodique");
           break;
   }
   sprintf(chaine,"%s",type);
}
void aleat_anne(char *chaine[4])
{int n ;
  n=rand()%72+1950;
  sprintf(chaine,"%d",n);
  printf("chaine =%s\n",chaine);

}
void int_to_char(int num , char * chain[4])
 {char chaine[10]="0123456789";
 char chaine2[4]="0000";
 int i ,n;
 for(i=3;i!=-1;i--)
 {n=num%10;
 if(n!=0){chaine2[i]=chaine[n];}
num=num/10;
}
chaine2[4]='\0';
 sprintf(chain,"%s",chaine2);
}
void aleat_disponible(char *dispo[1])
{
    int a;
    a=(int) rand()%2;
     sprintf(dispo,"%d",a);
}

//char Type [4][25]={"Texte imprime","Document electronique","Article","Periodique"};
void Cree_Ouvrage(LOVbarC *F){
    //ouvrire_LOVbarC
   ouvrire_LOVbarC(F,"ouvrage.bin",'n');
   int n,i ;
   printf(" entrer le nombre d'ouvrage que vous voullez entrer : ");
   scanf("%d",&n);
   if(n==0){Aff_Entete(F,1,NULL);}
   else{Aff_Entete(F,1,1);}
        Aff_Entete(F,2,0);
        Aff_Entete(F,3,0);
        Aff_Entete(F,4,n);
      Buffer_liste buf;
       char *type[50];
       char *cle[4];
       char *titre[50];
       char *disponible[1];
       char *annee[4];
       char *auteurs[50];
       char *resume[50];
       char *ouvrage[200];
       char *bloc_avant[200];
       char *chaine2[200];
 // on prend que la cote est au meme temp la cle
  int  taille=0 ;
  int suiv=1;
      strcpy(bloc_avant,"");

   for(i=1;i!=n+1;i++)
   {aleat_anne(annee);
    int_to_char(i,cle);
    aleat_chaine(titre,t);
    aleat_type(type);
    aleat_disponible(disponible);
    aleat_chaine(auteurs,t);
    aleat_resum(resume,10,15);
 sprintf(ouvrage,"%s%s%s%s%s%s%s%s",cle,titre,auteurs,type,annee,disponible,cle,resume);
       taille+=strlen(ouvrage)+strlen(bloc_avant);
    if((taille+1>=b)||(i==n)){
           buf.suiv=suiv+1;


      if(taille+1<b){
            buf.suiv=NULL;
            sprintf(chaine2 ,"%s",bloc_avant);
         if(strcmp(chaine2,"")==0){
                sprintf(bloc_avant,"%s%s",chaine2,ouvrage);
                }
         else{
             sprintf(bloc_avant,"%s/%s",chaine2,ouvrage);
            }
        }

       sprintf(buf.tab,"%s",bloc_avant);
       Ecrire_Dir_LOVbarC(F,suiv,buf);
       suiv++;
        taille=strlen(ouvrage);   strcpy(bloc_avant,ouvrage);
      }
    else{sprintf(chaine2 ,"%s",bloc_avant);
      if(strcmp(chaine2,"")==0){  sprintf(bloc_avant,"%s%s",chaine2,ouvrage);}
       else{sprintf(bloc_avant,"%s/%s",chaine2,ouvrage);}
    }

if((i==n)){sprintf(buf.tab,"%s",bloc_avant);
buf.suiv=NULL;
       Ecrire_Dir_LOVbarC(F,suiv,buf);

}


  }



Fermer_LOVbarC(F);
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
                /*if (!saturation && i==n-1){//pour traiter le cas du dernier ouvrage dans un nouveau bloc
                    Alloc_Bloc(F);
                    Ecrire_Dir_LOVbarC(F,bloc,buf);
                }*/
            }
        }
    }
    Fermer_LOVbarC(F);
}
void recherche (LOVbarC *F ,int clee, int *bloc, int *pos , int *trouv)
{ int i,k;
    i=entete(*F,1);
    *trouv=0;
    Buffer_liste buf;
    int stop=0;
    int indice =0;
     char chaine[200];
     char cle2[4];
    while (((i!=NULL)&&(*trouv==0))&&(stop==0)){
    Lire_Dir_LOVbarC(*F,i,&buf);
    sprintf(chaine,"%s",buf.tab);
     *bloc=i;
      indice=0;
     *pos=indice;
        while(((chaine[indice]!='\0')&&(*trouv==0))&&(stop==0))
         {
         for(k=0;k!=4;k++)
             {cle2[k]=chaine[indice+k];}
             cle2[4]='\0';
              if(atoi(cle2)==clee)
                  {*trouv=1;
                   break; }
              if(atoi(cle2)>clee){printf(" stop\n");
                    stop = 1;break;}
                    indice=indice+4;
              while((chaine[indice]!='/')&&(chaine[indice]!='\0'))
                       {indice++;
                       }

              if(chaine[indice]=='/'){indice++;}
              *pos=indice;
         }

      i=buf.suiv;
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
void modif_dispo(LOVbarC *F ,int clee , char *nv_etat[1]) // 1 pour disponible et 0 pour indisponible
{int pos,bloc,trouv;
int taille_type;
char type_taille[2];
 recherche(F,clee,&bloc,&pos,&trouv);
 if(trouv==1)
 {int i;
     Buffer_liste buf;
     Lire_Dir_LOVbarC(*F,bloc,&buf);
   pos=pos+4+(2*t);
   for(i=0;i!=2;i++)
   {type_taille[i]=buf.tab[pos+i];}
   type_taille[2]='\0';
   taille_type=atoi(type_taille);
   pos=pos+2+taille_type+4;
   buf.tab[pos]=nv_etat;
   Ecrire_Dir_LOVbarC(F,bloc,buf);
   }

 else
    {printf(" desole ce livre n'existe pas merci d'entrer une clee qui existe!\n"); }

}
