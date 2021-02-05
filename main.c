#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define b 100
#include "Fonctions.h"
char *alea_chaine()//on genere des nom de 3 a 19 caracteres
{
    char chaine[20];
    int a;
    a=rand()%16+3;

    char alphabet[26]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;
    for ( i=0  ; i <= a ;i++ )
    {
       sprintf(chaine,"%s%c",chaine,alphabet[rand()%26]);

    }
    chaine[i]='\0';
    return chaine;

}
char Type [4][25]={"Texte imprime","Document electronique","Article","Periodique"};
LOVbarC *Cree_Ouvrage(int n){

}

LOVbarC F;
int main()
{
    char *s=alea_chaine();
    printf("%s",s);


    return 0;
}
