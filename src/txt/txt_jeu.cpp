#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32
#include "winTxt.h"

#include "txt_jeu.h"
using namespace std;

void txtAff(WinTXT &win, const Jeu &jeu)
{
	const Terrain &ter = jeu.getConstTerrain();
	const Joueur &j1 = jeu.getConstJ1();
	const Joueur &j2 = jeu.getConstJ2();

	win.clear();

	// Affichage des murs et des trainées
	for (int x = 0; x < ter.getDimX(); ++x)
		for (int y = 0; y < ter.getDimY(); ++y)
			win.print(x, y, ter.getXY(vec2D(x, y)));

	// Affichage du Joueur1
	win.print(j1.getPosX(), j1.getPosY(), 'J');
	// Affichage du Joueur2
	win.print(j2.getPosX(), j2.getPosY(), 'K');

	win.draw();

	std::cout << "score Joueur 1 : " << jeu.getConstJ1().getScore() << std::endl;
	std::cout << "score Joueur 2 : " << jeu.getConstJ2().getScore() << std::endl;
}

void menuBoucle(bool &choixMode, bool &choixTerr)
{
	cout << "--------------------Menu---------------------" << endl;

	cout << "----------------Choix du mode----------------" << endl;
	cout << "1. MultiPlayers" << endl;
	cout << "2. Soloplayer" << endl;

	cout << "--------------Choix du Terrain---------------" << endl;
	cout << "3. Terrain avec mur   |   4. Terrain sans mur " << endl
		 << "####################  |   ...................." << endl
		 << "#..................#  |   ...................." << endl
		 << "#..................#  |   ...................." << endl
		 << "#..................#  |   ...................." << endl
		 << "#..................#  |   ...................." << endl
		 << "#..................#  |   ...................." << endl
		 << "#..................#  |   ...................." << endl
		 << "####################  |   ...................." << endl;

	unsigned int choix1;

	do
	{
		cout << "Entrer votre choix de mode : soit 1, soit 2." << endl;
		cin >> choix1;
	} while (choix1 != 2 && choix1 != 1);

	switch (choix1)
	{
	case 1:
		choixMode = true;
		break;
	case 2:
		choixMode = false;
		break;
	default:
		break;
	}

	unsigned int choix2;
	do
	{
		cout << "Entrer votre choix de terrain : soit 3, soit 4." << endl;
		cin >> choix2;
	} while (choix2 != 3 && choix2 != 4);

	switch (choix2)
	{
	case 3:
		choixTerr = true;
		break;
	case 4:
		choixTerr = false;
		break;
	default:
		break;
	}
}

void txtBoucle(Jeu &jeu)
{
	bool choixMode, choixTerr;
	menuBoucle(choixMode, choixTerr);

	// initialisation de la premiere manche
	jeu.NouvelleManche(choixTerr);
	jeu.multOS = 1;

	bool ok = true;
	do
	{
		// Creation d'une nouvelle fenetre en mode texte
		// => fenetre de dimension et position (WIDTH,HEIGHT,STARTX,STARTY)
		WinTXT win(jeu.getConstTerrain().getDimX(), jeu.getConstTerrain().getDimY());

		int c;

		txtAff(win, jeu);

#ifdef _WIN32
		Sleep(100);
#else
		usleep(100000);
#endif // WIN32

		// Gestion des collisions + bonus
		jeu.Interaction(choixTerr, jeu.getJ1(), jeu.getJ2());
		jeu.Interaction(choixTerr, jeu.getJ2(), jeu.getJ1());

		// Si le mode multi joueur à été choisis
		if (choixMode == true)
		{
			// Deux "vrais" joueurs
			jeu.avance(choixTerr, jeu.getJ1());
			jeu.avance(choixTerr, jeu.getJ2());
		}
		// Si le mode solo (avec IA) à été choisis
		else
		{
			// Joueur + IA
			jeu.avanceIA(choixTerr);
		}

		// Affiche le bonus sur le terrain
		jeu.AffBonus();

		jeu.afficheChronoBonus();

		c = win.getCh();
		switch (c)
		{
		case 'q':
			jeu.actionClavier('q');
			break;
		case 'd':
			jeu.actionClavier('d');
			break;
		case 'z':
			jeu.actionClavier('z');
			break;
		case 's':
			jeu.actionClavier('s');
			break;
		case 'm':
			jeu.actionClavier('m');
			break;
		case 'k':
			jeu.actionClavier('k');
			break;
		case 'l':
			jeu.actionClavier('l');
			break;
		case 'o':
			jeu.actionClavier('o');
			break;
		case ' ':
			ok = false;
			break;
		}

		/*if(jeu.getConstTerrain().estPositionJ1Valide(j))
			ok = false;*/

		//	} while (ok);

		// fin de la partie quand un des deux joueurs atteint un score de 5 points
	} while (jeu.getConstJ1().getScore() < 5 && jeu.getConstJ2().getScore() < 5 && ok != false);

	if (jeu.getConstJ1().getScore() == 5)
	{
		std::cout << "Le joueur 1 a gagné !! " << std::endl;
		jeu.getJ1().setScore(0);
		jeu.getJ2().setScore(0);
	}
	else
	{
		std::cout << "Le joueur 2 a gangé !! " << std::endl;
		jeu.getJ1().setScore(0);
		jeu.getJ2().setScore(0);
	}
}
