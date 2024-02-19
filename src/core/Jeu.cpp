#include "Jeu.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>

// Init
Jeu::Jeu() : ter(), j1(vec2D(16, 18), vec2D(1, 0), J1, 0), j2(vec2D(48, 18), vec2D(-1, 0), J2, 3)
{
	ter.laisserTrace(j1.getPos(), J1);
	ter.laisserTrace(j2.getPos(), J2);

	dureeBonus = 0;
	bonus = false;
}

// Initialise les joueurs et le terrain
void Jeu::NouvelleManche(bool terrain)
{
	// remet les joueurs a leurs positions de depart
	j1.setPos(vec2D(16, 18));
	j2.setPos(vec2D(48, 18));
	// change l'id de leurs cases de depart
	ter.setXY(vec2D(16, 18), J1);
	ter.setXY(vec2D(48, 18), J2);
	// remet leurs directions de depart (face a face)
	j1.setDirection(vec2D(1, 0));
	j2.setDirection(vec2D(-1, 0));

	// efface toutes les traces et bonus etant sur le terrain a la fin de la manche
	ter.cleanTerrain(terrain);

	// remet tout les booleens de bonus a false
	// pour que chaques joueurs recommance la partie sans bonus
	j1.setInv(false);
	j2.setInv(false);
	j1.setRalenti(false);
	j2.setRalenti(false);
	j1.setStop(false);
	j2.setStop(false);

	// informe qu'il n'y a plus aucun bonus de present sur la map
	bonus = false;
}

// fait avancer un joueur d'une case en fonction de sa direction
// et des bonus/malus
void Jeu::avance(bool const terrain, Joueur &j)
{
	j.Dep();
	ter.laisserTrace(j.getPos(), j.getIDc());

	// deplacement terrain sans murs
	if (terrain == false)
	{
		// wrap around horizontally
		if (j.getPosX() == ter.getDimX() - 1)
		{
			j.setPos(vec2D(0, j.getPosY()));
			ter.laisserTrace(j.getPos(), j.getIDc());
		}
		else if (j.getPosX() == 0)
		{
			j.setPos(vec2D(ter.getDimX() - 1, j.getPosY()));
			ter.laisserTrace(j.getPos(), j.getIDc());
		}

		// wrap around vertically
		if (j.getPosY() == ter.getDimY() - 1)
		{
			j.setPos(vec2D(j.getPosX(), 0));
			ter.laisserTrace(j.getPos(), j.getIDc());
		}
		else if (j.getPosY() == 0)
		{
			j.setPos(vec2D(j.getPosX(), ter.getDimY() - 1));
			ter.laisserTrace(j.getPos(), j.getIDc());
		}
	}

	// gestion des bonus/malus
	if (j.getInv() == true)
	{
		dureeBonus = clock() - j.getTimer(); 	 // regarder le chrono
		//std :: cout << dureeBonus ; 
		if (dureeBonus >= 6000*multOS)				 // bonus pendant 10 seconde (en ms)
		{
			j.setInv(false);
		}
	}
	else if (j.getRalenti() == true)
	{
		dureeBonus = clock() - j.getTimer();
		if (dureeBonus >= 6000*multOS)
		{
			j.setRalenti(false);
		}
	}
	else if (j.getStop() == true)
	{
		dureeBonus = clock() - j.getTimer();
		if (dureeBonus >= 5000*multOS) // bonus pendant 5 secondes (en ms)
		{
			j.setStop(false);
		}
	}
}

// Permet de determiner la longueur d'un chemin avant une collision
int Jeu ::analyse(vec2D dep)
{
	vec2D dir = j2.getPos();
	int s = 0;
	do
	{
		dir = dir + dep;
		s++;
	} while (ter.estPositionValide(dir, false) != false);

	return s;
}

// Change la direction de l'IA
void Jeu ::directionIA()
{
	int h, g, d, b;
	int c, alea;
	h = analyse(vec2D(0, 1));
	g = analyse(vec2D(1, 0));
	d = analyse(vec2D(-1, 0));
	b = analyse(vec2D(0, -1));

	alea = rand() % 2 + 1;
	if (alea == 1)
		c = std::max(h, std::max(b, std::max(d, g)));
	else
		c = std::max(g, std::max(d, std::max(b, h)));

	if (c == h)
		j2.setDirection(vec2D(0, 1));
	if (c == b)
		j2.setDirection(vec2D(0, -1));
	if (c == g)
		j2.setDirection(vec2D(1, 0));
	if (c == d)
		j2.setDirection(vec2D(-1, 0));
}

// Fait avancer un joueur d'une case a une direction
// avec IA
void Jeu ::avanceIA(bool const terrain)
{
	// Deplacement du vrai joueur
	avance(terrain, j1) ; 

	// Deplacement de l'IA
	if (j2.getnbDep() == 0)
	{
		directionIA();
		j2.setnbDep(3);
	}
	else
	{
		avance(terrain, j2) ; 
		j2.setnbDep(j2.getnbDep() - 1);
	}
	// timer ++ ;
}

// modifie la direction d'un joueur lorsqu'on appuie sur une touche
void Jeu ::actionClavier(const char touche)
{
	switch (touche)
	{
	case 'd':
		if (j1.getDirection() != vec2D(-1, 0)) // interdit d'aller dans la direction opposée
		{
			j1.setDirection(vec2D(1, 0));
		}
		break;
	case 'q':

		if (j1.getDirection() != vec2D(1, 0))
		{
			j1.setDirection(vec2D(-1, 0));
		}
		break;
	case 's':
		if (j1.getDirection() != vec2D(0, -1))
		{
			j1.setDirection(vec2D(0, 1));
		}
		break;
	case 'z':
		if (j1.getDirection() != vec2D(0, 1))
		{
			j1.setDirection(vec2D(0, -1));
		}
		break;

	case 'm':
		if (j2.getDirection() != vec2D(-1, 0))
		{
			j2.setDirection(vec2D(1, 0));
		}
		break;
	case 'k':
		if (j2.getDirection() != vec2D(1, 0))
		{
			j2.setDirection(vec2D(-1, 0));
		}
		break;
	case 'l':
		if (j2.getDirection() != vec2D(0, -1))
		{
			j2.setDirection(vec2D(0, 1));
		}
		break;
	case 'o':
		if (j2.getDirection() != vec2D(0, 1))
		{
			j2.setDirection(vec2D(0, -1));
		}
		break;
	default:
		break;
	}
}

// affiche aléatoirement un bonus sur le terrain
// toutes les 6 secondes ou s'il n'y a pas d'autre bonus
// sur le terrain
void Jeu::AffBonus()
{
	int posX;
	int posY;
	srand(time(NULL));
	clock_t t = clock();
	if (((t*multOS / 1000) % 6 == 0) && (bonus == false) ) 
	{
		do
		{
			posX = (rand() % ter.getDimX()) + 1;
			posY = (rand() % ter.getDimY()) + 1;
		} while (ter.getXY(vec2D(posX, posY)) != VIDE); 	// choisis une nouvelle case tant qu'elle n'est pas vide
		int b = (rand() % 3) + 1;							// choix aléatoire entre les 3 bonus
		if (b == 2)
		{
			ter.setXY(vec2D(posX, posY), RALENTI);
			bonus = true;
		}
		else if (b == 1)
		{
			ter.setXY(vec2D(posX, posY), INVINCIBLE);
			bonus = true;
		}
		else
		{
			ter.setXY(vec2D(posX, posY), STOP);
			bonus = true;
		}
	}
}

void Jeu ::Interaction(bool terrain, Joueur &jActeur, Joueur &jAutre)
{
	IDCase Case = ter.getXY(jActeur.getPos() + jActeur.getDirection());

	// si les deux joueurs se rentrent dedans face a face il y a egalite (aucun point)
	if (jActeur.getPos() + jActeur.getDirection() == jAutre.getPos() + jAutre.getDirection())
	{
		NouvelleManche(terrain);
	}

	// cas de collision avec un bonus
	else if (Case == INVINCIBLE)
	{
		jActeur.bonusI();
		setBonus(false);
	}

	else if (Case == RALENTI)
	{
		jAutre.malusR();
		setBonus(false);
	}

	else if (Case == STOP)
	{
		jAutre.malusS();
		setBonus(false);
	}

	// si la positions n'est pas valide, il y a collision alors on ajoute
	// un point a l'autre joueur et on recommence la manche
	else if (ter.estPositionValide(jActeur.getPos() + jActeur.getDirection(), jActeur.getInv()) != true)
	{
		jAutre.setScore(jAutre.getScore() + 1);
		NouvelleManche(terrain);
	}
}

void Jeu::afficheChronoBonus()
{
	if (j1.getInv() == true)
	{
		std::cout << "Bonus Invincible du Joueur 1 : " << dureeBonus / 1000 << std::endl;
	}

	if (j2.getInv() == true)
	{
		std::cout << "Bonus Invincible du Joueur 2 : " << dureeBonus / 1000 << std::endl;
	}

	else if (j1.getRalenti() == true)
	{
		std::cout << "Malus Ralenti du Joueur 2 : " << dureeBonus / 1000 << std::endl;
	}

	else if (j2.getRalenti() == true)
	{
		std::cout << "Malus Ralenti du Joueur 1 : " << dureeBonus / 1000 << std::endl;
	}

	else if (j1.getStop() == true)
	{
		std::cout << "Malus Stop du Joueur 2 : " << dureeBonus / 1000 << std::endl;
	}

	else if (j2.getStop() == true)
	{
		std::cout << "Malus Stop du Joueur 1 : " << dureeBonus / 1000 << std::endl;
	}
}

void Jeu::testRegression()
{
	Jeu jeu;
	// Verif du terrain
	assert(jeu.getConstTerrain().getDimX() == 64);
    assert(jeu.getConstTerrain().getDimY() == 36);

	// Verif du joueur 1
	assert(jeu.getConstJ1().getPos() == vec2D(16,18));
	assert(jeu.getConstJ1().getDirection() == vec2D(1,0));
	assert(jeu.getConstJ1().getIDc() == J1);
	assert(jeu.getJ1().getnbDep() == 0);
	assert(jeu.getConstTerrain().getXY(jeu.getConstJ1().getPos()) == J1);

	// Verif du joueur 2
	assert(jeu.getConstJ2().getPos() == vec2D(48,18));
	assert(jeu.getConstJ2().getDirection() == vec2D(-1,0));
	assert(jeu.getConstJ2().getIDc() == J2);
	assert(jeu.getJ2().getnbDep() == 3);
	assert(jeu.getConstTerrain().getXY(jeu.getConstJ2().getPos()) == J2);
}