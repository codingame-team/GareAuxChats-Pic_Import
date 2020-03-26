//
//  souris4.c
//  gare_aux_chats
//
//  Created by Pierrick Delrieu on 22/03/2020.
//  Copyright © 2020 Pierrick Delrieu. All rights reserved.
//

#include "../source/fonctions.h"

int souris4(int **monde)
{
    int mouvement = 1 + (rand() % 4);

    if(mouvement == 1)
    {
        return RIGHT;
    }
    else if(mouvement == 2)
    {
        return LEFT;
    }
    else if(mouvement == 3)
    {
        return UP;
    }
    else if(mouvement == 4)
    {
        return DOWN;
    }
    else
    {
        return SPOT;
    }
}
