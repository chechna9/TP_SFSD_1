#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define b 400
#define t 12//taille de l auteur et titre - 1
#define Taille_Bloc 100
#define Taille_Bloc_TOF 10

//======= LOVC ==================================================================
typedef struct LOVCbloc{
    char tab[b];//tableau de caractere
    int suiv;//numero du bloc suivant
} LOVCbloc;
typedef struct LOVCbloc Buffer_LOVC;//declaration du Buffer_liste
typedef struct Entete_LOVC{
    int tete;//adresse du premier bloc
    int nbInsert;//nombre globale des caracteres inserer
    int nbSupp;//nombre globale des caractere supprimer
    int nb_bloc;//nombre de bloc
}Entete_LOVC;
typedef struct Fichier_LOVC {
    Entete_LOVC entete;
    FILE *file;
}LOVC;
//=============TOF===============================================================
typedef struct enregistrement  {
char cle[5];
char titre[t];
char auteurs[t];
char anne_pub[5];
char dispo[2];
} enregistrement ;
typedef struct TOF_Bloc{
enregistrement tab[Taille_Bloc_TOF];
int nb_enreg_inserer;
}TOF_Bloc;
typedef struct Entete_TOF{
int nb_bloc;
int dernier_pos;
} Entete_TOF;

typedef struct Fichier_TOF {
    Entete_TOF entete;
    FILE *fichier;
}TOF;
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
void Alloc_Bloc(LOVbarC *F,int dernier_bloc);
//=============Macihne abstraite TOVC================================
void Aff_Entete_TOVC( TOVC *F,int i,int val);
int entete_TOVC(TOVC F,int i);
void Ecrire_Dir_TOVC(TOVC *F,int i,Buffer *buf);
void Lire_Dir_TOVC(TOVC F,int i,Buffer *buf);
void ouvrire_TOVC(TOVC *F,char nom[20],char mode);
void Fermer_TOVC(TOVC *F);
void Alloc_Bloc_TOVC(TOVC *F);
///==================== Machine abstraite TOF=================================================================
void fermer_TOF(TOF *F);
void Aff_Entete_TOF(TOF *F,int i,int val);
int entete_TOF(TOF F,int i);
void Ecrire_Dir_TOF(TOF *F,int i,TOF_Bloc buf);
void Lire_Dir_TOF(TOF F,int i,TOF_Bloc *buf);
void ouvrire_TOF(TOF *F,char nom[20],char mode);
void Alloc_bloc_TOF(TOF *F );
///===================================================LOVC================================================================
void Aff_Entete_LOVC(LOVC *F,int i,int val);
int entete_LOVC(LOVC F,int i);
void Ecrire_Dir_LOVC(LOVC *F,int i,Buffer_LOVC buf);

void Lire_Dir_LOVC(LOVC F,int i,Buffer_LOVC *buf);
void ouvrire_LOVC(LOVC *F,char nom[20],char mode);

void Fermer_LOVC(LOVC *F);
void Alloc_Bloc_LOVC(LOVC *F,int dernier_Bloc);
void creer_memoire(LOVbarC Fo);

void affichage_Memoire(LOVC F);

//==============Fonctions du TP=======================================
void del_type(char ouvrage[b]);//fonction qui supprime le type
void Cree_Livre(LOVbarC Fo);//Fo: fichier ouvrage

void affichage_TOVC(TOVC F);

void majuscule(char nom[20]);
//========debugging stuff=======================
void affichage_entete(LOVbarC F);
void affichage_bloc(LOVbarC F,int *k);
void affichage_bParB(LOVbarC F);

//hadi ntesti biha
void ecrire_chaine(LOVbarC *F,int i,char s[b]);
void insertion_nonO(LOVbarC *F,char chaine[b]);
void aleat_chaine(char chaine[50],int taille);
void aleat_resum(char chaine[50],int min , int max);
void aleat_type(char *chaine[24]);
void aleat_anne(char chaine[5]);
void int_to_char(int num , char chain[5]);
void aleat_disponible(char *dispo[2]);

int detectType(char ouvrage[b]);

void alea_chaine(char chaine[],int max,int min); //sup ou egale a min et strictement inf a max

void remplir_ouvrage(char ouvrage[b],int cle);
void Cree_Ouvrage(LOVbarC *F);
void recherche (LOVbarC *F ,int clee, int *bloc, int *pos , int *trouv);
void insertion(LOVbarC *F );
void modif_dispo(LOVbarC *F ,int clee , char nv_etat);
///=================================================================
void del_type_cote(char ouvrage[b]);
void Cree_Article(LOVbarC Fo);
void affichage_bloc2(LOVbarC F,int *i);
void affichage_bparb2(LOVbarC F);
void affiche_livre(TOVC F);
void recuperer_chaine(LOVbarC *F,int n, int *i, int *j, char chaine[],Buffer_liste *buf);
void remplir_livre(TOVC *F , int *bloc , int *pos , char ouvrage[] ,Buffer * buf );
void remplir_memoire(LOVC *F ,char ouvragee[b] ,int * bloc ,int *pos , Buffer_LOVC *buf );
void remplir_articl(TOVC *F , int *bloc , int * pos , char ouvrage[] , Tbloc *buf );
void remplir_periodique(TOF *F , int *bloc ,int *pos,TOF_Bloc *buf ,enregistrement enrg);
void cree_fichier(LOVbarC F);
void Affichage_TOF(TOF F);
void remplir_enreg(char ouvrage[b],enregistrement *enr);
void affiche_enreg(enregistrement enr);
#endif // FONCTIONS_H_INCLUDED
