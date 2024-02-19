#include "core/Jeu.h"
#include "core/Joueur.h"
#include "core/Terrain.h"

#include <iostream>

int main ()
{
    Joueur j;
    Terrain ter;
    Jeu jeu;
    j.testRegression();
    ter.testRegression();
    jeu.testRegression();

    return 0;
}