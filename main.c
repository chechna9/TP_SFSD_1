#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define b 100
#include "Fonctions.h"


LOVbarC F;
int main()
{
    Buffer buf1,buf2,buf3;
    ouvrire_LOVbarC(&F,"texte.txt",'n');

    affichage_entete(F);

    ecrire_chaine(&F,1,"on est a bloc1");


    insertion_nonO(&F,"on est a bloc2");

    insertion_nonO(&F,"on est a bloc3");
    affichage_entete(F);
    affichage_bParB(F);
    Aff_Entete(&F,1,3);

    Fermer_LOVbarC(&F);


    return 0;
}
