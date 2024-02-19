#include "winTxt.h"
#include "txt_jeu.h"

int main ( int argc, char** argv ) {
    termClear();
	Jeu jeu;	
	txtBoucle(jeu);
    termClear();
	return 0;
}
