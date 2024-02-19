#ifndef _TXTJEU
#define _TXTJEU

#include "Jeu.h"
#include "winTxt.h"
//#include "Txt_Menu.h" 
void txtAff(WinTXT & win, const Jeu & jeu);
void menuBoucle (bool & choixMode, bool & choixTerr);
void txtBoucle (Jeu & j);

#endif


