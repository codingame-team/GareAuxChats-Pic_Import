//
//  main.c
//  gare_aux_chats
//
//  Created by Pierrick Delrieu on 18/03/2020.
//  Copyright © 2020 Pierrick Delrieu. All rights reserved.
//


#include "fonctions.h"



int main()
{
    int **monde = NULL;
    int tour = 0;
    srand((unsigned)time(NULL)); //initialisation du temps


    monde = creation_monde_vide(HEIGHT, WIDTH);

    int position_souris1[2];
    int position_souris2[2];
    int position_souris3[2];
    int position_souris4[2];
    int position_souris5[2];

    position_initial_souris(&monde,position_souris1,position_souris2,position_souris3,position_souris4,position_souris5);


    //BOUCLE DE JEU
    while(condition_arret_partie(monde) == 1)
    {

        //JOUEUR1
        if(condition_vie_souris(&monde, SOURIS1, position_souris1) == 1)
        {
            deplacement_souris(&monde, SOURIS1, position_souris1, souris1(monde));
            position_souris(monde, SOURIS1, position_souris1);
        }

        //JOUEUR2
        if(condition_vie_souris(&monde, SOURIS2, position_souris2) == 1)
        {
            deplacement_souris(&monde, SOURIS2, position_souris2, souris2(monde));
            position_souris(monde, SOURIS2, position_souris2);
        }

        //JOUEUR3
        if(condition_vie_souris(&monde, SOURIS3, position_souris3) == 1)
        {
            deplacement_souris(&monde, SOURIS3, position_souris3, souris3(monde));
            position_souris(monde, SOURIS3, position_souris3);
        }

        //JOUEUR4
        if(condition_vie_souris(&monde, SOURIS4, position_souris4) == 1)
        {
            deplacement_souris(&monde, SOURIS4, position_souris4, souris4(monde));
            position_souris(monde, SOURIS4, position_souris4);
        }

        //JOUEUR5
        if(condition_vie_souris(&monde, SOURIS5, position_souris5) == 1)
        {
            deplacement_souris(&monde, SOURIS5, position_souris5, souris5(monde));
            position_souris(monde, SOURIS5, position_souris5);
        }

        //ZOMBIES
        deplacement_chat(&monde);
        random_ajout_chat(&monde);
        reabilitation_valeur_chat(&monde);

        affichage_monde(monde);
        tour ++;
        _sleep(1); //met le programme en pause pendant 1 sec
        supr_console();
    }

    printf("Fin Partie au tour %d", tour);

    desalocation_monde(monde);
    return 0;
}

