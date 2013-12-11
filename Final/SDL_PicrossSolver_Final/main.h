#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

int saisie_texte(SDL_Surface* , SDL_Rect, TTF_Font* , SDL_Color, int , char *, int , int);

void newGrille(picross);

void pause(picross);

void choix(picross);

void ouvrirGrille();

void surfaces();

void freesurfaces();

void affiche_indices(picross);

void affiche_grille(picross);

void maine(int);

#endif // MAIN_H_INCLUDED
