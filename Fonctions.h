#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define b 400
#define t 12
#define Taille_Bloc 100
//=======LOVbarC=================================================================
//=======Declarations des structures===========================================
typedef struct Lbloc{
    char tab[b];//tableau de caractere
    int suiv;//numero du bloc suivant
} Lbloc;

typedef struct Lbloc Buffer_liste;//declaration du Buffer_liste

typedef struct Entete{
    int tete;//adresse du premier bloc
    int nbInsert;//nombre globale des caracteres inserer
    int nbSupp;//nombre globale des caractere supprimer
    int nb_bloc;//nombre de bloc
}Entete;


typedef struct Fichier_LOVbarC {
    Entete entete;
    FILE *file;
}LOVbarC;
//=========Machine Abstraite TOVC============================================================================
//=================les structures====================================================/
typedef struct Tbloc      //la structure de bloc
{
    char chaine[Taille_Bloc];   //il s'agit d'une chaine de caractères
} Tbloc;


typedef struct  ouvrage        //structure où on récupère aussi les différents champs d'un enregistrement
{
    char clee [4];            //le code de livre
    char titre [20] ;  //l'auteur_le titre_la maison d'édition
    char auteurs [20];
   char annee [4];
   char dispo[1];
   char code[4];
   char resume [50];
} ouvrage;

typedef struct Tbloc Buffer;  //le buffer où on récupère on bloc

typedef struct Entete_TOVC
{
    int nb_bloc;//nombre du bloc inserer
    int dernier_pos;//dernier position dans le dernier bloc

} Entete_TOVC;

typedef struct TOVC     //structure de fichier
{
    FILE * fichier;             //poiteur vers le fichier
    Entete_TOVC entete;       //l'entete de fichier
} TOVC;
//===========machine abstraite LOVbarC==============================
void Aff_Entete(LOVbarC *F,int i,int val);

int entete(LOVbarC F,int i);

void Ecrire_Dir_LOVbarC(LOVbarC *F,int i,Buffer_liste buf);

void Lire_Dir_LOVbarC(LOVbarC F,int i,Buffer_liste *buf);
void ouvrire_LOVbarC(LOVbarC *F,char nom[20],char mode);

void Fermer_LOVbarC(LOVbarC *F);
void Alloc_Bloc(LOVbarC *F);
//=============Macihne abstraite TOVC================================
void Aff_Entete_TOVC( TOVC *F,int i,int val);
int entete_TOVC(TOVC F,int i);
void Ecrire_Dir_TOVC(TOVC *F,int i,Buffer buf);
void Lire_Dir_TOVC(TOVC F,int i,Buffer *buf);
void ouvrire_TOVC(TOVC *F,char nom[20],char mode);
void Fermer_TOVC(TOVC *F);
void Alloc_Bloc_TOVC(TOVC *F);
//==============Fonctions du TP=======================================
void cree_livre(LOVbarC F , TOVC * F2);
void affichage_TOVC(TOVC F);

void majuscule(char nom[20]);
//========debugging stuff=======================
void affichage_entete(LOVbarC F);
void affichage_bloc(LOVbarC F,int *k);
void affichage_bParB(LOVbarC F);

//hadi ntesti biha
void ecrire_chaine(LOVbarC *F,int i,char s[b]);
void insertion_nonO(LOVbarC *F,char chaine[b]);
void aleat_chaine(char *nom[50],int taille);
void aleat_resum(char *nom[50],int min , int max);
void aleat_type(char *chaine[24]);
void aleat_anne(char chaine[5]);
void int_to_char(int num , char chain[5]);
void aleat_disponible(char *dispo[2]);

//char Type [4][25]={"Texte imprime","Document electronique","Article","Periodique"};
void alea_chaine(char chaine[],int max,int min); //sup ou egale a min et strictement inf a max

void remplir_ouvrage(char ouvrage[b],int cle);
void Cree_Ouvrage(LOVbarC *F);
void recherche (LOVbarC *F ,int clee, int *bloc, int *pos , int *trouv);
void insertion(LOVbarC *F );
void modif_dispo(LOVbarC *F ,int clee , char *nv_etat[1]);
#endif // FONCTIONS_H_INCLUDED
