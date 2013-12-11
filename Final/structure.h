#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

#include "liste.h"

//STRUCTURES

//Case étant réservé en C, nous avons choisi le type box pour représenter le contenu d'une case de la grille de picross.
//Noir : la case est coloriée
//Blanc : la case est vide
//Gris : la case peut être soit blanche, soit noire.

typedef enum box box ;
enum box
{
    noir, blanc, gris
};

//La majorité des fonctions prennent en paramètre une ligne de la grille du picross.

typedef box *ligne;

//ind_lignes et ind_colonnes sont des tableaux de listes dans lesquelles sont stockées les indices.

typedef struct picross picross ;
struct picross
{
    int transpose; //0 normal 1 transpose
    int nb_lignes;
    int nb_colonnes;

    liste *ind_lignes;

    liste *ind_colonnes;

    ligne *grille;
};

//Structure chargée d'envoyées les lignes aux algorithmes de résolution.
//Les lignes les plus iteressantes auront une priorité plus élevée et seront traitées en premier.
typedef struct JobList{

int *prioriteLigne; //initialisation par défaut de toutes les cases à 1.
int *prioriteColonne; //idem


int nb_lignes;
int nb_colonnes;

}JobList;

//Structure utilisée dans la fonction prioMax pour renvoyer deux entiers.

typedef struct prioEtInd{
    int priorite;
    int indice;

}prioEtInd;

//FONCTIONS

//LIGNES
int ligneFinie(ligne, int);                                                 //fonction qui verifie si une ligne est finie ou non
int ligneSolution(ligne m_ligne, liste ind_lignes, int longueur_ligne);     //fonction qui verifie si une ligne est solution ou non
int degreLiberte(liste indices, int tailleLigne);                           //fonction qui calcule le degre de liberte d'une ligne

//GRILLE
picross Initialisation(char*);                   //fonction qui initialise une structure picross
void afficherGrille(picross);                    //fonction qui affiche la grille d'un picross
picross transposer(picross picross1);            //fonction qui transpose un picross
int verification(picross solution);              //fonction qui veriie si une grille est solution d'un picross ou non
picross copierPicross(picross source,char*);     //fonction qui copie un picross
int picrossFini(picross pic);                    //fonction qui verifie si une grille est fini ou non

//JOBLIST
JobList initJobList(picross pic1);                        //fonction qui initialise une JobList d'un picross
void prioriteup(int *prio, liste *indices, int nb_elem);  //fonction qui augment la priorite de certaines lignes suivant leurs elements
prioEtInd prioMax(int *prio, int taille);                 //fonction qui renvoie le numero de la ligne qui a la priorite maximale
void majJobList(int *prio, liste indices);                //fonction qui met a jour les priorites des lignes suivant la liste indices

//RESOLUTION
int premCaseGrise(int *lig, int *col, picross pic);       //fonction qui recherche une case grise d'un picross donne
int resolution(JobList joblist1, picross picross1);       //fonction qui applique les regles de resolution suivant les priorites des lignes
int generateurHypo(picross, picross*, int*,char*);        //fonction qui genere des hypotheses pour resoudre un picross incomplet
void resolveur(char*);                                    //fonction qui resout completement un picross


#endif // STRUCTURE_H_INCLUDED
