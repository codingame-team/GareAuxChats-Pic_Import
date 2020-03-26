//
//  souris.c
//  gare_aux_chats
//
//  Created by Pierrick Delrieu on 18/03/2020.
//  Copyright © 2020 Pierrick Delrieu. All rights reserved.
//


#include "fonctions.h"


int case_valide_souris(int i, int j, int **monde)
{
    // 1 si plateau[i][j] valide et 0 sinon

    int valide = 0;

    if((i<HEIGHT) && (j<WIDTH) && (i>=0) && (j>=0))
    {
        valide = 1;
    }

    if((valide == 1) && (monde[i][j] == CASE_VIDE))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void position_souris(int **monde, int souris, int position[2])
{
    int i, j;
    
    for(i=0; i<HEIGHT; i++)
    {
        for(j=0; j<WIDTH; j++)
        {
            if(monde[i][j] == souris)
            {
                position[0] = i;
                position[1] = j;
            }
        }
    }
}

void deplacement_souris(int ***monde, int souris, int position [2], int mouvement)
{
    if((case_valide_souris(position[0], position[1] + 1, *monde) == 1) && (mouvement == RIGHT))
    {
        *(*(*monde + position[0])+position[1]) = CASE_VIDE;
        *(*(*monde + position[0])+(position[1] + 1)) = souris;
    }
    else if((case_valide_souris(position[0], position[1] - 1, *monde) == 1) && (mouvement == LEFT))
    {
        *(*(*monde + position[0])+position[1]) = CASE_VIDE;
        *(*(*monde + position[0])+(position[1] - 1)) = souris;
    }
    else if((case_valide_souris(position[0] - 1, position[1], *monde) == 1) && (mouvement == UP))
    {
        *(*(*monde + position[0])+position[1]) = CASE_VIDE;
        *(*(*monde + (position[0] - 1))+position[1]) = souris;
    }
    else if((case_valide_souris(position[0] + 1, position[1], *monde) == 1) && (mouvement == DOWN))
    {
        *(*(*monde + position[0])+position[1]) = CASE_VIDE;
        *(*(*monde + (position[0] + 1))+position[1]) = souris;
    }
}


int condition_vie_souris(int ***monde, int souris, int position_joueur[2])
{
//    1 si le joueur doit continuer et 0 sinon
    if(*(*(*monde + position_joueur[0])+position_joueur[1]) != souris)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
