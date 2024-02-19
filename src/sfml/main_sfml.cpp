#include "Jeu.h"
#include "sfmlJeu.h"

int main()
{
	sfmlJeu sj;
	Jeu jeu;
	while (sj.running())
	{
		sj.sfmlBoucle();
		sj.sfmlAff();
	}
	return 0;
}
