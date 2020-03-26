//
//  souris.c
//  gare_aux_chats
//
//  Created by Pierrick Delrieu on 21/03/2020.
//  Copyright © 2020 Pierrick Delrieu. All rights reserved.
//

#include "../source/fonctions.h"

/*Les fonctions des joueurs peuvent etre consitué de :
 - int case_valide_souris(int i, int j, int **monde);
 - RIGHT, LEFT, UP, DOWN, SPOT
 - CHAT
 - CASE_VIDE
 - SOURIS1, SOURIS2, SOURIS3, SOURIS4, SOURIS5
 - HEIGHT, WIDHT (les tailles du monde)

Si dans la fonction le joueur modifie le monde, la souris est automatiquement disqualifié.
*/

void position_initial_souris(int ***monde, int position_joueur1[2], int position_joueur2[2],int position_joueur3[2],int position_joueur4[2],int position_joueur5[2])
{
    position_joueur1[0] = 14;
    //position_joueur1[0] = 9;
    position_joueur1[1] = 2;

    position_joueur2[0] = 2;
    position_joueur2[1] = 3;

    position_joueur3[0] = 6;
    position_joueur3[1] = 3;

    position_joueur4[0] = 9;
    position_joueur4[1] = 7;

    position_joueur5[0] = 11;
    //position_joueur5[0] = 5;
    position_joueur5[1] = 2;



    *(*(*monde + position_joueur1[0])+position_joueur1[1]) = SOURIS1;
    *(*(*monde + position_joueur2[0])+position_joueur2[1]) = SOURIS2;
    *(*(*monde + position_joueur3[0])+position_joueur3[1]) = SOURIS3;
    *(*(*monde + position_joueur4[0])+position_joueur4[1]) = SOURIS4;
    *(*(*monde + position_joueur5[0])+position_joueur5[1]) = SOURIS5;
}

