#ifndef _JOUEUR
#define _JOUEUR 

#include "vec2D.h"
#include "enum.h"
#include <time.h> 
#include <cassert>

class Joueur 
{
    private : 
        vec2D pos ; 
        int score ; 
        IDCase id ;
        clock_t timer ; 
        vec2D direction ; 

        bool invincible ; 
        bool ralenti ;
        bool stop ; 

        int nbDep ;                 //pour l'IA

    public : 
        //constructeurs 
        Joueur();
        Joueur(vec2D p, vec2D d, IDCase i, int nb) ;

        //deplacement avec la direction, en fonction des bonus
        vec2D Dep() ; 
        
        vec2D getDirection() const ;
        void setDirection (const vec2D d) ; 

        vec2D getPos () const ;
        void setPos (const vec2D p) ; 

        int getPosX () const ; 
        void setPosX (float a) ;

        int getPosY () const ;
        void setPosY (float b) ;
        
        int getnbDep () ;
        void setnbDep (int nb) ;

        IDCase getIDc () const ; 

        int getScore () const ; 
        void setScore (int newScore) ;

        bool getInv () const ;
        void setInv (bool b) ; 

        bool getRalenti () const ;
        void setRalenti (bool b) ; 
        
        bool getStop () const ; 
        void setStop (bool b) ; 

        //active les bonus/malus 
        void bonusI () ; 
        void malusR () ; 
        void malusS () ; 

        clock_t getTimer () const ;

        void testRegression () ;
}; 

#endif