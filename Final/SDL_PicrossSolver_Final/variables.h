#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

    SDL_Surface *kase = NULL;
    SDL_Surface *kase_noir = NULL;
    SDL_Surface *kase_blanc = NULL;
    SDL_Surface *fond = NULL;
    SDL_Surface *fond_newGrille = NULL;
    SDL_Surface *texte = NULL;
    SDL_Surface *ecran = NULL;
    SDL_Surface *texte_resolution=NULL;
    SDL_Surface *kase_ind = NULL;
    SDL_Surface *texte_newGrille = NULL;
    SDL_Surface *texte_enregistrement = NULL;
    SDL_Surface *texte_bouton_grille=NULL;
    SDL_Surface *texte_gauche=NULL;
    SDL_Surface *texte_droite=NULL;
    SDL_Surface *texte_haut=NULL;
    SDL_Surface *texte_bas=NULL;




    TTF_Font *police = NULL;
    TTF_Font *police_resolution = NULL;




    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Color couleurBlanc = {255,255,255};


    SDL_Rect position_texte_enregistrement;
    SDL_Rect position_bouton_grille;
    SDL_Rect position_grille;
    SDL_Rect position_bouton_resolution;
    SDL_Rect position_fond;
    SDL_Rect position_texte_newGrille;
    SDL_Rect position_texte_gauche;
    SDL_Rect position_texte_droite;
    SDL_Rect position_texte_haut;
    SDL_Rect position_texte_bas;


#endif // VARIABLES_H_INCLUDED
