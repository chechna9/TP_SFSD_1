#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define b 100

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

//=========Machine Abstraite===================================

void Aff_Entete(LOVbarC *F,int i,int val);

int entete(LOVbarC F,int i);

void Ecrire_Dir_LOVbarC(LOVbarC *F,int i,Buffer buf);
void Lire_Dir_LOVbarC(LOVbarC F,int i,Buffer *buf);

void ouvrire_LOVbarC(LOVbarC *F,char nom[],char mode);

void Fermer_LOVbarC(LOVbarC *F);
void Alloc_Bloc(LOVbarC *F);//en ajoute un bloc vide a la derniere position

//========debugging stuff=======================
void affichage_entete(LOVbarC F);

void affichage_bloc(LOVbarC F,int *i);//affichier un seul bloc
    ;

void affichage_bParB(LOVbarC F);//affichage bloc par bloc meme si il eté supprimer logiquement

//hadi ntesti biha
void ecrire_chaine(LOVbarC *F,int i,char s[b]);

void insertion_nonO(LOVbarC *F,char chaine[b]);


#endif // FONCTIONS_H_INCLUDED
