#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

int box_blanc(ligne m_ligne, liste ind_ligne, int longueur_ligne, liste *L_modif) //renvoie 1 quand fini
{
    int i=0;//compteur de cases sur la ligne
    int k=0;//compteur de cases noires sur la ligne
    int s=0;//somme des indices=nombre total de cases noires à placer sur la ligne
    liste L=ind_ligne;//copie de ind_ligne
    //calcul de s:
    while (L!=NULL)
    {
        s=s+L->info;
        L=L->succ;
    }
    //calcul du nombre de cases noires déjà présentes sur la ligne
    while (i<longueur_ligne)
    {
        if (m_ligne[i]==noir)
        {
            k++;
        }
        i++;
    }
    //si toutes les cases noires sont présentes, on complète avec du blanc
    if (k>s) return 0;
    else if (k==s)
    {
        for (i=0;i<longueur_ligne;i++)
        {
            if (m_ligne[i]==gris)
            {
                m_ligne[i]=blanc;
                *L_modif=ajouterEnTete(*L_modif,i);
            }
        }

    }
    return 1;//ligneSolution(ligne m_ligne, liste ind_lignes, int longueur_ligne);
}

int bord_box_blanc(ligne L, liste ind_ligne, int taille, liste *L_modif)
{

    int i=0,j=0, premier_ind=0, dernier_ind=0;
    liste M;
    M=ind_ligne;

    premier_ind=M->info;
    while ((M->succ)!=NULL)
    {
        M=M->succ;
    }
    dernier_ind=M->info;



    while ((i<taille-1) && (L[i]==blanc))
        /*On part du bord gauche de la ligne et on avance tant qu'on croise des box blanches*/
    {
        i++;
    }

    /*Si la box qui suit est noire, alors c'est le premier indice forcément*/
    if (L[i]==noir)
    {
        i++; //Pour ne pas colorier la box noire encore en noir
        j=premier_ind-1;
        while (j>0)
        {
            if (L[i]==blanc)
            {
                return 0;
            }

            //Pas la peine de recolorier une case noire
            else if (L[i]==gris)
            {
                L[i]=noir;
                *L_modif=ajouterEnTete(*L_modif,i);
            }

            i++;
            j--;
        }
        /*Une box blanche viendra forcément clore le premier indice*/
        if (L[i]==noir)
        {
            return 0;
        }
        else if (L[i]==gris)
        {
            L[i]=blanc;
            *L_modif=ajouterEnTete(*L_modif,i);
        }
    }


    /*De même pour le bord droit*/
    i=taille-1;
    while ((i>0)&&(L[i]==blanc))
        /*On part du bord droit de la ligne et on recule tant qu'on croise des box blanches*/
    {
        i--;
    }

    /*Si la box qui suit est noire, alors c'est le dernier indice forcément*/
    if (L[i]==noir)
    {
        i--;//Pour ne pas colorier la box noire encore en noir.

        j=dernier_ind-1;
        while (j>0)
        {
            if (L[i]==blanc)
            {
                return 0;
            }


            //Pas la peine de recolorier une case noire
            else if (L[i]==gris)
            {
                L[i]=noir;
                *L_modif=ajouterEnTete(*L_modif,i);
            }

            i--;
            j--;
        }
        /*Une box blanche viendra forcément clore le dernier indice*/
        if (L[i]==noir)
        {
            return 0;
        }
        else if (L[i]==gris)
        {
            L[i]=blanc;
            *L_modif=ajouterEnTete(*L_modif,i);
        }
    }
    return 1;
}

int minimal_box_blanc(ligne L, liste ind_ligne, int longueur, liste *L_modif)
{

    /*************************/
    int min, i=0, j=0, k=0, temoin=0;
    liste M;
    M=ind_ligne;
    min=elementMin(M);
    /*************************/

//Pour toute case, (hormis les 2 dernières qui n'ont pas d'intérêt pour cette méthode)
    for (i=0; i<longueur-1; i++)
    {
        temoin=0;
        if (L[i]==blanc)
        {
            j=i+1;
            while ((L[j]==gris)||(L[j]==noir))
            {
                if (L[j]==noir) temoin=1;
                j++;
            }

            /*Si toutes les cases sont grises entre deux blanches et que le plus petit indice ne rentre pas
            alors on peut tout colorier en blanc*/
            if ((j-i-1)<min)
            {
                if (temoin) return 0;
                i++;
                for (k=i;k<j;k++)
                {
                    L[k]=blanc;
                    *L_modif=ajouterEnTete(*L_modif,k);
                }
            }
        }
    }
    return 1;
}

//CASE MINMAX

int derniereCaseGauche(int depart, int indice, box *grille, int taille)  /* fonction qui renvoie la position de la derniere case d'un bloc le plus Ã  gauche possible
depart est la valeure de la case ou on dÃ©marre le test, indice la taille du bloc cherche, et grille, la ligne teste, taille est la taille de la ligne*/
{
    int act;                                             /* la valeure de la case actuelle*/
//    int i;                                               /*un simple compteur*/
    act=depart;
    while ((act-depart+1<indice)&&(act<taille))         /*je parcours les cases de la grille pour savoir ou s'arrete mon bloc*/
    {
        if (grille[act]==noir)                           /* si la case est noire le bloc est forcÃ©ment autour*/
        {
            act=depart+indice-1;
        }
        else if (grille[act]==blanc)                          /* si elle est blanche, le bloc est forcÃ©ment aprÃ¨s*/
        {
            act++;
            depart=act;
        }
        else act++;                                       /* si elle est grise, je me contente d'avancer d'une case*/
    }
    if (act>=taille)                                      /* si act depasse la taille c'est qu'il n'y a pas de solution donc je signale une erreure*/
    {
        return -1;
    }
    /*je verfifie qu'il n'y ai pas de case blanche au milieu s'il y en a je renvoie -1 pour signaler une erreure*/

    while ((act+1<taille)&&(grille[act+1]==noir))                                    /* pour Ãªtre sur de ne pas renvoyer un bloc complet collee a une case noire, ce qui serait impossible*/
    {
        act++;
    }
    return act;
}

int premiereCaseDroite(int depart, int indice, box *grille) /* pareil que plus haut, mais Ã  l'envers*/
{
    int act;
//    int i;
    act=depart;
    while ((depart-act+1<indice)&&(act>=0))
    {
        if (grille[act]==noir)
        {
            act=depart-indice+1;
        }
        else if (grille[act]==blanc)
        {
            act--;
            depart=act;
        }
        else act--;
    }
    if (act<0)
    {
        return -1;
    }

    while ((act>=0)&&(grille[act-1]==noir))
    {
        act--;
    }
    return act;
}

int coloriage(liste derCaseGauche, liste premCaseDroite, box *grille, liste *modif)             /* changer des listes des places extremes en case noire sur la grille*/
{
    int i;
    while (derCaseGauche!=NULL)                                 /* je parcours les listes */
    {
        if (premCaseDroite->info<=derCaseGauche->info)                          /* si q.info est plus petit ou egal ca veut dire que les deux possitions extreme se chevauchent, il faut donc colorier en noir*/
        {
            for (i=premCaseDroite->info;i<=derCaseGauche->info;i++)                  /* pour aller de la position la plus Ã  gauche Ã  celle la plus a droite*/
            {
                if (grille[i]==gris)             //!!!!!!!          /* si la case est blanche, je renvoie une erreure, sinon je colorie*/
                {
                    grille[i]=noir;
                    *modif=ajouterEnFin(*modif,i);
                }
                else if (grille[i]==noir)
                {
                }
                else return -1;
            }

        }
        derCaseGauche=derCaseGauche->succ;                       /* je passe au bloc suivant*/
        premCaseDroite=premCaseDroite->succ;
    }
    return 0;
}

int caseMinMax(liste indice, box *grille, int taille, liste *modif) //renvoie 0 si erreur
{
    int act;
    /* pour avoir la case actuelle*/
    liste derCaseGauche, premCaseDroite;                 /* pour stocker les rÃ©sultats des fonctions premiere case la plus a droite et derniere case la plus a gauche*/
    liste p,q;
    derCaseGauche=premCaseDroite=NULL;                    /* pour parcourir la liste indice*/
    p=indice;
    q=NULL;
    act=0;
    while (p!=NULL)                                    /* pour remplir ma liste derCaseGauche*/
    {
        act=derniereCaseGauche(act,p->info,grille,taille);
        if (act==-1)                                           /* si ma fonction a retourne -1 c'est qu'il y a une erreur, donc je la retransmet*/
        {
            return 0;
        }
        derCaseGauche=ajouterEnFin(derCaseGauche,act);
        act+=2;
        q=ajouterEnTete(q,p->info);      /*je retourne la liste pour la parcourir à l'envers dans la deuxiÃ¨me partie */
        p=p->succ;           /* je decale sur la droite pour tenir compte de la case blanche entre les blocs*/
    }
    act=taille-1;
    while (q!=NULL)                      /* pour remplir ma liste preCaseDroite*/
    {
        act=premiereCaseDroite(act,q->info,grille);
        if (act==-1)                                   /* si ma fonction a retourne -1 c'est qu'il y a une erreure, donc je la retransmet*/
        {
            return 0;
        }
        premCaseDroite=ajouterEnTete(premCaseDroite,act);                       /* je rajoute a la fin car sinon les deux listes ne seraient pas dans le meme sens*/
        act-=2;                                                   /* je decale sur la gauche pour tenir compte de la case blanche entre les blocs*/
        q=q->succ;
    }
    return coloriage(derCaseGauche,premCaseDroite,grille,modif)+1;               /* s'il y a une erreure je la retransmet, sinon coloriage utilise mes listes pour noircir les cases voulues*/
}
