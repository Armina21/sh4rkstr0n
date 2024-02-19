#include "Joueur.h"
#include <stdio.h>

Joueur :: Joueur() {
    pos = vec2D(15,15) ; 
    score = 0 ; 
    id = VIDE;
    direction = vec2D(1,0) ; 
    timer = 0 ;

    invincible = false ;
    ralenti = false ;
    stop = false ;  

    nbDep = 0 ;
}

Joueur :: Joueur(vec2D p, vec2D d, IDCase i, int nb)
{
    pos = p ;
    score = 0 ; 
    id = i ;
    direction = d ; 
    timer = 0 ;

    invincible = false ; 
    ralenti = false ; 
    stop = false ; 

    nbDep = nb ;
}

//gestion des deplacement grace a la direction 
//en fonction des bonus/malus 
vec2D Joueur :: Dep() 
{
    if (ralenti == true)
    {
        pos = pos + (direction/2) ;       
    }
    else if (ralenti == false && stop == false)
    {
        pos = pos + direction ;
    }  
    else 
    {
        pos = pos ; 
    }
    return pos ; 
}

vec2D Joueur :: getDirection() const{ return direction; }
void Joueur :: setDirection (const vec2D d){ direction = d ; }

vec2D Joueur :: getPos () const { return pos ; }
void Joueur::setPos (const vec2D p) { pos = p ; }

int Joueur :: getPosX () const { return pos.x ; }
void Joueur :: setPosX (float a) { pos.x = a; }

int Joueur :: getPosY () const { return pos.y ; }
void Joueur :: setPosY (float b) { pos.y = b; }

int Joueur :: getnbDep () { return nbDep ; }
void Joueur :: setnbDep (int nb) { nbDep = nb ; }

IDCase Joueur :: getIDc () const { return id ; }

int Joueur :: getScore () const { return score ; }
void Joueur :: setScore (int newScore) { score = newScore ; }

bool Joueur :: getInv () const { return invincible ; }
void Joueur :: setInv (bool b) { invincible = b ; }

bool Joueur :: getRalenti () const { return ralenti ; }
void Joueur :: setRalenti (bool b) { ralenti = b ; }

bool Joueur :: getStop () const { return stop ; }
void Joueur :: setStop (bool b) { stop = b ; }

clock_t Joueur :: getTimer () const { return timer ; }

void Joueur::bonusI () 
{
    invincible = true ; 
    timer = clock() ; 
}

void Joueur::malusR ()
{
    ralenti = true ; 
    timer = clock() ; 
}

void Joueur::malusS ()
{
    stop = true ; 
    timer = clock() ;
}

void Joueur::testRegression()
{
    // Verification des constructeurs
    Joueur j;
    assert(j.getPos() == vec2D(15,15));
    assert(j.getScore() == 0);
    assert(j.getIDc() == VIDE);
    assert(j.getDirection() == vec2D(1,0));
    assert(j.getTimer() == 0);
    assert(j.getInv() == false);
    assert(j.getRalenti() == false);
    assert(j.getStop() == false);
    assert(j.getnbDep() == 0);

    Joueur j2(vec2D(2,5), vec2D(0,1), J2, 2);
    assert(j2.getPos() == vec2D(2,5));
    assert(j2.getScore() == 0);
    assert(j2.getIDc() == J2);
    assert(j2.getDirection() == vec2D(0,1));
    assert(j2.getTimer() == 0);
    assert(j2.getInv() == false);
    assert(j2.getRalenti() == false);
    assert(j2.getStop() == false);
    assert(j2.getnbDep() == 2);

    // Changement de pos et direction
    j.setPos(vec2D(20,10));
    assert(j.getPos() == vec2D(20,10));
    j.setDirection(vec2D(0,-1));
    assert(j.getDirection() == vec2D(0,-1));
    // Verif que la position = position + direction
    j.Dep();
    assert(j.getPos() == vec2D(20,9));

    j2.setPosX(4);
    j2.setPosY(18);
    assert(j2.getPosX() == 4);
    assert(j2.getPosY() == 18);

    j2.setnbDep(5);
    assert(j2.getnbDep() == 5);

    j2.setInv(true);
    assert(j2.getInv() == true);
    j2.setRalenti(true);
    assert(j2.getRalenti() == true);
    j2.setStop(true);
    assert(j2.getStop() == true);

    j.bonusI();
    assert(j.getInv() == true);
    j.malusR();
    assert(j.getRalenti() == true);
    j.malusS();
    assert(j.getStop() == true);
}