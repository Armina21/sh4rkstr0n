#ifndef _JEU
#define _JEU
#include "enum.h"
#include "Joueur.h"
#include "Terrain.h"
#include "vec2D.h"
#include "time.h"
#include <cassert>

const int taille_x = 40;
const int taille_y = 25;

class Jeu
{
private:
    Terrain ter;
    Joueur j1;
    Joueur j2;
    clock_t dureeBonus;
    bool bonus;

public:
    Jeu();

    // fonctions get
    const Terrain &getConstTerrain() const;
    const Joueur &getConstJ1() const;
    const Joueur &getConstJ2() const;
    Joueur &getJ1();
    Joueur &getJ2();
    clock_t getTime() const;
    bool getBonus() const;

    // fonction set
    void setBonus(bool b);

    // reinitialise le terrain, lance une nouvelle manche
    void NouvelleManche(bool terrain);

    // deplacement des joueurs
    void actionClavier(const char touche);
    void avance(bool const terrain, Joueur &j);

    int multOS;  //coefficient multiplicateur selon l'OS

    // deplacement auto de l'IA
    int analyse(vec2D dep);
    void directionIA();
    void avanceIA(bool const terrain);

    // fonctions d'affichage
    void AffBonus();
    void afficheChronoBonus();

    // gestion des collisions entre joueurs, et avec les bonus
    void Interaction(bool terrain, Joueur &jActeur, Joueur &jAutre);

    void testRegression();
};

inline const Terrain &Jeu::getConstTerrain() const { return ter; }

inline const Joueur &Jeu::getConstJ1() const { return j1; }
inline const Joueur &Jeu::getConstJ2() const { return j2; }

inline Joueur &Jeu::getJ1() { return j1; }
inline Joueur &Jeu::getJ2() { return j2; }

inline clock_t Jeu::getTime() const { return dureeBonus; }
inline bool Jeu::getBonus() const { return bonus; }
inline void Jeu::setBonus(bool b) { bonus = b; }

#endif
