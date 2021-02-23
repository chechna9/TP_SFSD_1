#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Fonctions.h"

int main(){
  /*  char ouvrage[b];
    remplir_ouvrage(ouvrage,1);
    enregistrement enr;
    remplir_enreg(ouvrage,&enr);
    affiche_enreg(enr);
    TOF F_tof;
    ouvrire_TOF(&F_tof,"testTof.bin",'n');
    TOF_Bloc buf;
    buf.tab[0]=enr;
    Ecrire_Dir_TOF(&F_tof,1,buf);
    fermer_TOF(&F_tof);
    ouvrire_TOF(&F_tof,"testTof.bin",'a');
    Lire_Dir_TOF(F_tof,1,&buf);
    enr=buf.tab[0];
    affiche_enreg(enr);
    fermer_TOF(&F_tof);

    */
    TOF F_per;



LOVbarC F;

Cree_Ouvrage(&F);
ouvrire_LOVbarC(&F,"ouvrages.bin",'a');
affichage_entete(F);
cree_fichier(F);/*
ouvrire_TOVC(&F_art,"Articles.bin",'a');
    ouvrire_LOVC(&F_mem,"memoires.bin",'a');
    ouvrire_TOVC(&F_liv,"livres.bin",'a');
printf("\n******************************** deb1**********\n");
    affichage_Memoire(F_mem);

    printf("\n******************************** dfin1**********\n");

    printf("\n******************************** deb2**********\n");
    affiche_livre(F_liv);
    printf("\n******************************** dfin2**********\n");
    printf("\n******************************** deb3**********\n");;

    affiche_livre(F_art);

    printf("\n******************************** dfin3**********\n");*/
    ouvrire_TOF(&F_per,"periodique.bin",'a');
    Affichage_TOF(F_per);

/*
ouvrire_LOVC(&F,"ouvrages.bin",'a');
affichage_bParB(F);
int bloc,pos,trouv;
recherche(&F,-1,&bloc,&pos,&trouv);
printf( "trouv = %d , pos = %d , bloc = %d",trouv,pos,bloc);
modif_dispo(&F,94,'1');
affichage_bParB(F);*/
return 0;
}
