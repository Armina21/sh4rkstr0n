#ifndef _Terrain
#define _Terrain

#include <cassert>
#include "enum.h"
#include "Joueur.h"
#include "vec2D.h"

class Terrain
{
    private :

        int m_dimx ;
        int m_dimy ;
        IDCase ter[100][100] ;

    public :
        
        //constructeur 
        Terrain () ;

        //reinitialise le terrain 
        void cleanTerrain(bool terrain) ;

        int getDimX () const;
        int getDimY () const;

        IDCase getXY (const vec2D v) const;
        void setXY (const vec2D p, IDCase c) ; 

        //verifie que la position du joueur est valide
        bool estPositionValide (const vec2D v, bool inv) const;
        
        //fait apparaitre les traces des joueurs 
        void laisserTrace (const vec2D p, const IDCase c);

        void testRegression () ;
};

inline int Terrain::getDimX () const { return m_dimx; }

inline int Terrain::getDimY () const {	return m_dimy; }

#endif
