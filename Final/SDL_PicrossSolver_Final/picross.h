#ifndef RESOLUTION_H_INCLUDED
#define RESOLUTION_H_INCLUDED

#include "structure.h"

//Format commun int fct(ligne, liste ind, int taille, *liste);

int bord_box_blanc(ligne L, liste ind_ligne, int longueur, liste *L_modif);         //fonction qui permet d'étaler le premier indice s'il y a une case noire au début
int minimal_box_blanc(ligne L, liste ind_ligne, int longueur, liste *L_modif);      //fonction qui permet de remplir les intervalles entre deux cases blanches par des cases blanches s'il n'y a pas la place pour un bloc de case noire
int box_blanc(ligne m_ligne, liste ind_ligne, int longueur_ligne, liste *L_modif);  //fonction qui permet si toutes les cases noires sont remplies de remplacer les cases grises restantes par des cases blanches

//Case MinMax
int derniereCaseGauche(int, int, ligne, int);   //fonction qui permet de trouver la position la plus a gauche de la derniere case d'un bloc donne
int premiereCaseDroite(int, int, ligne);        //fonction qui permet de trouver la position la plus a droite de la premiere case d'un bloc donne
int coloriage(liste, liste, ligne, liste*);     //fonction qui noirci les cases en communs entre deux listes de positions donnees
int caseMinMax(liste, ligne, int, liste*);      //fonction qui noirci les cases en communs entre les deux positions extremes de chaque bloc d'une ligne


#endif
