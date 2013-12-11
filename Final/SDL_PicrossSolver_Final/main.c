#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "picross.h"
#include "liste.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "variables.h"



int saisie_texte(SDL_Surface *ecran, SDL_Rect position_zone, TTF_Font *police, SDL_Color couleur_texte, int long_max, char *saisie,int choix, int numLiCol) /*On envoie l'écran, la position de la zone de saisie, la police ( faites attentions car certaines polices ne contiennent pas tous les caractères, la couleur du texte, la longueur max de la saisie(pour éviter les dépassement de mémoire) et enfin le tableau de char pour recevoir la saisie)*/
{
    SDL_Surface *texte=NULL;
    SDL_Surface *rappel=NULL;
    SDL_Rect position_rappel;
    TTF_Font *police_grille = NULL;
    police_grille = TTF_OpenFont("angelina.ttf", 32);
    SDL_Event event;
    int continuer = 1;
    int i=0;

    texte = TTF_RenderText_Blended(police, saisie, couleur_texte);
    saisie[0]='\0';
    SDL_EnableUNICODE(1);
    SDL_EnableKeyRepeat(120, 120);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_KEYDOWN:
                if (i>long_max)
                    continuer=0;
                else if(event.key.keysym.sym==8 && i>0) // pour retour arrière
                {
                    i--;
                    saisie[i]=32;
                }
                else if (event.key.keysym.sym>=32 && event.key.keysym.sym<=126) //Touches ASCII de 32 à 126
                {
                    saisie[i]=(char)event.key.keysym.unicode;
                    i++;
                    saisie[i]='\0';
                }
                else if (event.key.keysym.sym==SDLK_RETURN || event.key.keysym.sym==SDLK_KP_ENTER) /* pour la touche Entrée => fin de la saisie */
                {
                    saisie[i]='\0';
                    continuer=0;
                }
                else if (event.key.keysym.sym==SDLK_KP0 ) /*Saisie de clavier numérique*/
                {
                    saisie[i]='0';
                    i++;
                    saisie[i]='\0';
                }
                else if (event.key.keysym.sym==SDLK_KP1 )
                {
                    saisie[i]='1';
                    i++;
                    saisie[i]='\0';
                }
                else if (event.key.keysym.sym==SDLK_KP2 )
                {
                    saisie[i]='2';
                    i++;
                    saisie[i]='\0';
                }
                else if (event.key.keysym.sym==SDLK_KP3 )
                {
                    saisie[i]='3';
                    i++;
                    saisie[i]='\0';
                }
                else if (event.key.keysym.sym==SDLK_KP4 )
                {
                    saisie[i]='4';
                    i++;
                    saisie[i]='\0';
                }
                else if (event.key.keysym.sym==SDLK_KP5 )
                {
                    saisie[i]='5';
                    i++;
                    saisie[i]='\0';
                }
                else if (event.key.keysym.sym==SDLK_KP6 )
                {
                    saisie[i]='6';
                    i++;
                    saisie[i]='\0';
                }
                else if (event.key.keysym.sym==SDLK_KP7 )
                {
                    saisie[i]='7';
                    i++;
                    saisie[i]='\0';
                }
                else if (event.key.keysym.sym==SDLK_KP8 )
                {
                    saisie[i]='8';
                    i++;
                    saisie[i]='\0';
                }
                else if (event.key.keysym.sym==SDLK_KP9 )
                {
                    saisie[i]='9';
                    i++;
                    saisie[i]='\0';
                }
                else if (event.key.keysym.sym==SDLK_KP_PERIOD )
                {
                    saisie[i]='.';
                    i++;
                    saisie[i]='\0';
                }
                else if (event.key.keysym.sym==SDLK_KP_DIVIDE )
                {
                    saisie[i]='/';
                    i++;
                    saisie[i]='\0';
                }
                else if (event.key.keysym.sym==SDLK_KP_MINUS)
                {
                    saisie[i]= '-' ;
                    i++;
                    saisie[i]='\0';
                }
                else if (event.key.keysym.sym==SDLK_KP_PLUS)
                {
                    saisie[i]= '+' ;
                    i++;
                    saisie[i]='\0';
                }
                else if (event.key.keysym.sym==SDLK_KP_MULTIPLY)
                {
                    saisie[i]= '*' ;
                    i++;
                    saisie[i]='\0';
                }
                else if (event.key.keysym.sym==SDLK_KP_EQUALS)
                {
                    saisie[i]= '=' ;
                    i++;
                    saisie[i]='\0';
                }

            break;

        }

        position_texte_newGrille.x=0;
        position_texte_newGrille.y=0;
        position_rappel.x=50;
        position_rappel.y=50;

        SDL_BlitSurface(fond_newGrille, NULL, ecran, &position_fond);

        if (numLiCol==1) { rappel= TTF_RenderText_Blended(police_grille, "         Ligne 1 : ",couleurBlanc);SDL_BlitSurface(rappel,NULL,ecran, &position_rappel); }
        if (numLiCol==2) { rappel= TTF_RenderText_Blended(police_grille, "         Ligne 2 : ",couleurBlanc);SDL_BlitSurface(rappel,NULL,ecran, &position_rappel); }
        if (numLiCol==3) { rappel= TTF_RenderText_Blended(police_grille, "         Ligne 3 : ",couleurBlanc);SDL_BlitSurface(rappel,NULL,ecran, &position_rappel); }
        if (numLiCol==4) { rappel= TTF_RenderText_Blended(police_grille, "         Ligne 4 : ",couleurBlanc);SDL_BlitSurface(rappel,NULL,ecran, &position_rappel); }
        if (numLiCol==5) { rappel= TTF_RenderText_Blended(police_grille, "         Ligne 5 : ",couleurBlanc);SDL_BlitSurface(rappel,NULL,ecran, &position_rappel); }
        if (numLiCol==6) { rappel= TTF_RenderText_Blended(police_grille, "         Ligne 6 : ",couleurBlanc);SDL_BlitSurface(rappel,NULL,ecran, &position_rappel); }
        if (numLiCol==7) { rappel= TTF_RenderText_Blended(police_grille, "         Ligne 7 : ",couleurBlanc);SDL_BlitSurface(rappel,NULL,ecran, &position_rappel); }
        if (numLiCol==8) { rappel= TTF_RenderText_Blended(police_grille, "         Ligne 8 : ",couleurBlanc);SDL_BlitSurface(rappel,NULL,ecran, &position_rappel); }
        if (numLiCol==9) { rappel= TTF_RenderText_Blended(police_grille, "         Ligne 9 : ",couleurBlanc); SDL_BlitSurface(rappel,NULL,ecran, &position_rappel);}
        if (numLiCol==10) { rappel= TTF_RenderText_Blended(police_grille, "       Ligne 10 : ",couleurBlanc);SDL_BlitSurface(rappel,NULL,ecran, &position_rappel); }
        if (numLiCol==11) { rappel= TTF_RenderText_Blended(police_grille, "       Ligne 11 : ",couleurBlanc);SDL_BlitSurface(rappel,NULL,ecran, &position_rappel); }
        if (numLiCol==12) { rappel= TTF_RenderText_Blended(police_grille, "       Ligne 12 : ",couleurBlanc);SDL_BlitSurface(rappel,NULL,ecran, &position_rappel); }
        if (numLiCol==13) { rappel= TTF_RenderText_Blended(police_grille, "       Ligne 13 : ",couleurBlanc);SDL_BlitSurface(rappel,NULL,ecran, &position_rappel); }




        if (choix==0)
        {

        texte_newGrille= TTF_RenderText_Blended(police_grille, "    Entrez le nombre de lignes, le nombre de colonnes :",couleurBlanc);

        SDL_BlitSurface(texte_newGrille,NULL,ecran, &position_texte_newGrille);
        }

        if (choix==1)
        {
            texte_newGrille= TTF_RenderText_Blended(police_grille, " Entrez les indices de la ligne separes par des espaces et finissez par -1 :",couleurBlanc);
            SDL_BlitSurface(texte_newGrille,NULL,ecran, &position_texte_newGrille);
        }
        if (choix==2)
        {
            texte_newGrille= TTF_RenderText_Blended(police_grille, " Entrez les indices de la colonne separes par des espaces et finissez par -1 :",couleurBlanc);
            SDL_BlitSurface(texte_newGrille,NULL,ecran, &position_texte_newGrille);
        }



        texte=TTF_RenderText_Blended(police_grille, saisie, couleur_texte);
        SDL_BlitSurface(texte, NULL, ecran, &position_zone); /* Blit du texte par-dessus */
        SDL_Flip(ecran);


    }

    SDL_FreeSurface(texte);

    return 0;
}

void newGrille(picross picross1)
{
	SDL_BlitSurface(fond_newGrille, NULL, ecran, &position_fond);

	position_texte_enregistrement.x= 800/2;
	position_texte_enregistrement.y= 600/2;
	int nb_li;
	int nb_col;

	char *sais[10];

	FILE* fichier = NULL;
	int valeur;int i;

    fichier = fopen("Initialisation.txt", "r+");

    if (fichier != NULL)
    {

        saisie_texte(ecran,position_texte_enregistrement,police_resolution,couleurBlanc,10,sais,0,i);
        fprintf(fichier, "%s \n", sais);
        fseek(fichier, 0, SEEK_SET);
        fscanf(fichier, "%d %d \n",&nb_li, &nb_col);

        for (i=0; i<nb_li;i++)
        {
            saisie_texte(ecran,position_texte_enregistrement,police_resolution,couleurBlanc,10,sais,1,i+1);
            fprintf(fichier, "%s \n", sais);
        }

        for (i=0; i<nb_col;i++)
        {
            saisie_texte(ecran,position_texte_enregistrement,police_resolution,couleurBlanc,10,sais,2,i+1);
            fprintf(fichier, "%s \n", sais);
        }

        fclose(fichier);
    }

    maine(0);
    SDL_Flip(ecran);

}

void pause(picross picross1)
{   /* Crée une boucle qui ne s'arête que quand on appuie sur échape ou qu'on clique sur la croix */
    int continuer = 1;
    JobList jobl1;
    jobl1=initJobList(picross1);
    SDL_Event event;



    while (continuer)
    {

        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;

                    case SDLK_BACKSPACE:
                       choix(picross1);

                        break;
                    case SDLK_SPACE:



    resolveur(picross1);

    position_grille.x = (800/2) - ((picross1.nb_lignes*(34))/2);
    position_grille.y = (600/2) - ((picross1.nb_colonnes*(34))/2); // ATTENTION MODIFIER LA RESOLUTION, A CHAQUE ESPACE, TRANSPOSER EST LANCEE

    affiche_grille(picross1);
    affiche_indices(picross1);
    SDL_Flip(ecran);

    //if(check==1) printf("Erreur lors de la resolution");

                        break;
                } break;

        }
    }
}

void choix(picross picross1)
{   /* Crée une boucle qui ne s'arête que quand on appuie sur échape ou qu'on clique sur la croix */
    position_texte_gauche.x=50;
    position_texte_gauche.y=600/2-50;
    position_texte_droite.x=800/2;
    position_texte_droite.y=600/2+50;

    SDL_BlitSurface(fond_newGrille, NULL, ecran, &position_fond);
    texte_newGrille= TTF_RenderText_Blended(police_resolution, " Vous voulez :  ",couleurBlanc);
    texte_gauche= TTF_RenderText_Blended(police_resolution, "Ouvrir une grille sauvegarder, appuyez Fleche Gauche.",couleurBlanc);
    texte_droite= TTF_RenderText_Blended(police_resolution, "Creer une nouvelle grille, Fleche Droite.",couleurBlanc);

    SDL_BlitSurface(texte_newGrille,NULL,ecran, &position_texte_newGrille);
    SDL_BlitSurface(texte_gauche,NULL,ecran, &position_texte_gauche);
    SDL_BlitSurface(texte_droite,NULL,ecran, &position_texte_droite);


    SDL_Flip(ecran);
    int continuer = 1;
    JobList jobl1;
    jobl1=initJobList(picross1);
    SDL_Event event;



    while (continuer)
    {

        SDL_WaitEvent(&event);
        switch(event.type)
        {


            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {




                       case SDLK_LEFT:
                       ouvrirGrille();
                       break;

                       case SDLK_RIGHT:
                       newGrille(picross1);
                } break;

        }
    }
}

void choix_grille()
{   /* Crée une boucle qui ne s'arête que quand on appuie sur échape ou qu'on clique sur la croix */
    position_texte_haut.x=800/2-40;
    position_texte_haut.y=600/2-100;
    position_texte_bas.x=800/2-40;
    position_texte_bas.y=600/2+100;

    SDL_BlitSurface(fond_newGrille, NULL, ecran, &position_fond);

    texte_haut= TTF_RenderText_Blended(police_resolution, "Grille 5 5 ",couleurBlanc);
    texte_bas= TTF_RenderText_Blended(police_resolution, "Grille 10 10",couleurBlanc);


    SDL_BlitSurface(texte_haut,NULL,ecran, &position_texte_haut);
    SDL_BlitSurface(texte_bas,NULL,ecran, &position_texte_bas);


    SDL_Flip(ecran);
    int continuer = 1;
    SDL_Event event;





    while (continuer)
    {

        SDL_WaitEvent(&event);
        switch(event.type)
        {


            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {




                       case SDLK_UP:


                       maine(1);

                       break;

                       case SDLK_DOWN:
                       maine(2);
                } break;

        }
    }
}

void ouvrirGrille()
{

   choix_grille();
}

void surfaces()
{

    /*Chargement du fond */
    fond_newGrille = SDL_LoadBMP("fond_menu.bmp");
    fond = SDL_LoadBMP("fond.bmp");

    /* Chargement des differentes images */
    kase_noir = SDL_LoadBMP("case_noir.bmp");
    kase = SDL_LoadBMP("case.bmp");
    kase_blanc = SDL_LoadBMP("case_blanc.bmp");
    kase_ind = SDL_LoadBMP("case_ind.bmp");
}

void freesurfaces()
{
    SDL_FreeSurface(fond);
    SDL_FreeSurface(kase_noir);
    SDL_FreeSurface(kase);
    SDL_FreeSurface(kase_blanc);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(texte_resolution);
    SDL_FreeSurface(kase_ind);
}

void affiche_indices(picross picross1)
{
    int i;
    position_grille.x = (800/2) - ((picross1.nb_lignes*(34))/2);
    position_grille.y = (600/2) - ((picross1.nb_colonnes*(34))/2)+5;
    for (i=0;i<picross1.nb_lignes;i++)
    {
        char indices[20]="";
        int compteur=0;
        SDL_FreeSurface(texte);

        liste temp=picross1.ind_lignes[i];
        while(temp != NULL)
        {
        compteur=compteur+1;
        position_grille.x=position_grille.x - 15;
        sprintf(indices,"%d",temp->info);
        texte = TTF_RenderText_Blended(police, indices, couleurBlanc);
        SDL_BlitSurface(texte,NULL, ecran, &position_grille);


        temp=temp->succ;
        }
        position_grille.x=position_grille.x + (15*(compteur)) ;
        compteur=0;


        position_grille.y=position_grille.y + 34;
    }

    position_grille.x = (800/2) - ((picross1.nb_lignes*(34))/2) + 12;
    position_grille.y = (600/2) - ((picross1.nb_colonnes*(34))/2);
     for (i=0;i<picross1.nb_colonnes;i++)
    {
        char indices[20]="";
        int compteur=0;
        SDL_FreeSurface(texte);

        liste temp=picross1.ind_colonnes[i];
        while(temp != NULL)
        {
        compteur=compteur+1;
        //if (compteur==1) position_grille.y=position_grille.y - 5;
        position_grille.y=position_grille.y - 25;
        sprintf(indices,"%d",temp->info);
        texte = TTF_RenderText_Blended(police, indices,couleurBlanc);
        SDL_BlitSurface(texte,NULL, ecran, &position_grille);


        temp=temp->succ;
        }
        position_grille.y=position_grille.y + (25*(compteur)) ;
        compteur=0;


        position_grille.x=position_grille.x + 34;
    }

}

void affiche_grille(picross picross1)
{
    int i, j ;
    for (i=0;i<picross1.nb_lignes;i++) {
    for (j=0;j<picross1.nb_colonnes;j++)
     {

        if (picross1.grille[i][j]==gris)
            {
                SDL_BlitSurface(kase, NULL, ecran, &position_grille);
            }
            if (picross1.grille[i][j]==noir)
            {
                SDL_BlitSurface(kase_noir, NULL, ecran, &position_grille);
            }
            if (picross1.grille[i][j]==blanc)
            {
                SDL_BlitSurface(kase_blanc, NULL, ecran, &position_grille);
            }

    position_grille.x=position_grille.x +34;

    }
    position_grille.x = (800/2) - ((picross1.nb_lignes*(34))/2);
    position_grille.y=position_grille.y + 34;
    }

}

void maine(int choix)
{
    picross picross1;

    picross1=Initialisation(choix);



    surfaces();

    position_fond.x=0;
    position_fond.y=0;
    position_grille.x = (800/2) - ((picross1.nb_lignes*(34))/2);
    position_grille.y = (600/2) - ((picross1.nb_colonnes*(34))/2);





    SDL_BlitSurface(fond, NULL, ecran, &position_fond);

    police = TTF_OpenFont("angelina.ttf", 22);
    police_resolution=TTF_OpenFont("angelina.ttf",30);

    texte_resolution= TTF_RenderText_Blended(police_resolution, "Pour lancer la Resolution, tapez Espace !",couleurNoire);
    position_bouton_resolution.x =(800/2) - (texte_resolution->w/2);
    position_bouton_resolution.y =600 -50;
    SDL_BlitSurface(texte_resolution,NULL,ecran, &position_bouton_resolution);

    texte_bouton_grille=TTF_RenderText_Blended(police_resolution, "Pour une nouvelle grille, tapez BackSpace",couleurBlanc);
    position_bouton_grille.x=800-415;
    position_bouton_grille.y=7;
    SDL_BlitSurface(texte_bouton_grille,NULL,ecran, &position_bouton_grille);



    affiche_grille(picross1);
    affiche_indices(picross1);

    SDL_Flip(ecran);



    pause(picross1);








    TTF_CloseFont(police);
    TTF_Quit();
    freesurfaces();
    SDL_Quit();

}

int main(int argc, char *argv[])
{
     SDL_Init(SDL_INIT_VIDEO);

    TTF_Init();

    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
    if (ecran == NULL)
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }



    SDL_WM_SetCaption("Picross", NULL);

    maine(0);

    return 0;
}





