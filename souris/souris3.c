//
//  souris3.c
//  gare_aux_chats
//
//  Created by Pierrick Delrieu on 22/03/2020.
//  Copyright © 2020 Pierrick Delrieu. All rights reserved.
//

#include "../source/fonctions.h"
#include <math.h>

typedef struct Coordonnees position;
struct Coordonnees {
    int x;
    int y;
};

double calculDistance(position souris, position chat )
{
    return sqrt((chat.x-souris.x)^2+(chat.y-souris.y)^2);
}

position positionSouris(int **monde, int idSouris)
{
    position positionSouris;
    int i, j;

    for(i=0; i<HEIGHT; i++)
    {
        for(j=0; j<WIDTH; j++)
        {
            if ( monde[i][j] == idSouris )
            {
                positionSouris.x = i;
                positionSouris.y = j;
            }
        }
    }
    return positionSouris;
}

position positionChatProche(int **monde, position positionSouris)
{
    position positionChat, positionChatProche;
    int i, j;
    double distance, minDistance;

    minDistance = sqrt(WIDTH^2+HEIGHT^2);
    positionChatProche.x = WIDTH;
    positionChatProche.y = HEIGHT;

    for(i=0; i<HEIGHT; i++)
    {
        for(j=0; j<WIDTH; j++)
        {
            if ( monde[i][j] == CHAT )
            {
                positionChat.x = i;
                positionChat.y = j;
                distance = calculDistance(positionSouris, positionChat);
                if ( distance < minDistance )
                {
                    minDistance = distance;
                    positionChatProche.x = positionChat.x;
                    positionChatProche.y = positionChat.y;
                }
            }
        }
    }
    return positionChatProche;
}

int souris3(int **monde)
{
    int i, j;
    int x, y, X, Y;
    position pChat, pSouris;

    pSouris = positionSouris(monde, SOURIS3);
    pChat = positionChatProche(monde, pSouris);

    x = pSouris.x;
    y = pSouris.y;
    X = pChat.x;
    Y = pChat.y;

    /*      0 -------------------------> Y
            |
            | (X1,Y1)---(X1,y)------(X1,Y2)
            |   |   Q1    |     Q2     |
            |   |         |            |
            | (x,Y1)----(x,y)-------(x,Y2)
            |   |         |            |
            |   |   Q4    |     Q3     |
            | (X2,Y1)---(X2,y)------(X2,Y2)
            v
            X
    */

    if ( x > X && y > Y ) // Quadrant n°1 (Nord/Ouest)
    {
        if ( abs(X - x) > abs(Y - y) )
            return DOWN;
        else
            return RIGHT;
    }
    else if ( x < X && y > Y ) // Quadrant n°2 (Nord/Est)
    {
        if ( abs(X - x) > abs(Y - y) )
            return LEFT;
        else
            return DOWN;
    }
    else if ( x < X && y < Y ) // Quadrant n°3 (Sud-Est)
    {
        if ( abs(X - x) > abs(Y - y) )
            return UP;
        else
            return LEFT;
    }
    else if ( x < X && y > Y ) // Quadrant n°4 (Sud-Ouest)
    {
        if ( abs(X - x) > abs(Y - y) )
            return UP;
        else
            return RIGHT;
    }
    else if ( x == X )
    {
        if ( y < Y )
            return LEFT;
        else
            return RIGHT;
    }
    else if ( y == Y )
    {
        if ( x < X )
            return UP;
        else
            return DOWN;
    }
    else
        return SPOT; // là ma souris est très mal et il est déjà trop tard... (pSouris == pChat) :-DDDDD

}
